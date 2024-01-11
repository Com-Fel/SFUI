#pragma once


#include "UI.h"



using namespace sf;
using namespace basic;

namespace UI {

	class SwitcherStyle : public StyleSheet {
	public:
		Vector2f mar;
		int bord, fontSize; 
		vector<vector<Color>> colors; 
		string fontName;

		SwitcherStyle(Vector2f mar, int bord, vector<vector<Color>> colors, int fontSize, string fontName) {

			this->mar = mar;
			this->bord = bord;
			this->colors = colors;
			this->fontSize = fontSize;
			this->fontName = fontName;


		}

	};



	class Switcher : public Button {
	public:
		bool canChange;
		Switcher(Vector2f pos, Vector2f size, Vector2f mar, int bord, vector<vector<Color>> colors, int fontSize, string fontName, string tag, string text) {
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
		Switcher(Vector2f pos, Vector2f size, StyleSheet style, string tag, string text) {
			this->pos = pos;
			this->size = size;
			this->mar = style.mar;
			this->bord = style.bord;
			this->colors = style.colors;
			this->fontSize = style.fontSize;
			this->fontName = style.fontName;
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
		Sprite update(InputInfo inputInf) {
			this->mouseInf = inputInf.mouse;
			isHover();
			if (!ishov) {
				canChange = true;
			}
			updateClickableInfo();

			draw();
			const sf::Texture& out = texture.getTexture();

			Sprite sprite(out);
			sprite.setPosition(pos);
			return sprite;
		}
	};
}