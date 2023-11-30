#pragma once

#include<iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
namespace parser {
    class Event {
    public:
        string name;
        string comment;
        int startTime;
        int duration;
        vector<string> images;
        vector<string> keysImages;

        int importance;
        int r;
        int g;
        int b;
        Event(string name, string comment, int startTime, int duration, vector<string> images, vector<string> keysImages, int importance, vector<int> color) {
            this->name = name;
            this->comment = comment;
            this->startTime = startTime;
            this->duration = duration;
            this->images = images;
            this->keysImages = keysImages;

            this->importance = importance;
            this->r = color[0];
            this->g = color[1];
            this->b = color[2];
        }
        Event() {}


    };
    class Calendar {
    public:
        string name;
        vector<Event> Events;
        int r;
        int g;
        int b;
        vector<string> users;
        Calendar() {}
        Calendar(vector<Event> Events, vector<string> users, string name, vector<int> color) {
            this->Events = Events;
            this->r = color[0];
            this->g = color[1];
            this->b = color[2];
            this->users = users;
            this->name = name;
        }
    };

    //vector<string> readLine(string *text, int i) {

    //}

    string readStr(string text, int& i) {

        string temp;
        i++;
        while (text[i] != ';') {
            temp += text[i];
            i++;
        }

        return temp;

    }
    int readInt(string text, int& i) {

        string temp;
        i++;
        while (text[i] != ';') {
            temp += text[i];
            i++;


        }

        return stoi(temp);

    }

    vector<string> readStrArray(string text, int& i) {

        string temp;
        vector<string> out;
        i++;
        while (true) {
            if (text[i] != ';') {

                while (text[i] != ',' && text[i] != ';') {

                    temp += text[i];


                    i++;

                }
                if (text[i] != ';') {
                    i++;
                }
                out.push_back(temp);
                temp = "";

            }
            else {
                return out;

            }
        }



    }
    vector<int> readIntArray(string text, int& i) {


        string temp;
        vector<int> out;
        i++;
        while (true) {
            if (text[i] != ';') {

                while (text[i] != ',' && text[i] != ';') {

                    temp += text[i];


                    i++;

                }
                if (text[i] != ';') {
                    i++;
                }
                out.push_back(stoi(temp));
                temp = "";

            }
            else {
                return out;

            }
        }

    }


    Event parseEvent(string text) {

        string Qname, Qcomment;
        int QstartTime, Qduration, Qimportance;
        vector<string> Qimages;
        vector<string> QkeysImages;
        vector<int> color;

        string temp;


        int i = 0;

        Qname = readStr(text, i);
        Qcomment = readStr(text, i);
        QstartTime = readInt(text, i);
        Qduration = readInt(text, i);
        Qimages = readStrArray(text, i);
        QkeysImages = readStrArray(text, i);
        Qimportance = readInt(text, i);
        color = readIntArray(text, i);

        return Event(Qname, Qcomment, QstartTime, Qduration, Qimages, QkeysImages, Qimportance, color);

    }
    Calendar parseCalendar(string filename) {

        ifstream in(filename);
        string text, line;

        int tempI = 0;


        vector<Event> Events;
        vector<string> users;
        string temp;
        int Cr, Cg, Cb, i;
        string Cname;
        vector<int> color;
        if (in.is_open())
        {
            while (getline(in, line))
            {
                for (int i = 0;i < line.length(); i++) {
                    if (line[i] != ' ') {
                        text += line[i];
                    }
                }


            }
        }


        in.close();


        vector<string> tempText;

        for (int i = 0;i < text.length();i++) {
            if (text[i] != ']') {
                if (text[i] != '[') {
                    temp += text[i];
                }

            }
            else {
                tempText.push_back(temp);
                temp = "";
            }
        }

        i = 0;

        Cname = readStr(tempText[0], i);
        users = readStrArray(tempText[0], i);
        color = readIntArray(tempText[0], i);


        for (int k = 1;k < tempText.size();k++) {


            Events.push_back(parseEvent(tempText[k]));
        }

        return Calendar(Events, users, Cname, color);

    }


}