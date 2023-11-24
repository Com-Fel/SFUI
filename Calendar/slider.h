#pragma once


#include "UI.h"



using namespace sf;
using namespace basic;

namespace UI {
	class SliderPiece : public Colored, public Dragable {
	public:
		int rad;
		SliderPiece(int rad,bool horizont) {
			this->rad = rad;
			if (horizont) {
				blockX = false;
				blockY = true;
			}
			else {
				blockX = true;
				blockY = false;
			}
			size = Vector2f(rad * 2, rad * 2);
			texture.create(rad*2, rad * 2);
		}
		Sprite update(MouseInf mouseInf) {
			this->mouseInf = mouseInf;
			isHover();
			isClicked();
			drag();
			draw();

			const sf::Texture& out = texture.getTexture();
			Sprite sprite(out);
			sprite.setPosition(pos);

			return sprite;
		}
		void draw() {
			
			CircleShape rect;

			rect.setFillColor(Color::Black);
			rect.setRadius(rad);

			texture.clear();
			texture.draw(rect);
			texture.display();

		}
	};


	class Slider : public Colored {

	};
}