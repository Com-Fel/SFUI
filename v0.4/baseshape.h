#pragma once


#include "UI.h"

using namespace std;

using namespace sf;
using namespace basic;
namespace UI {


	class BaseShape {
	public:


		Vector2f size,pos;
		vector<float> rads;
		Color col;
		RenderTexture texture;
		BaseShape(){}
		BaseShape(Vector2f size, vector<float> rads, Color col) {
			this->size = size;
			this->rads = rads;
			this->col = col;
			texture.create(size.x, size.y);
		}
		Sprite create() {
			texture.create(size.x, size.y);

			draw();

			const sf::Texture& out = texture.getTexture();
			Sprite sprite(out);
			sprite.setPosition(pos);
			return sprite;
		}
		void setSize(Vector2f size) {
			this->size = size;
		}
		void setPosition(Vector2f pos) {
			this->pos = pos;

		}
		void setFillColor(Color col) {
			this->col = col;
		}
		void setRads(vector<float> rads) {
			this->rads = rads;
		}
		void draw() {
			RectangleShape top, botom, left, right, center;
			CircleShape c1, c2, c3, c4;

			float bs = rads[distance(rads.begin(), max_element(rads.begin(), rads.end()))];
			c1.setOrigin(rads[0], rads[0]);
			c2.setOrigin(rads[1], rads[1]);
			c3.setOrigin(rads[2], rads[2]);
			c4.setOrigin(rads[3], rads[3]);

			c1.setPosition(rads[0], rads[0]);
			c2.setPosition(size.x - rads[1], rads[1]);
			c3.setPosition(rads[2], size.y - rads[2]);
			c4.setPosition(size.x - rads[3], size.y - rads[3]);

			c1.setRadius(rads[0]);
			c2.setRadius(rads[1]);
			c3.setRadius(rads[2]);
			c4.setRadius(rads[3]);


			c1.setTextureRect(IntRect(0, rads[0], rads[0], rads[0]));
			c2.setTextureRect(IntRect(rads[1], rads[1], rads[1], rads[1]));
			c3.setTextureRect(IntRect(0, 0, rads[2], rads[2]));
			c4.setTextureRect(IntRect(rads[3], 0, rads[3], rads[3]));


			center.setPosition(bs, bs);
			center.setSize(Vector2f(size.x - 2 * bs, size.y - 2 * bs));

			left.setPosition(0, rads[0]);
			left.setSize(Vector2f(bs, size.y - rads[0] - rads[2]));

			right.setPosition(size.x - bs, rads[1]);
			right.setSize(Vector2f(bs, size.y - rads[1] - rads[3]));

			top.setPosition(rads[0], 0);
			top.setSize(Vector2f(size.x - rads[0] - rads[1], bs));

			botom.setPosition(rads[2], size.y - bs);
			botom.setSize(Vector2f(size.x - rads[2] - rads[3], bs));



			c1.setFillColor(col);
			c2.setFillColor(col);
			c3.setFillColor(col);
			c4.setFillColor(col);
			top.setFillColor(col);
			left.setFillColor(col);
			right.setFillColor(col);
			botom.setFillColor(col);
			center.setFillColor(col);

			texture.clear(Color(0, 0, 0, 0));
	

			texture.draw(c1);
			texture.draw(c2);
			texture.draw(c3);
			texture.draw(c4);


			texture.draw(center);
			texture.draw(left);
			texture.draw(right);
			texture.draw(top);
			texture.draw(botom);



			texture.display();


		}
	};

}