#include<iostream>
#include <fstream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include "UI.h"



using namespace std;
using namespace sf;
using namespace UI;

int main() {
    setlocale(LC_ALL, "Russian");
    //Calendar c = parseCalendar("Calendar.hl");
    //cout << c.Events[0].images[0];   
    vector<vector<Color>> butC = { { Color(0,0,0),Color(50,50,50),Color(75,75,75) },
                                   { Color(255,255,255), Color(0,255,0),Color(0,0,0) },
                                   { Color(255,255,255), Color(0,255,0),Color(0,0,0) } };

    vector<vector<Color>> butC2 = {{ Color(255,255,255),Color(0,0,0),Color(100,0,0) },
                                   { Color(0,0,0), Color(255,255,255),Color(50,0,0) },
                                   { Color(0,0,0), Color(255,255,255),Color(50,0,0) } };

    RenderWindow window(VideoMode(500, 500), "SFMLworks");
    window.setFramerateLimit(60);


    Button b(Vector2f(100, 50), Vector2f(100, 100), Vector2f(20, 35), 5,  butC ,20,"arial.ttf","","Button");
    Button b2(Vector2f(205, 50), Vector2f(100, 45), Vector2f(30, 10), 3, butC, 20, "arial.ttf", "", "But2");
    Button b3(Vector2f(205, 100), Vector2f(100, 50), Vector2f(30, 10), 3, butC2, 20, "arial.ttf", "", "But3");
    Label l(Vector2f(100, 0), Vector2f(20, 10), {Color(255,255,255),Color(0,0,0,100)}, "arial.ttf",20,"vaav");
    ImageBox banan(Vector2f(350, 100), Vector2f(100, 100),"images/banan.jpg");
    Textbox tb(Vector2f(100, 200), Vector2f(100, 50),"Input...", 3, 2, { {Color(150,150,150),Color(255,255,255),Color(50,50,150),Color(0,0,0),Color(150,150,150)} , {Color(200,200,200),Color(255,255,255),Color(0,0,255),Color(0,0,0)} }, "arial.ttf", 15);
    Group gr(Vector2f(50,100), Vector2f(300,300),Color(0,0,0,100));


    banan.setPos(Vector2f(0, 0));
    gr.append(&b);
    gr.append(&l);
    gr.append(&banan);
    gr.append(&tb);

    Font font;
    Text text;
    
    font.loadFromFile("arial.ttf");
    text.setString("Hello world");
    text.setFont(font);
    text.setCharacterSize(24); 
    
    bool clicked = false;
// set the color
    text.setFillColor(sf::Color::Red);

    RectangleShape s;


    InputInfo inputInfo;
    while (window.isOpen())
    {
        string inp = "";
        
        sf::Event evt;
        inputInfo.keyboardInput = "";

        while (window.pollEvent(evt))

        {
            if (evt.type == sf::Event::Closed) {

                window.close();
            }
            inputInfo.update(evt, Mouse::getPosition(window));
            
        }
        window.clear(sf::Color::Red);
       // cout << Mouse::getPosition(window).x << " " << Mouse::getPosition(window).y << endl;
        window.draw(gr.update(inputInfo));
       
 
        window.display();

    }
    return 0;
}