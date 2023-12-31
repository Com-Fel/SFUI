#pragma once


#include "UI.h"

using namespace std;

using namespace sf;
using namespace basic;
namespace UI {
	class LabelStyle {

	public:
		 

		Vector2f mar;vector<vector<Color>> colors; string fontName; int fontSize;


		LabelStyle(Vector2f mar, vector<Color> colors, string fontName, int fontSize) {
			this->colors.push_back(colors);
			this->fontName = fontName;
			this->fontSize = fontSize;
			this->mar = mar;
		}


	};


	class Label : public base, public Colored, public Texteble {
	public:
		Font font;
		
		Label(){}
		Label(Vector2f pos, Vector2f mar,vector<Color> colors, string fontName,int fontSize, string text) {
			this->colors.push_back(colors);
			this->fontName = fontName;
			this->text = text;
			this->pos = pos;
			this->fontSize = fontSize;
			this->mar = mar;
			font.loadFromFile(fontName);

			texture.create(fontSize*(text.length()+1)/2+mar.x*2, fontSize*1.3+mar.y*2);

		}
		Label(Vector2f pos, LabelStyle style, string text) {
			this->colors = style.colors;
			this->fontName = style.fontName;
			this->text = text;
			this->pos = pos;
			this->fontSize = style.fontSize;
			this->mar = style.mar;
			font.loadFromFile(style.fontName);

			texture.create(fontSize * (text.length() + 1) / 2 + mar.x * 2, fontSize * 1.3 + mar.y * 2);
		}
		void Create(Vector2f pos, LabelStyle style, string text) {
			this->colors = style.colors;
			this->fontName = style.fontName;
			this->text = text;
			this->pos = pos;
			this->fontSize = style.fontSize;
			this->mar = style.mar;
			font.loadFromFile(style.fontName);

			texture.create(fontSize * (text.length() + 1) / 2 + mar.x * 2, fontSize * 1.3 + mar.y * 2);
		}
		Sprite update(InputInfo inputInf) {
			draw();
			const sf::Texture& out = texture.getTexture();

			Sprite sprite(out);
			sprite.setPosition(pos);
			return sprite;
		}
		void draw() {
			

			Text.setString(text);
			Text.setFont(font);
			Text.setCharacterSize(fontSize);
			Text.setPosition(mar.x,mar.y);
			Text.setFillColor(colors[0][0]);

			
			texture.clear(colors[0][1]);
			texture.draw(Text);
			texture.display();


		}
		void setText(string text) {

			this->text = text;
			texture.create(fontSize * (text.length() + 1) / 2 + mar.x * 2, fontSize * 1.3 + mar.y * 2);

		}
	};

}