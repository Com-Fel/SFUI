#pragma once


#include "UI.h"

using namespace std;

using namespace sf;
using namespace basic;
namespace UI {
	class Label : public base, public Colored, public Texteble {
	public:
		
		Label(Vector2f pos, Vector2f mar,vector<Color> colors, string fontName,int fontSize, string text) {
			this->colors.push_back(colors);
			this->fontName = fontName;
			this->text = text;
			this->pos = pos;
			this->fontSize = fontSize;
			this->mar = mar;
			texture.create(fontSize*(text.length()+1)/2+mar.x*2, fontSize*1.3+mar.y*2);
		}
		Sprite update() {
			draw();
			const sf::Texture& out = texture.getTexture();

			Sprite sprite(out);
			sprite.setPosition(pos);
			return sprite;
		}
		void draw() {
			Font font;
			Text Text;

			font.loadFromFile(fontName);
			Text.setString(text);
			Text.setFont(font);
			Text.setCharacterSize(fontSize);
			Text.setPosition(mar.x,mar.y);
			Text.setFillColor(colors[0][0]);

			
			texture.clear(colors[0][1]);
			texture.draw(Text);
			texture.display();


		}
	};

}