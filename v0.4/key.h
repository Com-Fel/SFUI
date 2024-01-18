#pragma once


#include "UI.h"

using namespace sf;
using namespace std;


namespace basic {
    char keytoch(Event evt) {
        int out;

        if (evt.key.code <= 25) {
            out = evt.key.code + 97;

            if (evt.key.shift) {
                out -= 32;
            }
        }
        else if (evt.key.code <= 35) {
            out = evt.key.code + 22;

        }
        else if (evt.key.code == 57) {
            out = ' ';

        }
        else if (evt.key.code == 58) {
            out = '\n';
        }
        else {
            out = char("");

        }
        return char(out);
    }

    class MouseInf {
    public:
        bool clicked = false;
        bool clickedRight = false;

        int scroll = 0;

        Vector2i pos;
        MouseInf() {}
        MouseInf(Vector2i pos, bool clicked) {
            this->pos.x = pos.x;
            this->pos.y = pos.y;

            this->clicked = clicked;
        }
    };
    class InputInfo {
    public:
        bool rightClickBlock = false;
        string keyboardInput = "";
        MouseInf mouse;
        sf::Event evt;
        vector<int> clickedKeyCodes = {};
        vector<int> releasedKeyCodes = {};
        vector<int> pressedKeyCodes = {};
        vector<bool> blockedClick;
        
        InputInfo() {
            for (int i = 0;i < 100;i++) {
                blockedClick.push_back(false);
            }
        }
        InputInfo(string keyboardInput, MouseInf mouse, sf::Event evt) {
            this->keyboardInput = keyboardInput;
            this->mouse = mouse;
            this->evt = evt;
            for (int i = 0;i < 100;i++) {
                blockedClick.push_back(false);
            }
        }

        void update(Event evt, Vector2i mousePos) {
            mouse.pos = mousePos;
            this->evt = evt;
            releasedKeyCodes = {};
            clickedKeyCodes = {};

            if (evt.type == sf::Event::KeyPressed) {
                if (!blockedClick[evt.key.code]) {
                    clickedKeyCodes.push_back(evt.key.code);
                    blockedClick[evt.key.code] = true;

                }
                if (keyboardInput != "DELETE2") {
                    keyboardInput += keytoch(evt);


                }
                if (evt.key.code == 59) {
                    keyboardInput = "DELETE2";
                }

                bool in = false;
                for (int i = 0;i < pressedKeyCodes.size();i++) {
                    if (pressedKeyCodes[i] == evt.key.code) {
                        in = true;
                    }
                }
                if (!in) {
                    pressedKeyCodes.push_back(evt.key.code);
                }

            }
            if (evt.type == sf::Event::KeyReleased) {

                blockedClick[evt.key.code] = false;

                for (int i = 0;i < pressedKeyCodes.size();i++) {
                    if (evt.key.code == pressedKeyCodes[i]) {
                        pressedKeyCodes.erase(pressedKeyCodes.begin() + i);
                    }

                }
                releasedKeyCodes.push_back(evt.key.code);
                
            }

            if (evt.type == sf::Event::MouseButtonPressed) {
                if (evt.mouseButton.button == sf::Mouse::Left) {
                    mouse.clicked = true;
                }
                if (evt.mouseButton.button == sf::Mouse::Right && !rightClickBlock) {
                    mouse.clickedRight = true;
                    rightClickBlock = true;
                }
            }
            else {
                mouse.clickedRight = false;

            
            }
            if (evt.type == sf::Event::MouseButtonReleased) {
                if (evt.mouseButton.button == sf::Mouse::Left) {
                    mouse.clicked = false;

                }
                if (evt.mouseButton.button == sf::Mouse::Right) {
                    mouse.clickedRight = false;
                    rightClickBlock = false;

                }


            }
            mouse.scroll = 0;

            if (evt.type == sf::Event::MouseWheelScrolled) {
                mouse.scroll = evt.mouseWheelScroll.delta * 5;

            } 



        }
        
    };
    InputInfo inputInfo;

    class KeyCode {
    public:
        const int Q=16,W=22,E=4,R=17,T=19,Y=24,U=20,I=8,O=14,P=15,A=0,S=18,
                  D=3,F=5,G=6,H=7,J=9,K=10,L=11,Z=25,X=23,C=2,V=21,B=1,N=13,M=12,
                  _0=26,_1=27,_2=28,_3=29,_4=30,_5=31,_6=32,_7=33,_8=34,_9=35,
                  SHIFT=38,R_SHIFT=42,CTRL=37,R_CTRL=41,TAB=60,ENTER=58,BACKSPACE=59,ESC=36,
                  SPACE=57,ALT=39,R_ALT=43,WIN=40,INS=65,HOME=64,END=63,DEL=66,
                  PAGE_UP=61,PAGE_DOWN=62,ARROW_L=71,ARROW_R=72,ARROW_U=73,ARROW_D=74,
                  F1=85,F2=86,F3=87,F4=88,F5=89,F6=90,F7=91,F8=92,F9=93,F10=94,F11=95,F12=86,
                  NUM_0=75,NUM_1=76,NUM_2=77,NUM_3=78,NUM_4=79,NUM_5=80,NUM_6=81,NUM_7=82,NUM_8=83,NUM_9=84;

    }; 

    KeyCode keyCode;

}
