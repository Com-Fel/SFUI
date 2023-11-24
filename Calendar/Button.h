#pragma once

#include<iostream>
#include <fstream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "basic.h"


using namespace std;

using namespace sf;
using namespace basic;

namespace UI {

	class Button: public Clickeble, public Texteble, public Colored, public Bordered {
	private:
		
	public:
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

		Sprite update(MouseInf mouse) {
			ishov = isHover(mouse.pos);
			isClicked(mouse.clicked);
			draw();
			const sf::Texture& out = texture.getTexture();

			Sprite sprite(out);
			sprite.setPosition(pos);
			return sprite;
		}
		void draw() {

			RectangleShape border;
			RectangleShape fon;

			Font font;
			Text Text;

			font.loadFromFile(fontName);
			Text.setString(text);
			Text.setFont(font);
			Text.setCharacterSize(fontSize);
			Text.setPosition(mar.x, mar.y);


			border.setSize(Vector2f(size.x, size.y));
			border.setPosition(0, 0);

			fon.setSize(Vector2f(size.x - 2 * bord, size.y - 2 * bord));
			fon.setPosition(bord, bord);

			Text.setPosition(mar.x, mar.y);

			if (isclicked) {
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

			texture.clear();

			texture.draw(border);
			texture.draw(fon);
			texture.draw(Text);
			texture.display();


		}
	};
}
