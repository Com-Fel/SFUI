#pragma once

#include<iostream>
#include <fstream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "basic.h"
#include "UI.h"
using namespace sf;
using namespace UI;

namespace UI {
	class Scene:public base, public Colored {
	public:
		vector<Button*> buttons;
		vector<Label*> labels;
		vector<ImageBox*> images;
		vector<Textbox*> textboxes;
		MouseInf localMouse;

		string input;
		Scene(Vector2f pos, Vector2f size, Color color) {
			this->pos = pos;
			this->size = size;
			colors.push_back({});
			colors[0].push_back(color);

			texture.create(size.x, size.y);

		}
		Sprite update(MouseInf mouse, string inp) {
			localMouse.pos.x = mouse.pos.x - pos.x;
			localMouse.pos.y = mouse.pos.y - pos.y;
			localMouse.clicked = mouse.clicked;
			input = inp;


			draw();

			const sf::Texture& out = texture.getTexture();
			Sprite sprite(out);
			sprite.setPosition(pos);

			return sprite;
		}
		void draw() {



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
	};
	
}