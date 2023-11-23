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
    Label l(Vector2f(350, 50), Vector2f(20, 10), {Color(255,255,255),Color(0,0,0,100)}, "arial.ttf",20,"vaav");
    ImageBlock banan(Vector2f(350, 100), Vector2f(100, 100),"images/banan.jpg");
    Textbox tb(Vector2f(100, 200), Vector2f(100, 50), 3, 2, { {Color(150,150,150),Color(255,255,255),Color(50,50,150),Color(0,0,0)} , {Color(200,200,200),Color(255,255,255),Color(0,0,255),Color(0,0,0)} }, "arial.ttf", 15);


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
    while (window.isOpen())
    {
        string inp = "";

        sf::Event evt;
        while (window.pollEvent(evt))

        {
            if (evt.type == sf::Event::Closed) {

                window.close();
            }
            if (evt.type == sf::Event::KeyPressed) {
                if (inp != "DELETE2") {
                    inp += keytoch(evt);

                    
                }
                if (evt.key.code == 59) {
                    inp = "DELETE2";
                }
            }
            if (evt.type == sf::Event::MouseButtonPressed) {
                if (evt.mouseButton.button == sf::Mouse::Left) {
                    clicked = true;
                }
                
            }
            if (evt.type == sf::Event::MouseButtonReleased) {
                if (evt.mouseButton.button == sf::Mouse::Left) {
                    clicked = false;
                }
            }
            
        }
        
        window.clear(sf::Color::Red);
       // cout << Mouse::getPosition(window).x << " " << Mouse::getPosition(window).y << endl;
       
        // draw it to the window

        window.draw(banan.update());
        

        window.draw(b.update(Mouse::getPosition(window), clicked));
        window.draw(b2.update(Mouse::getPosition(window), clicked));
        
        window.draw(b3.update(Mouse::getPosition(window), clicked));
        window.draw(l.update());
        window.draw(tb.update(Mouse::getPosition(window), clicked,inp));
        window.display();

    }
    return 0;
}