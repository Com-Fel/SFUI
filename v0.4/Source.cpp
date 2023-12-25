#include "SFUI/UI.h"



using namespace std;
using namespace sf;
using namespace UI;



int main() {
    setlocale(LC_ALL, "Russian");

    ContextSettings settings;
    settings.antialiasingLevel = 0;

    RenderWindow window(VideoMode(1920, 1080), "SFMLworks", Style::Default, settings);
    window.setFramerateLimit(60);


    Button testBut(Vector2f(50, 50), Vector2f(100, 100), StandartContextMenuButtonStyle, "", "Click");
  

    WindowsRenderer windowsRenderer(Vector2f(window.getSize().x, window.getSize().y));
    windowsRenderer.createNewWindow(Vector2f(100, 130), Vector2f(600, 500), "Test1", StandartWindowStyle);
    windowsRenderer.createNewWindow(Vector2f(100, 110), Vector2f(300, 300), "Test2", StandartWindowStyle);
    windowsRenderer.createNewWindow(Vector2f(100, 90), Vector2f(300, 300), "Test3", StandartWindowStyle);
    windowsRenderer.createNewWindow(Vector2f(100, 70), Vector2f(300, 300), "Test4", StandartWindowStyle);
    windowsRenderer.createNewWindow(Vector2f(100, 50), Vector2f(300, 300), "qweqwe", StandartWindowStyle);
    
    windowsRenderer.windows[0]->append(&testBut);


    Scene mainScene(Vector2f(1920, 1080), Color(0, 0, 0));
    InputInfo inputInfo;
   
    ContextMenuRenderer contextMenuRenderer(Vector2f(1920, 1080), StandartContextMenuStyle);
  

    while (window.isOpen())
    {
        

        string inp = "";
        
        sf::Event evt;
        inputInfo.keyboardInput = "";

        window.pollEvent(evt);
        inputInfo.update(evt, Mouse::getPosition(window));
        windowsRenderer.update(inputInfo);
        
        window.clear(Color(200, 200, 255));
        
        window.draw(mainScene.update(inputInfo));
        window.draw(windowsRenderer.sprite);
        window.draw(contextMenuRenderer.update(inputInfo));

        window.display();

    }
    return 0;
}


