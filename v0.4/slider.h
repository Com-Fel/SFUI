#pragma once


#include "UI.h"



using namespace sf;
using namespace basic;

namespace UI {
	class SliderPiece : public Colored, public Dragable {
	public:
		int rad;
		SliderPiece(){}
		SliderPiece(int rad,bool horizont) {
			this->rad = rad;
			
			blockX = !horizont;
			blockY = horizont;
			setPos(Vector2f(0, 0));
			size = Vector2f(rad * 2, rad * 2);
			
		}
		Sprite update(MouseInf mouseInf, int end) {
			this->mouseInf = mouseInf;
			isHover();
			isClicked();
			drag();


			if (pos.x > end) {
				pos.x = end;
			}
			if (pos.x < 0) {
				pos.x = 0;
			}
			if (pos.y > end) {
				pos.y = end;
			}
			if (pos.y < 0) {
				pos.y = 0;
			}

			draw();

			const sf::Texture& out = texture.getTexture();
			Sprite sprite(out);
			sprite.setPosition(pos);

			return sprite;
		}
		void draw() {
			
			CircleShape crc;
			texture.create(rad * 2, rad * 2);
			crc.setFillColor(Color::Red);
			crc.setRadius(rad);

			texture.clear(Color(0,0,0,0));
			texture.draw(crc);
			texture.display();

		}
	};


	class Slider : public Colored, public Clickable {
	public:
		int minValue,maxValue, length, width, Prad, value;

		bool horizont;
		SliderPiece pic;
		MouseInf localMouse;
		Slider(Vector2f pos, int length, int minValue, int maxValue, int width, int Prad, vector<vector<Color>> colors,bool horizont) {
			setPos(pos);
			this->length = length;
			this->minValue = minValue;
			this->maxValue = maxValue;
			this->width = width;
			this->Prad = Prad;
			this->colors = colors;
			this->horizont = horizont;
			if (horizont) {
				texture.create(length + Prad * 2, Prad * 2);
				pic.setPos(Vector2f(0, 0));

			}
			else {
				texture.create(Prad * 2, length + Prad * 2);
				pic.setPos(Vector2f(0, length));


			}
			pic.rad = Prad;
			pic.blockX = !horizont;
			pic.blockY = horizont;

			pic.size = Vector2f(Prad * 2, Prad * 2);

		}
		Sprite update(MouseInf mouseInf) {
			localMouse.pos.x = mouseInf.pos.x - pos.x;
			localMouse.pos.y = mouseInf.pos.y - pos.y;
			localMouse.clicked = mouseInf.clicked;
			this->mouseInf = mouseInf;
			float pPos;
			if (horizont) {
				pPos = pic.pos.x;
			}
			else {
				pPos = length-pic.pos.y;

			}

			
			value = pPos / length * (maxValue - minValue) + minValue;
			draw();

			const sf::Texture& out = texture.getTexture();
			Sprite sprite(out);
			sprite.setPosition(pos);

			return sprite;
		}
		void draw() {
			RectangleShape rect;
			if (horizont) {
				rect.setSize(Vector2f(length, width));
				rect.setPosition(Prad, Prad - width / 2);

			}
			else {
				rect.setSize(Vector2f(width, length));
				rect.setPosition(Prad - width / 2, Prad);


			}
			rect.setFillColor(Color::Black);
			texture.clear(Color(0, 0, 0, 0));
			texture.draw(rect);

			texture.draw(pic.update(localMouse, length));

			texture.display();

		}
	};
}