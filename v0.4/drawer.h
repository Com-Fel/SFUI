#pragma once


#include "UI.h"

using namespace std;

using namespace sf;
using namespace basic;

namespace UI {
	class Drawer :public base {
	public:
		Sprite sprite;
		string path;
		Texture out;
		Drawer(){}
		Drawer(Vector2f size) {
			this->pos = Vector2f(0,0);
			this->size = size;
			

			texture.create(size.x, size.y);
			draw();
			const sf::Texture& out = texture.getTexture();
			sprite.setTexture(out);

		}
		
		Sprite update() {

			
			draw();
			const sf::Texture& out = texture.getTexture();
			sprite.setTexture(out);
			

			return sprite;
		}
		void draw() {
		
			texture.display();

		}

		void clear() {
			texture.clear(Color(0, 0, 0, 0));
		}

		void drawRect(Vector2f pos, Vector2f size, Color col) {
			RectangleShape rect;
			rect.setFillColor(col);
			rect.setPosition(pos);
			rect.setSize(size);
			texture.draw(rect);
			update();

		}


	};
	Drawer drawer;

}