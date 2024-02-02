#pragma once


#include "UI.h"

using namespace std;

using namespace sf;
using namespace basic;
namespace UI {


	class Gradient :public Colored, public base{
	public:
		Color color1, color2;
		int length;
		Sprite sprite;
		vector<Color> grad;

		Gradient(){}
		Gradient(Color color1, Color color2, Vector2f size, Vector2f pos) {
			this->color1 = color1;
			this->color2 = color2;
			this->size = size;
			this->pos = pos;
			
			(255,size.y);
		}
		


		void draw() {
			texture.create(255, size.y);


			RectangleShape pix;
			pix.setSize(Vector2f(1, size.y));

			for (int i = 0;i < 256;i++) {

				grad.push_back(Color(0+ color1.r *(color1.r== color2.r), 0 + color1.g * (color1.g == color2.g), 0 + color1.b * (color1.b == color2.b)));

			}
			int iter = 0;

			//RED
			if (color1.r < color2.r) {

				for (float r = color1.r;r < color2.r;r += (float(color2.r) - float(color1.r))/255) {
					grad[iter].r = r;
					iter++;


				}
			}
			else {

				for (float r = color1.r;r > color2.r;r += (float(color2.r) - float(color1.r)) / 255) {
					grad[iter].r = r;
					iter++;


				}
			}

			//GREEN
			iter = 0;

			if (color1.g < color2.g) {

				for (float g = color1.g;g < color2.g;g += (float(color2.g) - float(color1.g)) / 255) {
					grad[iter].g = g;
					iter++;


				}
			}
			else {

				for (float g = color1.g;g > color2.g;g += (float(color2.g) - float(color1.g)) /255) {
					grad[iter].g = g;
					iter++;


				}
			}
			iter = 0;
			//BLUE
			if (color1.b < color2.b) {

				for (float b = color1.b;b < color2.b;b += (float(color2.b) - float(color1.b)) / 255) {
					grad[iter].b = b;
					iter++;


				}
			}
			else {

				for (float b = color1.b;b > color2.b;b += (float(color2.b) - float(color1.b)) / 255) {
					grad[iter].b = b;
					iter++;


				}
			}
			//ALPHA
			iter = 0;
			if (color1.a < color2.a) {

				for (float a = color1.a;a < color2.a;a += (float(color2.a) - float(color1.a)) / 255) {
					grad[iter].a = a;
					iter++;


				}
			}
			else {

				for (float a = color1.a;a > color2.a;a += (float(color2.a) - float(color1.a)) / 255) {
					grad[iter].a = a;
					iter++;


				}
			}




			texture.clear(Color(0,0,0,0));
			for (int i = 0;i < grad.size();i++) {
				pix.setPosition(i,0);
				pix.setFillColor(grad[i]);
				texture.draw(pix);

			}


			texture.display();


			const sf::Texture& out = texture.getTexture();

			sprite.setTexture(out);
			sprite.setPosition(pos);
			sprite.scale(size.x/255,1);
		}
	};
	
	class Gradient2D : public Colored, public base {
	public:
		vector<Gradient*> grads;
		vector<Color> colors;
		Sprite sprite;
		Gradient2D(vector<Color> colors, Vector2f size, Vector2f pos) {
			
			

		

			
			this->colors = colors;

			this->size = size;
			this->pos = pos;
			texture.create(255,255);

			
		}

		void draw() {
			Gradient grad1(colors[0], colors[1], Vector2f(255, 1), Vector2f(0, 0));
			Gradient grad2(colors[2], colors[3], Vector2f(255, 1), Vector2f(0, 255));

			
			grad1.draw();
			grad2.draw();

			texture.clear(Color(0, 0, 0,0));

			
			for (int i = 0;i < grad1.grad.size();i++) {

				Gradient gr(grad1.grad[i], grad2.grad[i], Vector2f(255,1), Vector2f(0, i));
				gr.draw();
				

				texture.draw(gr.sprite);

			}
			//texture.draw(grad1.sprite);
			//texture.draw(grad2.sprite);


			texture.display();

			const sf::Texture& out = texture.getTexture();

			sprite.setTexture(out);
			sprite.setPosition(pos);
			sprite.scale(size.x / 255, size.y/255);



		}



	};
	
}