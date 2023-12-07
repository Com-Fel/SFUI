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

		Gradient(Color color1, Color color2, int length, Vector2f pos) {
			this->color1;
			this->color2;
			this->length;
			this->pos = pos;
		}
		


		void draw() {
			RectangleShape pix;



			texture.clear();

			texture.draw(pix);


			texture.display();


		}
	};

}