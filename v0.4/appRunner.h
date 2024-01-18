#include "UI.h"



using namespace std;
using namespace sf;
using namespace UI;





int RunApplication() {
    setlocale(LC_ALL, "Russian");

    BlockGroup win = parseFile("index.stab");
    BlockGroup head = win.getBlockGroup("head");
    BlockGroup body = win.getBlockGroup("body");
    Head headInfo(head);


    string oldFile = readFileWithSpaces("SFUI/userScript.h");
    if (oldFile != parseScript(headInfo.scriptPath)) {
        cout << "Changes saved" << endl;
        return 0;
    }
    loadChanges();
    
    

    StyleSheets styles(headInfo.stylePath);
   

   

    ContextSettings settings;
    settings.antialiasingLevel = 0;

    Vector2f winSize = getVector2f(win.getValue("size"));
    mainScene.setSize(winSize);

    RenderWindow window(VideoMode(winSize.x, winSize.y), win.getValue("title"), sf::Style::Close, settings);
    window.setFramerateLimit(60);


    WindowsRenderer windowsRenderer(Vector2f(window.getSize().x, window.getSize().y));

    
    
    ContextMenuRenderer contextMenuRenderer(Vector2f(1920, 1080), StandartContextMenuStyle);
    Group Gbody(body, styles);
    mainScene.append(&Gbody);

    drawer.setSize(winSize);
    drawer.drawRect(Vector2f(500,500),Vector2f(100,100),Color::White);

    onLoad();
    while (window.isOpen())
    {
        //mainScene.setSize(Vector2f(window.getSize().x, window.getSize().y));

        string inp = "";
        
        sf::Event evt;
        inputInfo.keyboardInput = "";

        window.pollEvent(evt);
        inputInfo.update(evt, Mouse::getPosition(window));
        windowsRenderer.update(inputInfo);


        onUpdate();

        window.clear();
        
        window.draw(mainScene.update(inputInfo));
        window.draw(drawer.sprite);

        window.display();
        
    }
    return 0;
}


