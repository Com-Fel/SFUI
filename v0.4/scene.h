#pragma once

#include "UI.h"
using namespace sf;
using namespace UI;

namespace UI {
	class Scene :public Group {
	public:
		vector<LocalWindow*> windows;
		Scene(){}
		Scene(Vector2f size, Color color) {
			this->pos = Vector2f(0, 0);
			this->size = size;
			colors.push_back({ color });
			texture.create(size.x, size.y);

		}
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
			Sprite sprite(out);
			sprite.setPosition(pos);

			return sprite;
		}


		


		void draw() {

			InputInfo inp;

			texture.clear(colors[0][0]);

			drawElem(buttons);
			drawElem(labels);
			drawElem(images);
			drawElem(textboxes);
			drawElem(groups);
			drawElem(sliders);
			drawElem(switchers);
			drawElem(windows);

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
		void append(LocalWindow* lw) {
			windows.push_back(lw);
		}
	};
	Scene mainScene(Vector2f(1920, 1080), Color(0, 0, 0));
}
