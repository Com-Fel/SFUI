#pragma once


#include "UI.h"

using namespace std;

using namespace sf;
using namespace basic;

namespace UI {
	class ImageBox :public base {
	public:
		Sprite sprite;
		string path;
		Texture out;

		ImageBox(Vector2f pos,Vector2f size, string path) {
			this->pos = pos;
			this->size = size;
			this->path = path;
			out.loadFromFile(path);

			texture.create(size.x, size.y);
			draw();
			const sf::Texture& out = texture.getTexture();
			sprite.setTexture(out);

		}
		ImageBox(Block inp, StyleSheets styles) {
			for (int i = 0;i < inp.params.size();i++) {
				string key = inp.params[i].key;
				string value = inp.params[i].value;


				if (key == "path") {
					path = value;
				}
				if (key == "pos") {
					pos = getVector2f(value);
				}

				if (key == "size") {
					size = getVector2f(value);

				}
				if (key == "id") {
					tag = value;
				}
				
			}
			out.loadFromFile(path);

			texture.create(size.x, size.y);
			draw();
			const sf::Texture& out = texture.getTexture();
			sprite.setTexture(out);
		}
		ImageBox(){}
		Sprite update(basic::InputInfo inputInf) {
			

			sprite.setPosition(pos);

			return sprite;
		}
		void draw() {
			Sprite sprite(out);
			sprite.setScale(size.x/out.getSize().x, size.y / out.getSize().y);

			texture.clear(Color(0,0,0,0));
			texture.draw(sprite);
			texture.display();

		}

	};
}