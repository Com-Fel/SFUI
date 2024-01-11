#pragma once


#include "UI.h"

using namespace std;

using namespace sf;
using namespace basic;

namespace UI {

	class TextboxStyle : public StyleSheet {



	public:
		int b, b2, fontSize;
		vector<vector<Color>> colors;
		string fontName;

		TextboxStyle(int b, int b2, vector<vector<Color>> colors, string fontName, int fontSize) {
			this->b = b;
			this->b2 = b2;
			this->colors = colors;
			this->fontName = fontName;
			this->fontSize = fontSize;
		}

	};

	class Textbox :  public Texteble, public Colored, public Clickable {
	public:
		int b, b2;
		
		string input;
		const int tTime = 20;
		int strings = 1, instr,ticker = tTime;
		string stText = text;
		string placeHolder;
		Textbox(Vector2f pos,Vector2f size, string placeHolder, int b,int b2,vector<vector<Color>> colors,string fontName, int fontSize) {
			this->pos = pos;
			this->size = size;
			this->b = b;
			this->b2 = b2;
			this->colors = colors;
			this->fontName = fontName;
			this->fontSize = fontSize;
			this->placeHolder = placeHolder;
			font.loadFromFile(fontName);

			texture.create(size.x,size.y);
			instr = size.x*1.3/ fontSize;
		}
		Textbox(Vector2f pos, Vector2f size, string placeHolder, StyleSheet style) {
			this->pos = pos;
			this->size = size;
			this->b = style.bord;
			this->b2 = style.bordIn;
			this->colors = style.colors;
			this->fontName = style.fontName;
			this->fontSize = style.fontSize;
			this->placeHolder = placeHolder;
			font.loadFromFile(fontName);

			texture.create(size.x, size.y);
			instr = size.x * 1.3 / fontSize;
		}
		Textbox(Block inp, StyleSheets styles) {
			StyleSheet style;
			
			
			for (int i = 0;i < inp.params.size();i++) {
				string key = inp.params[i].key;
				string value = inp.params[i].value;



				if (key == "pos") {
					pos = getVector2f(value);
				}

				if (key == "size") {
					size = getVector2f(value);

				}
				if (key == "placeholder") {
					placeHolder = value;
					this->b = style.bord;
					this->b2 = style.bordIn;
					this->colors = style.colors;
					this->fontName = style.fontName;
					this->fontSize = style.fontSize;
				}
				if (key == "style") {
					style = styles.getStyle(value);
				}
				if (key == "id") {
					this->tag = value;
					tag = value;
				}
			}
			font.loadFromFile(fontName);

			texture.create(size.x, size.y);
			instr = size.x * 1.3 / fontSize;
		}



		Sprite update(InputInfo inputInf) {
			
			mouseInf = inputInf.mouse;

			input = inputInf.keyboardInput;

			updateClickableInfo();
			
			txt();
			
			draw();
			
			const sf::Texture& out = texture.getTexture();

			Sprite sprite(out);
			sprite.setPosition(pos);
			return sprite;
		}
		void txt() {
			
			if (input != "" || !chosen) {
				if (!stText.empty() && text[text.length() - 1] == '|') {
					text.pop_back();
				}
			}
			if (input != "DELETE2") {
				if (chosen) {
					stText += input;
				}
			}

			else if(stText.size()>0 && chosen){
				stText.pop_back();
			}

			string temp= "";
			


			for (int i = 0;i < stText.length();i++) {
				if (i % instr==0&&i!=0) {
					temp += '\n';
				}
				temp += stText[i];


			}
			text = temp;
			if (chosen) {
				ticker -= 1;
				if (ticker > 0) {
					text += '|';
				}
				else  if(ticker <= -tTime){
					if (!stText.empty() && text[text.length() - 1] == '|') {
						text.pop_back();
					}
					ticker = tTime;
				}
			}
			else {
				ticker = tTime;

				if (input == "" && stText == "") {
					text = placeHolder;
				}
			}

		}
		void draw() {

			RectangleShape border;
			RectangleShape fon;

			
			Text.setString(text);
			Text.setFont(font);
			Text.setCharacterSize(fontSize);
			Text.setPosition(b + b2 + 3, b + b2 + 3);


			border.setPosition(b,b);
			border.setSize(Vector2f(size.x - b * 2, size.y - b * 2));

			fon.setPosition(b+b2, b + b2);	
			fon.setSize(Vector2f(size.x -(b + b2)*2, size.y - (b + b2) * 2));
			

			if (chosen) {
				texture.clear(colors[1][1]);
				fon.setFillColor(colors[0][1]);
				border.setFillColor(colors[3][1]);
				Text.setFillColor(colors[2][1]);

			}
			else if(stText =="") {
				texture.clear(colors[1][0]);
				fon.setFillColor(colors[0][0]);
				border.setFillColor(colors[3][0]);
				Text.setFillColor(colors[2][2]);
			}
			else {
				texture.clear(colors[1][0]);
				fon.setFillColor(colors[0][0]);
				border.setFillColor(colors[3][0]);
				Text.setFillColor(colors[2][0]);
			}

			texture.draw(border);
			texture.draw(fon);
			texture.draw(Text);

			texture.display();
			
		}
		
	};
}