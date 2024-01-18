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
    string styleName;
    string styleType;
    vector<KeyValue> keyValue;
    RawStyle(){}
    RawStyle(string styleName,string styleType,vector<KeyValue> keyValue) {
        this->styleName = styleName;
        this->styleType = styleType;
        this->keyValue = keyValue;
    }

    
};




string readFile(string filename) {
    ifstream in(filename);
    string text, line;
    bool isText = false;
    if (in.is_open())
    {
        while (getline(in, line))
        {
            for (int i = 0;i < line.length(); i++) {
                if (line[i] == '"' ) {
                    isText = !isText;
                }
                
                else if ((line[i] != ' ' && line[i] != '	') || isText) {

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
    if (a == '|') {
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
    return out;
}
string readFromToInd(string inp, int a, int b) {
   
    string out;


    for (int i = a;i < b;i++) {
        out += inp[i];

    }
    return out;
}


KeyValue readString(string inp) {
    KeyValue out;
    string temp;
    int j;
    for (int i = 0;i < inp.size();i++) {
        if (inp[i] != '='&&inp[i]!='"') {
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
    if (!temp.empty()) {
        out.push_back(readString(temp));
        temp = "";
    }
    return out;
}

RawStyle getRaw(string inp) {
    
    string name = readFromTo(inp, '|', '{');
    string rdata = readFromTo(inp, '{', '}');

    vector<KeyValue> data = ConvertTokeyValueVector(rdata);
    RawStyle out(name, "StyleSheet", data);
    return out;
}

vector<RawStyle> getRawStyleVector(vector<string> inp) {
    vector<RawStyle> out;
    for (int i = 0;i < inp.size();i++) {
        out.push_back(getRaw(inp[i]));
    }
    return out;
}

Color getColorFromString(string st) {
    
    string temp;
    int r = -1, g = -1, b = -1;

    
    for (int i = 1;i < st.size();i++) {
        if (st[i] != '-'&&st[i]!=')') {
            temp += st[i];
        }
        else {
            if (r == -1) {
                r = stoi(temp);
                temp = "";
            }
            else if (g == -1) {
                g = stoi(temp);
                temp = "";
            }
            else if (b == -1) {
                b = stoi(temp);
                temp = "";
            }
        }
    }
    if (!temp.empty()) {
        b = stoi(temp);
        temp = "";
    }
    return Color(r,g,b);
}

