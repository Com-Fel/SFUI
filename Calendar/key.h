#pragma once


#include<iostream>
#include <fstream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

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