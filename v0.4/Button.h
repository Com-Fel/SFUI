#pragma once

#include "UI.h"



using namespace std;

using namespace sf;
using namespace basic;

namespace UI {

	class ButtonStyle:public Style {

	public:
		Vector2f mar;
		int bord, fontSize;
		vector<vector<Color>> colors;
		string fontName;
		vector<float> rads;
		
		ButtonStyle() {}
		ButtonStyle(vector<vector<Color>> colors, int bord, Vector2f mar, int fontSize, string fontName, vector<float> rads) {
			this->bord = bord;
			this->colors = colors;
			this->fontSize = fontSize;
			this->fontName = fontName;
			this->mar = mar;
			this->rads = rads;
		}
	};
	class Button: public Clickable, public Texteble, public Colored, public Bordered {
		
	public:
		BaseShape border;
		BaseShape fon;

		Font font;

		typedef void (*onClick)();
		onClick onClickFunction = EmptyFunction;
		Button(){}
		Button(Vector2f pos, Vector2f size, Vector2f mar, int bord, vector<vector<Color>> colors, int fontSize, string fontName, string tag, string text) {
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
		Button(Vector2f pos, Vector2f size, ButtonStyle style, string tag, string text) {
			this->pos = pos;
			this->size = size;
			this->mar = style.mar;
			this->bord = style.bord;
			this->colors = style.colors;
			this->fontSize = style.fontSize;
			this->fontName = style.fontName;
			this->rads = style.rads;
			this->tag = tag;
			this->text = text;

			


			font.loadFromFile(fontName);
			Text.setString(text);
			Text.setFont(font);
			texture.create(size.x, size.y);
		}
		void Create(Vector2f pos, Vector2f size, ButtonStyle style, string tag, string text) {
			this->pos = pos;
			this->size = size;
			this->mar = style.mar;
			this->bord = style.bord;
			this->colors = style.colors;
			this->fontSize = style.fontSize;
			this->fontName = style.fontName;
			this->rads = style.rads;
			this->tag = tag;
			this->text = text;
			font.loadFromFile(fontName);
			Text.setString(text);
			Text.setFont(font);
			texture.create(size.x, size.y);
		}
		Sprite update(InputInfo inf) {
			this->mouseInf = inf.mouse;
			updateClickableInfo();
			if (isclicked) {
				onClickFunction();
			}
			draw();
			const sf::Texture& out = texture.getTexture();

			Sprite sprite(out);
			sprite.setPosition(pos);
			
			return sprite;
		}
		void draw() {

		
			
			border.setRads(rads);
			fon.setRads(rads);
			

			
			Text.setCharacterSize(fontSize);
			Text.setPosition(mar.x, mar.y);


			border.setSize(Vector2f(size.x, size.y));
			border.setPosition(Vector2f(0, 0));

			fon.setSize(Vector2f(size.x - 2 * bord, size.y - 2 * bord));
			fon.setPosition(Vector2f(bord, bord));
			Text.setPosition(mar.x, mar.y);

			if (selected) {
				fon.setFillColor(colors[0][2]);
				border.setFillColor(colors[1][2]);
				Text.setFillColor(colors[2][2]);
			}
			else if (ishov) {
				fon.setFillColor(colors[0][1]);
				border.setFillColor(colors[1][1]);
				Text.setFillColor(colors[2][1]);
			}
			else {
				fon.setFillColor(colors[0][0]);
				border.setFillColor(colors[1][0]);
				Text.setFillColor(colors[2][0]);
			}

			texture.clear(Color(0,0,0,0));

			texture.draw(border.create());
			texture.draw(fon.create());

			texture.draw(Text);


			texture.display();


		}
		
	};


	
}
