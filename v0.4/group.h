#pragma once

#include "UI.h"

using namespace std;

using namespace sf;


namespace UI {
	class Group :public Colored,public Clickable {
	public:
		vector<Button*> buttons;
		vector<Label*> labels;
		vector<ImageBox*> images;
		vector<Textbox*> textboxes;
		vector<Group*> groups;
		vector<Slider*> sliders;
		vector<Switcher*> switchers;

		Vector2f offset = Vector2f(0,0);
		MouseInf localMouse;

		string input;
		InputInfo localInf;
		Group(Vector2f pos, Vector2f size, Color color) {
			this->pos = pos;
			this->size = size;
			colors.push_back({ color });

			texture.create(size.x, size.y);

		}
		Group(BlockGroup inp,StyleSheets styles) {



			this->pos = Vector2f(0,0);
			this->size = Vector2f(200, 200);
			colors.push_back({ Color(0,0,0,0) });
			for (int i = 0;i < inp.params.size();i++) {
				string key = inp.params[i].key;
				string value = inp.params[i].value;



				if (key == "pos") {
					this->pos = getVector2f(value);
				}

				if (key == "size") {
					this->size = getVector2f(value);
				}
				
				if (key == "id") {
					this->tag = value;
				}
				if (key == "color") {
					this->colors[0][0] = getColorFromString(value);
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
				if(elem.type == "textbox") {
					append(new Textbox(elem, styles));
				}
			}


			for (int i = 0;i < inp.innerGroups.size();i++) {
				
				Group gr(inp.innerGroups[i], styles);
				this->append(new Group(inp.innerGroups[i], styles));

			}


			texture.create(size.x, size.y);

		}

		Group(){}
		Sprite update(InputInfo inf) {
			this->mouseInf = inf.mouse;

			//offset.y += inf.mouse.scroll;
			localMouse.pos.x = inf.mouse.pos.x - pos.x-offset.x;
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

				Vector2f p = el[i]->getPos();
				Sprite tempTexture = el[i]->update(localInf);
				

				tempTexture.setPosition(p.x + offset.x, p.y + offset.y);
				texture.draw(tempTexture);
			}
		}



		void draw() {

			InputInfo inp;
			if(colors.empty()){
				texture.clear(Color(0,0,0,0));

			}
			else {
				texture.clear(colors[0][0]);

			}
			
			drawElem(buttons);
			drawElem(labels);
			drawElem(images);
			drawElem(textboxes);
			drawElem(groups);
			drawElem(sliders);
			drawElem(switchers);
			
			texture.display();

		}
		
		void append(Button *but) {
			buttons.push_back(but);
		}
		void append(Label *lab) {
			labels.push_back(lab);

		}
		void append(ImageBox *im) {
			images.push_back(im);

		}
		void append(Textbox *tb) {
			textboxes.push_back(tb);

		}
		void append(Group *gr) {
			groups.push_back(gr);

		}
		void append(Slider *sl) {
			sliders.push_back(sl);

		}
		void append(Switcher *sw) {
			switchers.push_back(sw);

		}
		
		void createButton(Vector2f pos,Vector2f size, StyleSheet style, string tag,string text) {
			append(new Button(pos,size,style,tag,text));
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
			append(new Group(pos,size,color));
		}
		
		template<typename  Element>
		Button* findButtonById(string id) {
			for (int i = 0;i < buttons.size();i++) {
				if (buttons[i]->tag == id) {
					return buttons[i];
				}
			}
			
		}

		Label* findLabelById(string id) {

			for (int i = 0;i < labels.size();i++) {
				cout << labels[i]->tag << endl;
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
			
		

	};
}