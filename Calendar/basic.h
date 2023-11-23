#pragma once
#include<iostream>
#include <fstream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
using namespace std;

using namespace sf;
namespace basic {
	class base {
	public:
		Vector2f pos, size, mar;
		RenderTexture texture;
		string  tag;
		int id;
		base(){}
		
		Vector2f getPos() {
			return pos;
		}
		void setPos(Vector2f pos) {
			this->pos = pos;
		}
		Vector2f getSize() {
			return size;
		}
		void setSize(Vector2f size) {
			this->size = size;
		}
		Vector2f getMargin() {
			return mar;
		}
		Vector2f setMargin(Vector2f mar) {
			this->mar = mar;
		}

	};

	class Clickeble: public base {
	public:
		bool ishov, isclicked;
		bool isClicked(bool mouseClick) {

			if (ishov && mouseClick) {
				isclicked = true;
			}
			else {
				isclicked = false;

			}
			return isclicked;

		}

		bool isHover(Vector2i mPos) {
			int mx = mPos.x;
			int my = mPos.y;
			int sx = size.x;
			int  sy = size.y;

			if (((pos.x < mx && mx < pos.x + sx) && (pos.y < my && my < pos.y + sy))) {
				ishov = true;
				return true;
			}
			else {
				ishov = false;
				return false;
			}

		}
	};
	class Texteble {
	public:
		string text, fontName;
		int fontSize;

		string getText() {
			return text;
		}
		void setText(string text) {
			this->text = text;
		}
	};

	class Colored {
	public:
		vector<vector<Color>> colors;
		void setColor(Color col, vector<int> st) {
			colors[st[0]][st[1]] = col;
		}
		Color getColor(vector<int> st) {
			return colors[st[0]][st[1]];
		}
	};
	class Bordered {
	public:
		int bord;
		int getBorderSize() {
			return bord;
		}
		void setBorderSize(int bord) {
			this->bord = bord;
		}
	};
}