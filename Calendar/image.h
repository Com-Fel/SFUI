#pragma once


#include "UI.h"

using namespace std;

using namespace sf;
using namespace basic;

namespace UI {
	class ImageBox :public base {
	public:
		string path;
		ImageBox(Vector2f pos,Vector2f size, string path) {
			this->pos = pos;
			this->size = size;
			this->path = path;
			texture.create(size.x, size.y);
		}
		ImageBox(){}
		Sprite update() {
			draw();
			
			const sf::Texture& out = texture.getTexture();
			Sprite sprite(out);
			sprite.setPosition(pos);

			return sprite;
		}
		void draw() {
			Texture out;
			out.loadFromFile(path);
			Sprite sprite(out);
			sprite.setScale(size.x/out.getSize().x, size.y / out.getSize().y);

			texture.clear();
			texture.draw(sprite);
			texture.display();

		}

	};
}