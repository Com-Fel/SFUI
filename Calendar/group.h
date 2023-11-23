#pragma once

#include<iostream>
#include <fstream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "basic.h"
#include "UI.h"

using namespace std;

using namespace sf;
using namespace basic;
using namespace UI;


namespace UI {
	class Group :public base {
	public:
		vector<Button> 
		Group(Vector2f pos, Vector2f size) {
			this->pos = pos;
			this->size = size;
			texture.create(size.x, size.y);
		}
		Sprite update() {
			draw();

			const sf::Texture& out = texture.getTexture();
			Sprite sprite(out);
			sprite.setPosition(pos);

			return sprite;
		}
		void draw() {
			
			
			
			texture.clear();
			//texture.draw();
			texture.display();

		}

	};
}