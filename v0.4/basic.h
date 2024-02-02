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

	void EmptyFunction(){}

	class XY {
	public:
		float x, y;
		XY(){}
		XY(float x, float y) {
			this->x = x;
			this->y = y;
		}
	};
	

	class base {
	public:
		Vector2f pos = Vector2f(0,0), size, mar;
		Vector2f oldSize;

		RenderTexture texture;
		Sprite sprite;
		string  tag;
		bool enabled = true;
		bool isChange, parentChange;
		int id;
		int Zpos;
		string strSizeX, strSizeY;
		string strPosX = "0px", strPosY = "0px";

		typedef void (*onUpdate)();
		onUpdate onUpdateFunction = EmptyFunction;


		base(){}
		Sprite update() {};
		Vector2f getPos() {
			return pos;
		}
		void setPos(Vector2f pos) {

			

			//cout << strPosX << " " << strPosY << tag << endl;
			this->pos = pos;

			this->strPosX = to_string(int(this->pos.x)) + "px";
			this->strPosY = to_string(int(this->pos.y)) + "px";
		}
		Vector2f getSize() {
			return size;
		}
		void setSize(Vector2f size) {
			this->size = size;
			this->strSizeX = to_string(int(this->size.x)) + "px";
			this->strSizeY = to_string(int(this->size.y)) + "px";
			if (texture.getSize().x != size.x|| texture.getSize().y != size.y) {
				texture.create(size.x, size.y);
			}
	

		}
		Vector2f getMargin() {
			return mar;
		}
		void setMargin(Vector2f mar) {
			this->mar = mar;
		}

	};

	class Clickable: public base {
	public:
		bool ishov, isclicked, selected, chosen,pressed,blockPress;
		MouseInf mouseInf;
		MouseInf localMouseInf;
		InputInfo localInf;
		vector<float> rads = { 0,0,0,0 };
		MouseInf localMouse;

		string input;
		
		typedef void (*onClick)();
		onClick onClickFunction = EmptyFunction;
		bool isPressed() {

			if (ishov && mouseInf.clicked) {
				if (pressed) {
					blockPress = true;
				}
				pressed = true;

			}
			else {
				pressed = false;
				blockPress = false;

			}

			return pressed;

		}
		bool isClicked() {

			if (pressed&&!blockPress) {
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
			if ((((pos.x < mx && mx < pos.x + sx) && (pos.y < my && my < pos.y + sy))&&(!mouseInf.clicked||ishov))&&enabled) {
				ishov = true;
				return ishov;
			}
			else {
				ishov = false;
				return ishov;
			}

		}
		bool isSelected() {
			if (pressed||selected) {
				selected = true;
			}

			if (!mouseInf.clicked) {
				selected = false;

			}

			return selected;

		}
		bool isChosen() {
			if (selected||pressed) {
				chosen = true;

			}
			if (mouseInf.clicked && !(selected || pressed)) {
				chosen = false;

			}
			
			return chosen;

		}
		void updateClickableInfo() {
			isChange = false;
			isChange = ishov != isHover() || isChange;
			isChange = pressed != isPressed() || isChange;
			isChange = isclicked!=isClicked() || isChange;
			isChange = selected!=isSelected() || isChange;
			isChange = chosen!=isChosen() || isChange;
			
		}
	};
	class Texteble {
	public:
		string text, fontName;
		int fontSize;
		Font font;
		Text Text;
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
		bool blockX = false, blockY =  false,firstDrag = true;
		Vector2i correct;
		void drag() {
			if (firstDrag) {
				if (!blockX) {
					correct.x = pos.x - mouseInf.pos.x;
				}
				if (!blockY) {
					correct.y = pos.y - mouseInf.pos.y;
				}
				firstDrag = false;
			}
			if (pressed|| selected) {
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
				firstDrag = true;
			}
		}

	};


	
}