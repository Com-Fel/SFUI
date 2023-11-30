#pragma once

#include "UI.h"

using namespace std;

using namespace sf;


namespace UI {
	class Group :public base,public Colored {
	public:
		vector<Button*> buttons;
		vector<Label*> labels;
		vector<ImageBox*> images;
		vector<Textbox*> textboxes;
		vector<Group*> groups;

		MouseInf localMouse;

		string input;
		InputInfo localInf;
		Group(Vector2f pos, Vector2f size, Color color) {
			this->pos = pos;
			this->size = size;
			colors.push_back({});
			colors[0].push_back(color);

			texture.create(size.x, size.y);

		}
		Group(){}
		Sprite update(InputInfo inf) {
			localMouse.pos.x = inf.mouse.pos.x - pos.x;
			localMouse.pos.y = inf.mouse.pos.y - pos.y;
			localMouse.clicked = inf.mouse.clicked;
			input = inf.keyboardInput;
			localInf.update(inf.evt, localMouse.pos);
			
			draw();

			const sf::Texture& out = texture.getTexture();
			Sprite sprite(out);
			sprite.setPosition(pos);

			return sprite;
		}
		void draw() {
			
			InputInfo inp;
			
			texture.clear(colors[0][0]);
			for (int i = 0;i < buttons.size();i++) {
				texture.draw(buttons[i]->update(localMouse));
			}
			for (int i = 0;i < labels.size();i++) {
				texture.draw(labels[i]->update());

			}
			for (int i = 0;i < images.size();i++) {
				texture.draw(images[i]->update());

			}
			for (int i = 0;i < textboxes.size();i++) {
				texture.draw(textboxes[i]->update(localMouse, input));

			}
			for (int i = 0;i < groups.size();i++) {
				texture.draw(groups[i]->update(localInf));

			}
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
		void append(Group* gr) {
			groups.push_back(gr);

		}
	};
}