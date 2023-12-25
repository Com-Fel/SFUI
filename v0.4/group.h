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
		
		

	};
}