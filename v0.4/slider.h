#pragma once


#include "UI.h"
#include <math.h>


using namespace sf;
using namespace basic;

namespace UI {
	class SliderPiece : public Colored, public Dragable {
	public:
		int rad;
		bool angle;
		SliderPiece(){}
		SliderPiece(int rad,bool horizont, bool angle) {
			this->rad = rad;
			this->angle = angle;
			blockX = !horizont;
			blockY = horizont;
			setPos(Vector2f(0, 0));
			size = Vector2f(rad * 2, rad * 2);
			
		}
		void update(MouseInf mouseInf, int end) {
			this->mouseInf = mouseInf;
			isHover();
			isClicked();
			isSelected();
			drag();
			if (angle) {
				if (blockY) {
					pos.y = pos.x;
				}
				if (blockX) {
					pos.x = end-pos.y;

				}
			}

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
			sprite.setTexture(out);
			sprite.setPosition(pos);

			
		}
		void draw() {
			
			CircleShape crc;
			texture.create(rad * 2, rad * 2);
			if (selected) {
				crc.setFillColor(colors[0][2]);
			}
			else if(ishov){
				crc.setFillColor(colors[0][1]);

			}
			else {
				crc.setFillColor(colors[0][0]);

			}
			crc.setRadius(rad);

			texture.clear(Color(0,0,0,0));
			texture.draw(crc);
			texture.display();

		}
	};


	class Slider : public Colored, public Clickable {
	public:
		int minValue,maxValue, length, width, Prad, value;

		bool horizont, angle;
		SliderPiece pic;
		MouseInf localMouse;
		Slider(){}
		Slider(Vector2f pos, int length, int minValue, int maxValue, int width, int Prad, vector<vector<Color>> colors, bool horizont, bool angle) {
			setPos(pos);
			this->length = length;
			this->minValue = minValue;
			this->maxValue = maxValue;
			this->width = width;
			this->Prad = Prad;
			this->colors = colors;
			this->horizont = horizont;
			this->angle = angle;
			if (!angle) {
				if (horizont) {

					texture.create(length + Prad * 2, Prad * 2);
					pic.setPos(Vector2f(0, 0));
				}
				else {
					texture.create(Prad * 2, length + Prad * 2);
					pic.setPos(Vector2f(0, length));
				}
			}
			else {
				texture.create(length + Prad * 2, length + Prad * 2);
				if (horizont) {
					pic.setPos(Vector2f(0, 0));
				}
				else {
					pic.setPos(Vector2f(length, 0));
				}
			}


			pic.angle = angle;
			pic.rad = Prad;
			pic.blockX = !horizont;
			pic.blockY = horizont;

			pic.size = Vector2f(Prad * 2, Prad * 2);
			pic.colors.push_back(this->colors[1]);

		}

		void Create() {
			if (!angle) {
				if (horizont) {

					texture.create(length + Prad * 2, Prad * 2);
					pic.setPos(Vector2f(0, 0));
				}
				else {
					texture.create(Prad * 2, length + Prad * 2);
					pic.setPos(Vector2f(0, length));
				}
			}
			else {
				
				texture.create(length + Prad * 2, length + Prad * 2);
				if (horizont) {

					pic.setPos(Vector2f(0, 0));
				}
				else {
					pic.setPos(Vector2f(length, 0));
				}
			}
			pic.angle = angle;
			pic.rad = Prad;
			pic.blockX = !horizont;
			pic.blockY = horizont;

			pic.size = Vector2f(Prad * 2, Prad * 2);
			pic.colors.push_back(this->colors[1]);

		}
		Sprite update(InputInfo inputInf) {
			

			localMouse.pos.x = inputInf.mouse.pos.x - pos.x;
			localMouse.pos.y = inputInf.mouse.pos.y - pos.y;
			localMouse.clicked = inputInf.mouse.clicked;
			this->mouseInf = inputInf.mouse;
			float pPos;
			pic.update(localMouse, length);
			
			if (horizont) {
				pPos = pic.pos.x;
				if (angle) {
					//pic.pos.y = pic.pos.x;
				}

			}
			else {
				pPos = length-pic.pos.y;
				if (angle) {
					//pic.pos.x = pic.pos.y;
				}
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
			if (!angle) {
				if (horizont) {

					texture.create(length + Prad * 2, Prad * 2);
					
				}
				else {
					texture.create(Prad * 2, length + Prad * 2);
					
				}
			}
			else {

				texture.create(length + Prad * 2, length + Prad * 2);
				
			}

			

			if (horizont) {
				rect.setSize(Vector2f(length, width));
				rect.setPosition(Prad, Prad - width / 2);
				
			}
			else {
				rect.setSize(Vector2f(width, length));
				rect.setPosition(Prad - width / 2, Prad);
			}
			if (angle) {
				rect.setSize(Vector2f(sqrt(length * length * 2), width));
				rect.setOrigin(Vector2f(0, width / 2));

				if (horizont) {
					rect.setPosition(0, width );

					rect.setRotation(45);
				}
				else {
					rect.setPosition(length + width + pic.rad, width);

					rect.setRotation(135);
				}


			}
			rect.setFillColor(colors[0][0]);
			texture.clear(Color(0, 0, 0, 0));
			texture.draw(rect);
			//pic.sprite.setOrigin(Vector2f(pic.rad/2,0));
			texture.draw(pic.sprite);

			texture.display();

		}

		void setValue() {

		}
	};
}