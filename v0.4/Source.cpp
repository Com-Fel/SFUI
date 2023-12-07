
#include "SFUI/UI.h"



using namespace std;
using namespace sf;
using namespace UI;



int main() {
    setlocale(LC_ALL, "Russian");
    //Calendar c = parseCalendar("Calendar.hl");
    //cout << c.Events[0].images[0];   
    vector<vector<Color>> butC = { { Color(0,0,0),Color(50,50,50),Color(75,75,75)    },
                                   { Color(255,255,255), Color(0,255,0),Color(0,0,0) },
                                   { Color(255,255,255), Color(0,255,0),Color(0,0,0) } };

    vector<vector<Color>> butC2 = {{ Color(255,255,255),Color(0,0,0),Color(100,0,0) },
                                   { Color(0,0,0), Color(255,255,255),Color(50,0,0) },
                                   { Color(0,0,0), Color(255,255,255),Color(50,0,0) }  };

    RenderWindow window(VideoMode(800, 600), "SFMLworks");
    window.setFramerateLimit(60);
    ButtonStyle StButton(butC, 1,Vector2f(30,10),20, "arial.ttf");

    Swither sw(Vector2f(100, 0), Vector2f(100, 100), Vector2f(20, 35), 5,  butC ,20,"arial.ttf","","Switch");
    Button b(Vector2f(100, 50), Vector2f(100, 100), Vector2f(20, 35), 5, butC, 20, "arial.ttf", "", "Button");

    Button b2(Vector2f(150, 50), Vector2f(100, 45), StButton, "", "But2");
    Button b3(Vector2f(205, 100), Vector2f(100, 50), Vector2f(30, 10), 3, butC2, 20, "arial.ttf", "", "But3");
    Label l(Vector2f(100, 0), Vector2f(20, 10), {Color(255,255,255),Color(0,0,0,100)}, "arial.ttf",20,"vaav");
    ImageBox banan(Vector2f(350, 100), Vector2f(100, 100),"images/banan.png");
    Group gr(Vector2f(200, 100), Vector2f(300, 300), Color(0, 0, 0, 100));

    Textbox tb(Vector2f(100, 200), Vector2f(100, 50),"Input...", 3, 2, { {Color(150,150,150),Color(255,255,255),Color(50,50,150),Color(0,0,0),Color(150,150,150)} , {Color(200,200,200),Color(255,255,255),Color(0,0,255),Color(0,0,0)} }, "arial.ttf", 15);
    Textbox tb2(Vector2f(200, 200), Vector2f(100, 50), "Input...", 3, 2, { {Color(150,150,150),Color(255,255,255),Color(50,50,150),Color(0,0,0),Color(150,150,150)} , {Color(200,200,200),Color(255,255,255),Color(0,0,255),Color(0,0,0)} }, "arial.ttf", 15);

    banan.setPos(Vector2f(0, 0));
    gr.append(&b2);
    gr.append(&l);
    gr.append(&banan);
    gr.append(&tb);
    gr.append(&tb2);


    Font font;
    Text text;
    
    font.loadFromFile("arial.ttf");
    text.setString("Hello world");
    text.setFont(font);
    text.setCharacterSize(24); 
    
    bool clicked = false;

// set the color
    text.setFillColor(sf::Color::Red);

    vector<float> rads = { 0.1,0.5,2,1,0,12.98 };
    
    Slider sl(Vector2f(0, 300), 50, 0, 255, 2, 4, { {Color(75,75,75)},{Color(0,0,0),Color(150,150,150),Color(200,200,200)} }, true, true);
    InputInfo inputInfo;
    BaseShape test(Vector2f(250, 200), { 25,25,50,50 }, Color::Black);
    Sprite t = test.create();
    t.setPosition(200,50);
    TransformableObject tr(Vector2f(100,100), Vector2f(100, 100));
    RectangleShape pix;
    pix.setSize(Vector2f(1, 1));
  
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
        l.text = to_string(sl.value);
        
        gr.offset.x = sl.value;
        window.clear(Color(200, 200, 255));
        window.draw(gr.update(inputInfo));
        window.draw(sl.update(inputInfo.mouse));
        window.draw(sw.update(inputInfo.mouse));
        window.draw(tr.update(inputInfo.mouse));

       // window.draw(t);
        window.display();

    }
    return 0;
}


