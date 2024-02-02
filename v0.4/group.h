#pragma once

#include "UI.h"

using namespace std;

using namespace sf;


namespace UI {
	class Group :public Colored, public Clickable {
	public:
		vector<Button*> buttons;
		vector<Label*> labels;
		vector<ImageBox*> images;
		vector<Textbox*> textboxes;
		vector<Group*> groups;
		vector<Slider*> sliders;
		vector<Switcher*> switchers;

		Vector2f offset = Vector2f(0, 0);
		MouseInf localMouse;


		string background = "";
		Texture backgroundImage;

		string input;
		InputInfo localInf;
		Sprite spriteIm;
		StyleSheets styles;
		Group(Vector2f pos, Vector2f size, Color color) {
			this->pos = pos;
			this->size = size;
			colors.push_back({ color });

			texture.create(size.x, size.y);

		}
		Group(BlockGroup inp, StyleSheets styles) {
			this->styles = styles;


			this->pos = Vector2f(0, 0);
			this->size = Vector2f(200, 200);
			colors.push_back({ Color(0,0,0,0) });
			for (int i = 0;i < inp.params.size();i++) {
				string key = inp.params[i].key;
				string value = inp.params[i].value;



				if (key == "pos") {
					strPosX = getStrSize(value)[0];
					strPosY = getStrSize(value)[1];

				}

				if (key == "size") {
					strSizeX = getStrSize(value)[0];
					strSizeY = getStrSize(value)[1];
				}

				if (key == "id") {
					this->tag = value;
				}
				if (key == "color") {
					this->colors[0][0] = getColorFromString(value);
				}
				if (key == "background-image") {
					this->background = value;
					backgroundImage.loadFromFile(background);
					Sprite spriteIm1(backgroundImage);
					spriteIm = spriteIm1;
				}
			}

			for (int i = 0;i < inp.innerElements.size();i++) {
				Block elem = inp.innerElements[i];


				if (elem.type == "button") {
					append(new Button(elem, styles));
				}
				if (elem.type == "label") {
					append(new Label(elem, styles));
				}
				if (elem.type == "image") {
					append(new ImageBox(elem, styles));
				}
				if (elem.type == "textbox") {
					append(new Textbox(elem, styles));
				}
			}


			for (int i = 0;i < inp.innerGroups.size();i++) {

				Group gr(inp.innerGroups[i], styles);
				this->append(new Group(inp.innerGroups[i], styles));

			}


			texture.create(size.x, size.y);

		}

		Group() {}
		Sprite update(InputInfo inf) {
			this->mouseInf = inf.mouse;

			//offset.y += inf.mouse.scroll;
			localMouse.pos.x = inf.mouse.pos.x - pos.x - offset.x;
			localMouse.pos.y = inf.mouse.pos.y - pos.y - offset.y;
			localMouse.clicked = inf.mouse.clicked;
			input = inf.keyboardInput;
			localInf.update(inf.evt, localMouse.pos);
			localInf.keyboardInput = inf.keyboardInput;


			updateClickableInfo();

			draw();

			const sf::Texture& out = texture.getTexture();
			sprite.setTexture(out);
			sprite.setPosition(pos);
			return sprite;
		}


		template<typename elems>
		void drawElem(elems el) {

			for (int i = 0;i < el.size();i++) {

				el[i]->enabled = enabled;
				el[i]->setSize(Vector2f(getPX(el[i]->strSizeX, size.x), getPX(el[i]->strSizeY, size.y)));

				el[i]->setPos(Vector2f(getPX(el[i]->strPosX, size.x), getPX(el[i]->strPosY, size.y)));
				

				Vector2f p = el[i]->getPos();
				Sprite tempTexture = el[i]->update(localInf);
				isChange = el[i]->isChange || isChange;

				tempTexture.setPosition(p.x + offset.x, p.y + offset.y);
				texture.draw(tempTexture);
			}
		}


		void draw() {
			

			if (colors.empty()) {
				texture.clear(Color(0, 0, 0, 0));

			}
			else {
				texture.clear(colors[0][0]);

			}
			if (!background.empty()) {
				
				spriteIm.setScale(size.x / backgroundImage.getSize().x, size.y / backgroundImage.getSize().y);
				texture.draw(spriteIm);

			}
			drawElem(buttons);
			drawElem(labels);

			drawElem(textboxes);
			drawElem(groups);
			drawElem(sliders);
			drawElem(switchers);
			drawElem(images);
			texture.display();

		}

		void append(Button* but) {
			buttons.push_back(but);
		}
		void append(Label* lab) {
			labels.push_back(lab);

		}
		void append(ImageBox* im) {
			images.push_back(im);

		}
		void append(Textbox* tb) {
			textboxes.push_back(tb);

		}
		void append(Group* gr) {
			groups.push_back(gr);

		}
		void append(Slider* sl) {
			sliders.push_back(sl);

		}
		void append(Switcher* sw) {
			switchers.push_back(sw);

		}

		void createButton(Vector2f pos, Vector2f size, StyleSheet style, string tag, string text) {
			append(new Button(pos, size, style, tag, text));
		}
		void createLabel(Vector2f pos, StyleSheet style, string text) {
			append(new Label(pos, style, text));

		}
		void createImageBox(Vector2f pos, Vector2f size, string path) {
			append(new ImageBox(pos, size, path));
		}
		void createTextbox(Vector2f pos, Vector2f size, string placeHolder, StyleSheet style) {
			append(new Textbox(pos, size, placeHolder, style));
		}
		void createGroup(Vector2f pos, Vector2f size, Color color) {
			append(new Group(pos, size, color));
		}
		Group* createBlock(string name) {
			for (int i = 0;i < staticGroups.size();i++) {
				if (staticGroups[i].type == name) {
					append(new Group(staticGroups[i], styles));
					break;
				}
			}
			return groups[groups.size() - 1];
		}



		Button* findButtonById(string id) {
			for (int i = 0;i < buttons.size();i++) {
				if (buttons[i]->tag == id) {
					return buttons[i];
				}
			}

		}

		Label* findLabelById(string id) {

			for (int i = 0;i < labels.size();i++) {
				if (labels[i]->tag == id) {

					return labels[i];
				}
			}


		}
		ImageBox* findImageBoxById(string id) {
			for (int i = 0;i < images.size();i++) {
				if (images[i]->tag == id) {
					return images[i];
				}
			}

		}
		Textbox* findTextboxById(string id) {
			for (int i = 0;i < textboxes.size();i++) {
				if (textboxes[i]->tag == id) {
					return textboxes[i];
				}
			}

		}
		Group* findGroupById(string id) {
			for (int i = 0;i < groups.size();i++) {
				if (groups[i]->tag == id) {
					return groups[i];
				}
			}

		}
		bool haveClickedButton() {
			for (int i = 0;i < buttons.size();i++) {
				if (buttons[i]->isclicked) {
					return true;
				}
			}
			for (int i = 0;i < groups.size();i++) {
				if (groups[i]->haveClickedButton()) {
					return true;
				}
			}
			return false;

		}
		Button** findClickedButton() {
			for (int i = 0;i < buttons.size();i++) {
				if (buttons[i]->isclicked) {
					return &buttons[i];
				}
			}
			for (int i = 0;i < groups.size();i++) {
				if (groups[i]->haveClickedButton()) {
					return groups[i]->findClickedButton();
				}

			}
			return new Button * ();

		}

	};
}