#pragma once


#include "UI.h"

using namespace std;

using namespace sf;
using namespace basic;
namespace UI {

	class TrPart :public Dragable, public Colored {
	public:

		TrPart() { texture.create(10, 10); }
		TrPart(Vector2f pos) {
			this->pos = pos;
			
			
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

			RectangleShape rect;
			rect.setPosition(0, 0);
			rect.setSize(size);
			rect.setFillColor(Color(200, 200, 200));
			texture.getSize();

			if (selected) {
				rect.setFillColor(Color(200,200,200));
			}
			else if (ishov) {
				rect.setFillColor(Color(100, 100, 100));

			}
			else {
				rect.setFillColor(Color(50, 50, 50));

			}
			
			texture.clear();

			texture.draw(rect);
			texture.display();

		}

	};



	class TransformableObject : public Dragable, public Colored {
	public:
		
		vector<TrPart*> drags;
		TrPart point;
		Sprite p;
		Slider r1,r2,r3,r4;
		vector<Slider*> rads;
		int maxVal;
		TransformableObject(Vector2f pos,Vector2f size) {
			this->pos = pos;
			this->size = size;
			texture.create(size.x, size.y);
			point.setPos(Vector2f(size.x-10, size.x-10));
			point.setSize(Vector2f(10, 10));


			append(&point);

			append(&r1);
			append(&r2);
			append(&r3);
			append(&r4);


			rads[0]->horizont = true;
			rads[0]->angle = true;

			rads[1]->horizont = false;
			rads[1]->angle = true;

			rads[2]->horizont = false;
			rads[2]->angle = true;

			rads[3]->horizont = true;
			rads[3]->angle = true;


			for (int i = 0;i < 4;i++) {
				
				rads[i]->length = 50;
				rads[i]->minValue = 0;
				rads[i]->maxValue = 100;

				rads[i]->width = 2;
				rads[i]->Prad = 4;
				rads[i]->colors = { {Color(75,75,75)},{Color(0,0,0),Color(150,150,150),Color(200,200,200)} };
				
			
				rads[i]->Create();

			}
			
			
			
		}

		Sprite update(InputInfo inputInf) {
		

			this->mouseInf.pos.x = inputInf.mouse.pos.x ;
			this->mouseInf.pos.y = inputInf.mouse.pos.y ;
			this->mouseInf.clicked = inputInf.mouse.clicked;

			this->localMouseInf.pos.x = inputInf.mouse.pos.x - pos.x;
			this->localMouseInf.pos.y = inputInf.mouse.pos.y - pos.y;
			this->localMouseInf.clicked = inputInf.mouse.clicked;
			
			
			updateClickableInfo();
			bool can = true;
			for (int i = 0;i < 4;i++) {
				if (rads[i]->pic.selected || rads[i]->pic.ishov) {
					can = false;
				}
				maxVal = min({ size.x, size.y }) / 4;
				rads[i]->maxValue = maxVal;

			}
			if (!point.ishov&& !point.selected && can) {
				drag();

			}

		    p = point.update(localMouseInf);


			size.x = point.pos.x + point.size.x;
			size.y = point.pos.y + point.size.y;

			draw();

			const sf::Texture& out = texture.getTexture();
			
			Sprite sprite(out);
			
			sprite.setPosition(pos);
			return sprite;
		}
		void draw() {
			BaseShape shape(size, { float(r1.value),maxVal-float(r2.value),float(r3.value),maxVal-float(r4.value) },Color(255,0,0));


			texture.create(size.x, size.y);


			texture.clear(Color(0, 0, 0,0));
			texture.draw(shape.create());

			texture.draw(p);
			
			Sprite sr1, sr2, sr3, sr4;
			InputInfo inf;
			inf.mouse = localMouseInf;

			sr1 = r1.update(inf);
			sr2 = r2.update(inf);
			sr3 = r3.update(inf);
			sr4 = r4.update(inf);

			rads[0]->setPos(Vector2f(size.x / 10, size.y / 10));
			rads[1]->setPos(Vector2f(size.x - size.x / 10-  sr2.getTextureRect().width , size.y / 10));
			rads[2]->setPos(Vector2f(size.x / 10, size.y - size.y / 10 - sr2.getTextureRect().height));
			rads[3]->setPos(Vector2f(size.x - size.x / 10 - sr2.getTextureRect().width, size.y - size.y / 10 - sr2.getTextureRect().height));

			float m = min({ size.x,size.y }) / 3;
			if (m > 50) {
				m = 50;
			}
			rads[0]->length = m;
			rads[1]->length = m;
			rads[2]->length = m;
			rads[3]->length = m;



			texture.draw(sr1);
			texture.draw(sr2);
			texture.draw(sr3);
			texture.draw(sr4);


			texture.display();


		}
		void append(TrPart* p) {
			drags.push_back(p);
		}
		void append(Slider* p) {
			rads.push_back(p);
		}
	};

}