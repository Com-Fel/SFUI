#pragma once

#include "UI.h"

using namespace std;

using namespace sf;

namespace UI {

	class ContextMenuStyle: public Style{
	public:
		ButtonStyle buttonStyle;
		int buttonWidth;
		int buttonLength;
		int borderSize;
		Color borderColor;
		ContextMenuStyle(){}
		ContextMenuStyle(int buttonWidth,int buttonLength, int borderSize,Color borderColor,ButtonStyle buttonStyle) {
			this->buttonStyle = buttonStyle;
			this->buttonWidth = buttonWidth;
			this->buttonLength = buttonLength;
			this->borderSize = borderSize;

			this->borderColor = borderColor;
		}
	};


	class ContextMenu :public Clickable, public Colored {
	public:
		vector<Button*> buttons;
		ContextMenuStyle style;
		ContextMenu(){}
		ContextMenu(Vector2f pos, ContextMenuStyle style){
			this->pos = pos;
			this->style = style;
			this->style.buttonStyle = style.buttonStyle;
			texture.create(style.buttonWidth, 100);
		
		}
		void init(Vector2f pos, ContextMenuStyle style) {
			this->pos = pos;
			this->style = style;
			this->style.buttonStyle = style.buttonStyle;
			texture.create(style.buttonWidth+ style.borderSize, 100);

		}
		void hide() {
			texture.clear(Color(0, 0, 0, 0));
			
		}
		void show(vector<string> var) {
			buttons = {};
			for (int i = 0;i < var.size();i++) {
				buttons.push_back(new Button(Vector2f(style.borderSize,i* style.buttonLength+ (style.borderSize*int(i==0))-style.buttonStyle.bord * i),Vector2f(style.buttonWidth, style.buttonLength), style.buttonStyle,var[i],var[i]));
				texture.create(style.buttonWidth + style.borderSize*2, style.buttonLength* var.size() + style.borderSize - style.buttonStyle.bord * i);

			}
			cout << "a";
		}
		Sprite update(InputInfo inf) {
			this->mouseInf = inf.mouse;

			localMouse.pos.x = inf.mouse.pos.x - pos.x ;
			localMouse.pos.y = inf.mouse.pos.y - pos.y;
			localMouse.clicked = inf.mouse.clicked;

			input = inf.keyboardInput;
			localInf.update(inf.evt, localMouse.pos);
			localInf.keyboardInput = inf.keyboardInput;
			updateClickableInfo();
			draw();

			const Texture& out = texture.getTexture();

			sprite.setTexture(out);
			sprite.setPosition(pos);
			return sprite;
		}
		void draw() {
			texture.clear(style.borderColor);
			for (int i = 0;i < buttons.size();i++) {
				texture.draw(buttons[i]->update(localInf));
			}
			texture.display();

		}

	};
	class ContextMenuRenderer :public base {
	public:
		ContextMenu menu;
		ContextMenuStyle style;

		bool activeMenu = false;
		ContextMenuRenderer(Vector2f size, ContextMenuStyle style) {
			this->size = size;
			this->style = style;
			menu.init(Vector2f(100, 100), style);
			texture.create(size.x, size.y);
		}
		Sprite update(InputInfo inf) {

			if (inf.mouse.clickedRight) {
				activeMenu = true;
				menu.init(Vector2f(inf.mouse.pos.x, inf.mouse.pos.y), style);
				menu.show({"Create new","Delete","Save file","Create new file","Close window"});
				

			}
			if (inf.mouse.clicked) {
				activeMenu = false;

			}


			if (activeMenu) {
				menu.update(inf);
			}
			else {
				menu.hide();
			}
			draw();

			const Texture& out = texture.getTexture();

			sprite.setTexture(out);
			return sprite;
		}
		void draw() {
			texture.clear(Color(0, 0, 0, 0));
			texture.draw(menu.sprite);
			texture.display();

		}
	};
}