#pragma once


#include "UI.h"



using namespace sf;
using namespace basic;

namespace UI {
	class Swither : public Button {
	public:
		bool canChange;
		Swither(Vector2f pos, Vector2f size, Vector2f mar, int bord, vector<vector<Color>> colors, int fontSize, string fontName, string tag, string text) {
			this->pos = pos;
			this->size = size;
			this->mar = mar;
			this->bord = bord;
			this->colors = colors;
			this->fontSize = fontSize;
			this->fontName = fontName;
			this->tag = tag;
			this->text = text;
			texture.create(size.x, size.y);

		}
		bool isClicked() {

			if (ishov && mouseInf.clicked ) {
				if (canChange) {
					isclicked = !isclicked;
					canChange = false;

				}
			}
			else {
				canChange = true;

			}
			return isclicked;

		}
		Sprite update(MouseInf mouseInf) {
			this->mouseInf = mouseInf;
			isHover();
			if (!ishov) {
				canChange = true;
			}
			isClicked();

			draw();
			const sf::Texture& out = texture.getTexture();

			Sprite sprite(out);
			sprite.setPosition(pos);
			return sprite;
		}
	};
}