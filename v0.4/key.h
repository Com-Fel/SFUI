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
         
        string keyboardInput = "";
        MouseInf mouse;
        sf::Event evt;
        InputInfo() {  }
        InputInfo(string keyboardInput, MouseInf mouse, sf::Event evt) {
            this->keyboardInput = keyboardInput;
            this->mouse = mouse;
            this->evt = evt;
        }

        void update(Event evt, Vector2i mousePos) {
            mouse.pos = mousePos;
            this->evt = evt;
            if (evt.type == sf::Event::KeyPressed) {
                if (keyboardInput != "DELETE2") {
                    keyboardInput += keytoch(evt);


                }
                if (evt.key.code == 59) {
                    keyboardInput = "DELETE2";
                }
            }
            if (evt.type == sf::Event::MouseButtonPressed) {
                if (evt.mouseButton.button == sf::Mouse::Left) {
                    mouse.clicked = true;
                }

            }
            if (evt.type == sf::Event::MouseButtonReleased) {
                if (evt.mouseButton.button == sf::Mouse::Left) {
                    mouse.clicked = false;
                }
            }
            mouse.scroll = 0;

            if (evt.type == sf::Event::MouseWheelScrolled) {
                mouse.scroll = evt.mouseWheelScroll.delta * 5;

            }



        }
        
    };
}