#pragma once


#include "UI.h"

using namespace std;

using namespace sf;
using namespace basic;

namespace UI {
	class Textbox :  public Texteble, public Colored, public Clickable {
	public:
		int b, b2;
		bool selected = false;
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
			texture.create(size.x,size.y);
			instr = size.x*1.3/ fontSize;
		}
		
		Sprite update(MouseInf mouse,string inp) {
			
			mouseInf = mouse;

			input = inp;

			isHover();
			isClicked();
			txt();
			draw(mouse.pos, mouse.clicked);
			if (isclicked) {
				selected = true;
			}
			if (mouse.clicked && !ishov) {
				selected = false;

			}
			const sf::Texture& out = texture.getTexture();

			Sprite sprite(out);
			sprite.setPosition(pos);
			return sprite;
		}
		void txt() {
			
			if (input != "" || !selected) {
				if (!stText.empty() && stText[stText.length() - 1] == '|') {
					stText.pop_back();
				}
			}
			if (input != "DELETE2") {
				if (selected) {
					stText += input;
				}
			}

			else if(stText.size()>0){
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
			if (selected) {
				ticker -= 1;
				if (ticker == 0) {
					stText += '|';
				}
				else if (ticker == -tTime) {
					if (!stText.empty() && stText[stText.length() - 1] == '|') {
						stText.pop_back();
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
		void draw(Vector2i mPos, bool mouseClick) {

			RectangleShape border;
			RectangleShape fon;

			Font font;
			Text Text;
			
			font.loadFromFile(fontName);
			Text.setString(text);
			Text.setFont(font);
			Text.setCharacterSize(fontSize);
			Text.setPosition(b + b2 + 3, b + b2 + 3);


			border.setPosition(b,b);
			border.setSize(Vector2f(size.x - b * 2, size.y - b * 2));

			fon.setPosition(b+b2, b + b2);	
			fon.setSize(Vector2f(size.x -(b + b2)*2, size.y - (b + b2) * 2));
			

			if (selected) {
				texture.clear(colors[1][0]);
				fon.setFillColor(colors[1][1]);
				border.setFillColor(colors[1][2]);
				Text.setFillColor(colors[1][3]);

			}
			else if(stText =="") {
				texture.clear(colors[0][0]);
				fon.setFillColor(colors[0][1]);
				border.setFillColor(colors[0][2]);
				Text.setFillColor(colors[0][4]);
			}
			else {
				texture.clear(colors[0][0]);
				fon.setFillColor(colors[0][1]);
				border.setFillColor(colors[0][2]);
				Text.setFillColor(colors[0][3]);
			}

			texture.draw(border);
			texture.draw(fon);
			texture.draw(Text);

			texture.display();
			
		}
		
	};
}