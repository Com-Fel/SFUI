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
		Label(Vector2f pos, StyleSheet style, string text) {
			this->colors = style.colors;
			this->fontName = style.fontName;
			this->text = text;
			this->pos = pos;
			this->fontSize = style.fontSize;
			this->mar = style.mar;
			font.loadFromFile(style.fontName);

			texture.create(fontSize * (text.length() + 1) / 2 + mar.x * 2, fontSize * 1.3 + mar.y * 2);
		}
		Label(Block inp, StyleSheets styles) {
			StyleSheet style;
			Vector2f pos(0, 0);
			Vector2f size(50, 50);
			string text = "But";
			string tag = "";

			for (int i = 0;i < inp.params.size();i++) {
				string key = inp.params[i].key;
				string value = inp.params[i].value;



				if (key == "pos") {
					strPosX = getStrSize(value)[0];
					strPosY = getStrSize(value)[1];
				}

				if (key == "size") {
					size = getVector2f(value);

				}
				if (key == "text") {
					text = value;
				}
				if (key == "style") {
					style = styles.getStyle(value);
				}
				if (key == "id") {
					this->tag = value;
					tag = value;
				}
			}

			Create(pos, style, text);
		}



		void Create(Vector2f pos, StyleSheet style, string text) {
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
			Text.setFillColor(colors[2][0]);

			
			texture.clear(colors[0][0]);
			texture.draw(Text);
			texture.display();


		}
		void setText(string text) {

			this->text = text;
			texture.create(fontSize * (text.length() + 1) / 2 + mar.x * 2, fontSize * 1.3 + mar.y * 2);

		}
		void setSize(Vector2f inp){}
	};

}