#pragma once
#include "UI.h"



using namespace std;
using namespace sf;
using namespace basic;


namespace UI {
	class StyleSheet {
	public:
		string name;
		Vector2f mar = Vector2f(0, 0);
		int bord = 1, fontSize = 12, bordIn = 1;
		vector<vector<Color>> colors = { { Color(25,25,25)    ,Color(100,100,100)  ,Color(120,120,120),Color(0,0,255) },
										 { Color(150,150,150) ,Color(150,150,150)  ,Color(150,150,150),Color(0,0,255)},
										 { Color(255,255,255) ,Color(255,255,255)  ,Color(255,255,255) ,Color(0,0,255) },
										 { Color(150,150,150) ,Color(150,150,150)  ,Color(150,150,150),Color(0,0,255)}, };
		string fontName = "arial.ttf";
		vector<float> rads = { 0,0,0,0 };
		StyleSheet() {}
		StyleSheet(string name,vector<vector<Color>> colors, int bord, Vector2f mar, int fontSize, string fontName, vector<float> rads) {
			this->bord = bord;
			this->colors = colors;
			this->fontSize = fontSize;
			this->fontName = fontName;
			this->mar = mar;
			this->rads = rads;
			this->name = name;

		};
		StyleSheet(RawStyle Rstyle) {
			name = Rstyle.styleName;

			for (int i = 0;i < Rstyle.keyValue.size();i++) {

				string key = Rstyle.keyValue[i].key;
				string value = Rstyle.keyValue[i].value;


				if (key == "font-name") {
					fontName = value;
				}
				if (key == "font-size") {
					fontSize = stoi(value);
				
				}

				

				if (key == "background-color") {
					colors[0][0] = getColorFromString(value);
					colors[0][1] = getColorFromString(value);
					colors[0][2] = getColorFromString(value);
				}
				if (key == "hover:background-color") {
					colors[0][1] = getColorFromString(value);
				}
				if (key == "clicked:background-color") {
					colors[0][2] = getColorFromString(value);
				}

				if (key == "border-color") {
					colors[1][0] = getColorFromString(value);
					colors[1][1] = getColorFromString(value);
					colors[1][2] = getColorFromString(value);

				}
				if (key == "hover:border-color") {
					colors[1][1] = getColorFromString(value);
				}
				if (key == "clicked:border-color") {
					colors[1][2] = getColorFromString(value);
				}


				if (key == "text-color") {
					colors[2][0] = getColorFromString(value);
					colors[2][1] = getColorFromString(value);
					colors[2][2] = getColorFromString(value);

				}
				if (key == "hover:text-color") {
					colors[2][1] = getColorFromString(value);
				}
				if (key == "clicked:text-color") {
					colors[2][2] = getColorFromString(value);
				}

				

			}


		}

	};

	class StyleSheets {
	public:
		vector<StyleSheet*> styles;


		StyleSheets(string path) {
			vector<RawStyle> inp = getRawStyleVector(divideBlocks(readFile(path)));
			for (int i = 0;i < inp.size();i++) {
				styles.push_back(new StyleSheet(inp[i]));
			}
		}
		StyleSheet getStyle(string stylename) {
			for (int i = 0;i < styles.size();i++) {
				
				if (styles[i]->name == stylename) {
					
					return *styles[i];
				}
			}
		}


	};


}
