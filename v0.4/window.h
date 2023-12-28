#pragma once

#include "UI.h"

using namespace std;

using namespace sf;

namespace UI {
	
	class LocalWindowStyle : public Style {
	public:
		string fontName;
		int fontSize; 
		vector<vector<Color>> colors;
		ButtonStyle closeStyle;
		ButtonStyle hideStyle;
		LocalWindowStyle(){}
		LocalWindowStyle(string fontName, int fontSize, vector<vector<Color>> colors, ButtonStyle closeStyle, ButtonStyle hideStyle) {
			this->fontName = fontName;
			this->fontSize = fontSize;
			this->colors = colors;
			this->closeStyle = closeStyle;
			this->hideStyle = hideStyle;
		}
	};

	class LocalWindow:public Colored, public Dragable{
	public:
		int topMenuSize = 20;

		int margin = 1;
		int buttonMargin = margin;

		Group topMenu;
		Group workSpace;
		Group MainGroup;

		Label name;
		Button close, hide;
		
		string windowName;
		LocalWindowStyle style;

		LocalWindow(Vector2f pos, Vector2f size, string name, LocalWindowStyle style) {
			this->pos = pos;
			this->size = size;
			this->colors = style.colors;
			this->windowName = name;
			this->style = style;



			init(style);
		}
		LocalWindow(Vector2f pos, Vector2f size,string name,string fontName,int fontSize,vector<vector<Color>> colors, ButtonStyle closeStyle, ButtonStyle hideStyle) {
			this->pos = pos;
			this->size = size;
			this->colors = colors;
			this->windowName = name;

			style.fontName = fontName;
			style.fontSize = fontSize;
			style.colors = colors;
			style.closeStyle = closeStyle;
			style.hideStyle = hideStyle;

			

			init(style);



		}
		void init(LocalWindowStyle style) {
			LabelStyle st(Vector2f(0,0), { { colors[2]} }, style.fontName, style.fontSize);
			name.Create(Vector2f(margin + 5, 0),st, windowName);
			//this->name.fontName = style.fontName;
			//this->name.fontSize = style.fontSize;
			//this->name.colors = { { colors[2]} };
			//this->name.setText(windowName);
			//this->name.setPos();


			topMenu.setSize(Vector2f(size.x, topMenuSize));
			topMenu.setPos(Vector2f(0, 0));
			topMenu.colors = { { colors[1][0] } };


			workSpace.setSize(Vector2f(size.x - margin * 2, size.y - margin));
			workSpace.setPos(Vector2f(margin, topMenuSize));
			workSpace.colors = { { colors[0][0] } };


			close.Create(Vector2f(size.x - topMenuSize, 1), Vector2f(topMenuSize - 2, topMenuSize - 2), style.closeStyle, "close", "x");
			hide.Create(Vector2f(size.x - topMenuSize * 2, 1), Vector2f(topMenuSize - 2, topMenuSize - 2), style.hideStyle, "hide", "-");
			topMenu.append(&name);
			topMenu.append(&close);
			topMenu.append(&hide);


			MainGroup.setSize(Vector2f(size.x, size.y + topMenuSize));
			MainGroup.append(&topMenu);
			MainGroup.append(&workSpace);

			texture.create(size.x, size.y + topMenuSize);
			


		}
		Sprite update(InputInfo inf) {

			this->mouseInf = inf.mouse;
			localMouseInf.pos.x = inf.mouse.pos.x - pos.x ;
			localMouseInf.pos.y = inf.mouse.pos.y - pos.y ;
			localMouseInf.clicked = inf.mouse.clicked;
			localInf.update(inf.evt, localMouseInf.pos);
			localInf.keyboardInput = inf.keyboardInput;

			MainGroup.enabled = enabled;
			updateClickableInfo();

			if (topMenu.selected) {
				drag();
			}
			

			if (chosen) {
				Zpos = 0;
			}

			draw();
			const sf::Texture& out = texture.getTexture();

			Sprite sprite(out);
			sprite.setPosition(pos);
			return sprite;
		}
		void draw() {

			topMenu.colors = { {colors[0][int(chosen)]} };
			workSpace.colors = { {colors[1][int(chosen)]} };

			texture.clear(colors[3][int(chosen)]);
			texture.draw(MainGroup.update(localInf));

			texture.display();


		}
		template<typename elem>
		void append(elem el) {
			workSpace.append(el);
		}
	};


	class WindowsRenderer:public Clickable {
	public:
		vector<LocalWindow*> windows;



		WindowsRenderer(Vector2f size){
			this->size = size;
			this->pos = Vector2f(0, 0);
			texture.create(size.x, size.y);
		}
		void createNewWindow(Vector2f pos, Vector2f size, string name, LocalWindowStyle style) {
			windows.push_back(new LocalWindow(pos, size, name, style));
			windows[windows.size() - 1]->Zpos = windows.size() - 1;
		}
	
		void update(InputInfo inf) {
			this->localInf = inf;

			


			for (int i = 0;i < windows.size();i++) {
				if (windows[i]->topMenu.buttons[0]->isclicked) {
					//delete windows[i]; // =========================================================================ERROR
					windows.erase(windows.begin()+i);
					for (int j = i;j < windows.size();j++) {
						windows[j]->Zpos--;
					}
				}
			}
			bool canSelected = true;
			for (int i = 0;i <windows.size();i++) {
				windows[i]->enabled = canSelected;
				if (windows[i]->ishov) {
					canSelected = false;
				}
			}
			sort();
			draw();


			const sf::Texture& out = texture.getTexture();
			sprite.setTexture(out);
			sprite.setPosition(pos);

		}
		void draw(){
			texture.clear(Color(0,0,0,0));
			
			for (int i = windows.size()-1;i >=0 ;i--) {
				

				texture.draw(windows[i]->update(localInf));
				

			}
			texture.display();
		}
		void sort() {
			for (int i = 1;i < windows.size();i++) {
				if (windows[i]->Zpos == 0) {
					
					vector<LocalWindow*> TempWindows = windows;
					for (int j = 0;j < windows.size();j++) {
						if (j<i) {
							windows[j]->Zpos++;
						}

						TempWindows[windows[j]->Zpos] = windows[j];
					}
					windows[0] = windows[i];
					windows = TempWindows;

				}
			}

		}

	};

}