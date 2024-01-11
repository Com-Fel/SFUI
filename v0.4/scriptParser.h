#pragma once
#include<iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;



class Function {
public:
    string key;
    typedef void (*onClick)();
    onClick value;
    Function(string key, onClick onClick) {
        this->key = key;
        this->value = onClick;

    }
    

};
vector<Function> functionsDictionary;


Function findFunction(string key, vector<Function> inp) {
    for (int i = 0;i < inp.size();i++) {
        if (inp[i].key == key) {
            return inp[i];
        }

    }
}



string readFileWithSpaces(string filename) {
    ifstream in(filename);
    string text, line;
    if (in.is_open())
    {
        while (getline(in, line))
        {
            for (int i = 0;i < line.length(); i++) {
               

               text += line[i];

                

            }
            text += '\n';

        }
    }
    return text;
}

string readLast(string inp,int count) {
    string out;
    if (count > inp.size()) {
        count = inp.size();
    }
    for (int i = 0;i < count;i++) {
        out = inp[inp.size() - i - 1] + out;
    }

    return out;
}

string parseScript(string filename) {
    string text = readFileWithSpaces(filename);
    ofstream out("SFUI/userScript.h");

    string dictionary = "void loadChanges(){\n	functionsDictionary = {",temp;

    bool readName = false;

    for (int i = 0;i < text.size();i++) {
        if (text[i] != ' ' && text[i] != '	'&& text[i] !=  '(') {
            temp += text[i];
        }
        if (readLast(temp,4) == "void") {
            readName = true;
            temp = "";
        }
        if (readName) {
            if (text[i] == '(') {
                dictionary += "Function(\"" + temp + "\", &" + temp + "),";
                temp = "";
                readName = false;
            }
           
        }
    }
   
    dictionary = dictionary.substr(0, dictionary.size() - 1);
    dictionary += "};\n}";
    if (out.is_open()) {
        out << text << endl;
        out << dictionary;
    }
   
    out.close();
    return readFileWithSpaces("SFUI/userScript.h");
}
