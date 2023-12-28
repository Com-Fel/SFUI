#pragma once
#include<iostream>
#include <fstream>
#include <string>
#include <vector>

class KeyValue {
public:
    string key;
    string value;
};


class RawStyle {
public:
    RawStyle(string styleName,string styleType,vector<KeyValue> keyValue) {
        this->styleName = styleName;
        this->styleType = styleType;
        this->keyValue = keyValue;
    }

    string styleName;
    string styleType;
    vector<KeyValue> keyValue;
};


string readFile(string filename) {
    ifstream in(filename);
    string text, line;

    if (in.is_open())
    {
        while (getline(in, line))
        {
            for (int i = 0;i < line.length(); i++) {
                if (line[i] != ' ' && line[i] != '	') {
                    text += line[i];
                    
                }
            }


        }
    }
    return text;
}


vector<string> divideBlocks(string text) {
    string temp;
    vector<string> out;

    for (int i = 0;i < text.size();i++) {
        temp += text[i];
        if (text[i] == '}') {
            out.push_back(temp);
            temp = "";
        }
    }
    return out;
}


string readFromTo(string inp, char a, char b) {
    bool write = false;
    if (a == '^') {
        write = true;
    }
    string out;
    

    for (int i = 0;i < inp.size();i++) {
        if (inp[i] == b) {

            return out;

        }
        if (write) {
            out += inp[i];
        }
        if (inp[i] == a) {
            write = true;
        }
       
    }
}


KeyValue readString(string inp) {
    KeyValue out;
    string temp;
    int j;
    for (int i = 0;i < inp.size();i++) {
        if (inp[i] != '=') {
            temp += inp[i];
        }
        else {
            j = i+1;
            break;
        }
    }
    out.key = temp;
    temp = "";

    for (int i = j;i < inp.size();i++) {
        temp += inp[i];        
    }
    out.value = temp;
    return out;

}

vector<KeyValue> ConvertTokeyValueVector(string inp) {
    string temp;
    vector<KeyValue> out;
    for (int i = 0;i < inp.size();i++) {
        if (inp[i] != ','&& inp[i] != ';') {
            temp += inp[i];
        }
        else {
            out.push_back(readString(temp));
            temp = "";
        }
    }
    return out;
}

RawStyle getRaw(string inp) {
    string styleType = readFromTo(inp, '^', '@');
    string name = readFromTo(inp, '@', '{');
    string rdata = readFromTo(inp, '{', '}');
  
    vector<KeyValue> data = ConvertTokeyValueVector(rdata);
    RawStyle out(name, styleType, data);
    return out;
}

vector<RawStyle> getRawStyleVector(vector<string> inp) {
    vector<RawStyle> out;
    for (int i = 0;i < inp.size();i++) {
        out.push_back(getRaw(inp[i]));
    }
    return out;
}


/*
 button@style-name{	
    fontname="example.ttf",
    fontsize=12,
    textcolor=(255-255-255),
}

button@style-name:hover{

}

button@style-name:clicked{

}
*/