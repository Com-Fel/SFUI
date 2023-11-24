#pragma once


#include<iostream>
#include <fstream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "basic.h"

using namespace sf;
using namespace std;



char keytoch(Event evt) {
    int out;
    
    if (evt.key.code <= 25) {
        out = evt.key.code + 97;

        if (evt.key.shift) {
            out -= 32;
        }
    }
    else if (evt.key.code <= 35) {
        out =  evt.key.code + 22;

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
class InputInfo {
public:
    string keyboardInput = "";
    MouseInf mouse;

    InputInfo(){}
    
    
    void update(Event evt, Vector2i mousePos) {
        mouse.pos = mousePos;

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
    }

};