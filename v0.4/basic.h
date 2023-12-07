#pragma once
#include "UI.h"

using namespace std;

using namespace sf;
namespace basic {

	float max(vector<float> pp) {
		return pp[distance(pp.begin(), max_element(pp.begin(), pp.end()))];
	}
	float min(vector<float> pp) {
		return pp[distance(pp.begin(), min_element(pp.begin(), pp.end()))];
	}

	class MouseInf {
	public:
		bool clicked = false;
		int scroll = 0;
		Vector2i pos;
		MouseInf() {}
		MouseInf(Vector2i pos, bool clicked) {
			this->pos.x = pos.x;
			this->pos.y = pos.y;

			this->clicked = clicked;
		}
	};


	class base {
	public:
		Vector2f pos, size, mar;
		RenderTexture texture;
		string  tag;
		int id;
		base(){}
		Sprite update() {};
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

	class Clickable: public base {
	public:
		bool ishov, isclicked, selected;
		MouseInf mouseInf;
		MouseInf localMouseInf;
		Sprite sprite;
		bool isClicked() {

			if (ishov && mouseInf.clicked) {
				isclicked = true;
			}
			else {
				isclicked = false;

			}			

			return isclicked;

		}

		bool isHover() {
			int mx = mouseInf.pos.x;
			int my = mouseInf.pos.y;
			int sx = size.x;
			int  sy = size.y;
			
			if (((pos.x < mx && mx < pos.x + sx) && (pos.y < my && my < pos.y + sy))&&(!mouseInf.clicked||ishov)) {
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
	class Dragable:public Clickable{
	public:
		bool blockX, blockY =  false;
		Vector2i correct;
		void drag() {
			if (!selected) {
				if (!blockX) {
					correct.x = pos.x - mouseInf.pos.x;
				}
				if (!blockY) {
					correct.y = pos.y - mouseInf.pos.y;
				}
			}
			if (isclicked|| selected) {
				selected = true;
				if (blockX) {
					setPos(Vector2f(pos.x, (mouseInf.pos.y + correct.y)));

				}
				else if (blockY) {
					setPos(Vector2f((mouseInf.pos.x + correct.x),pos.y));

				}
				else {
					setPos(Vector2f((mouseInf.pos.x + correct.x), (mouseInf.pos.y + correct.y)));

				}

			}
			if(!mouseInf.clicked) {
				selected = false;

			}
		}

	};


	
}