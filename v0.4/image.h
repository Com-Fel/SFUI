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
		Texture image;

		ImageBox(Vector2f pos,Vector2f size, string path) {
			this->pos = pos;
			this->size = size;
			this->path = path;
			image.loadFromFile(path);

			texture.create(size.x, size.y);
			draw();
			const sf::Texture& out = texture.getTexture();
			sprite.setTexture(out);

		}
		ImageBox(Block inp, StyleSheets styles) {
			size = Vector2f(0, 0);
			for (int i = 0;i < inp.params.size();i++) {
				string key = inp.params[i].key;
				string value = inp.params[i].value;


				if (key == "path") {
					path = value;
				}
				if (key == "pos") {
					strPosX = getStrSize(value)[0];
					strPosY = getStrSize(value)[1];
					

				}

				if (key == "size") {
					strSizeX = getStrSize(value)[0];
					strSizeY = getStrSize(value)[1];

				}
				if (key == "id") {
					tag = value;
				}
				
			}
			image.loadFromFile(path);
			if (size == Vector2f(0, 0)) {
				size.x = image.getSize().x;
				size.y = image.getSize().y;
				strSizeX = to_string(int(size.x)) + "px";
				strSizeY = to_string(int(size.y)) + "px";
				cout << strSizeX;
			}
			texture.create(size.x, size.y);

			draw();
			const sf::Texture& out = texture.getTexture();
			sprite.setTexture(out);
		}
		ImageBox(){}
		Sprite update(basic::InputInfo inputInf) {

			if (oldSize != size) {
				texture.create(size.x, size.y);
			}
			oldSize = size;


			draw();
			const sf::Texture& out = texture.getTexture();
			Sprite sp(out);
			sp.setPosition(pos);
			sp.setTexture(out);
			return sp;
		}
		void draw() {
			Sprite spriteIm(image);
			spriteIm.setScale(size.x/ image.getSize().x, size.y / image.getSize().y);
	
			
			texture.clear(Color(0,0,0,0));
			texture.draw(spriteIm);
			texture.display();
			
		}

	};
}