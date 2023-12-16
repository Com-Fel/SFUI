
#include "SFUI/UI.h"



using namespace std;
using namespace sf;
using namespace UI;



int main() {
    setlocale(LC_ALL, "Russian");
    //Calendar c = parseCalendar("Calendar.hl");
    //cout << c.Events[0].images[0];   
    vector<vector<Color>> butC = { { Color(150,50,70),Color(200,0,0),Color(255,0,0)    },
                                   { Color(100,0,0), Color(150,0,0),Color(200,0,0) },
                                   { Color(255,255,255), Color(255,255,255),Color(255,255,255) } };

    vector<vector<Color>> butC2 = { { Color(150,150,70),Color(200,200,0),Color(255,255,0)    },
                                    { Color(100,100,0), Color(150,150,0),Color(200,200,0) },
                                    { Color(255,255,255), Color(255,255,255),Color(255,255,255) } };


    ContextSettings settings;
    settings.antialiasingLevel = 0;

 

    RenderWindow window(VideoMode(800, 600), "SFMLworks", Style::Default, settings);
    window.setFramerateLimit(60);



    ButtonStyle close(butC, 2, Vector2f(6, -1), 17, "arial.ttf", {5,5,5,5 });
    ButtonStyle hide(butC2, 2, Vector2f(6, -1), 17, "arial.ttf", { 5,5,5,5 });

    Switcher sw(Vector2f(100, 0), Vector2f(100, 100), Vector2f(20, 35), 5,  butC ,20,"arial.ttf","","Switch");
    Button b(Vector2f(100, 50), Vector2f(50, 30), close, "", "test");
    Label l(Vector2f(100, 0), Vector2f(20, 10), {Color(255,255,255),Color(0,0,0,100)}, "arial.ttf",20,"vaav");
    ImageBox banan(Vector2f(350, 100), Vector2f(100, 100),"images/banan.png");
    Group gr(Vector2f(200, 100), Vector2f(300, 300), Color(0, 0, 0, 100));

    Textbox tb(Vector2f(100, 200), Vector2f(100, 50),"Input...", 3, 2, { {Color(150,150,150),Color(255,255,255),Color(50,50,150),Color(0,0,0),Color(150,150,150)} , {Color(200,200,200),Color(255,255,255),Color(0,0,255),Color(0,0,0)} }, "arial.ttf", 15);
    
    Scene mainScene(Vector2f(800,600),Color(50,50,50));


    banan.setPos(Vector2f(0, 0));
    gr.append(&l);
    gr.append(&banan);
    gr.append(&tb);

    Slider sl(Vector2f(0, 200), 50, 0, 255, 2, 4, { {Color(75,75,75)},{Color(0,0,0),Color(150,150,150),Color(200,200,200)} }, true, false);
    InputInfo inputInfo;

    //LocalWindow win(Vector2f(50, 50), Vector2f(400, 300), "Window", "arial.ttf", 13, { {Color(100,100,120),Color(100,100,150) },{Color(50,50,70),Color(50,50,90) },{Color(255,255,255),Color(0,0,0,0)},{Color(20,20,100),Color(0,0,200)} }, close, hide);
    //LocalWindow win2(Vector2f(50, 0), Vector2f(400, 300), "Window2", "arial.ttf", 13, { {Color(100,100,120),Color(100,100,150) },{Color(50,50,70),Color(50,50,90) },{Color(255,255,255),Color(0,0,0,0)},{Color(20,20,100),Color(0,0,200)} }, close, hide);

    //win.append(&b);
    //win.append(&sl);
    //mainScene.append(&win);
    //mainScene.append(&win2);
    LocalWindowStyle windowStyle("arial.ttf", 13, { {Color(100,100,120),Color(100,100,150) },{Color(50,50,70),Color(50,50,90) },{Color(255,255,255),Color(0,0,0,0)},{Color(20,20,100),Color(0,0,200)} }, close, hide);

    WindowsRenderer windowsRenderer(Vector2f(window.getSize().x, window.getSize().y));
    windowsRenderer.createNewWindow(Vector2f(50,50), Vector2f(300, 300),"TEST1", windowStyle);
    windowsRenderer.createNewWindow(Vector2f(50, 70), Vector2f(300, 300), "TEST2", windowStyle);
    windowsRenderer.createNewWindow(Vector2f(100, 90), Vector2f(300, 300), "TEST3", windowStyle);
    windowsRenderer.createNewWindow(Vector2f(80, 110), Vector2f(300, 300), "TEST4", windowStyle);
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
        windowsRenderer.update(inputInfo);

        window.clear(Color(200, 200, 255));

        window.draw(mainScene.update(inputInfo));
        window.draw(windowsRenderer.sprite);
        window.display();

    }
    return 0;
}


