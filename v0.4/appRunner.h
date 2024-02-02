#include "UI.h"



using namespace std;
using namespace sf;
using namespace UI;




int RunApplication() {
    setlocale(LC_ALL, "Russian");

    BlockGroup win = parseFile("index.stab");
    BlockGroup headGroup = win.getBlockGroup("head");
    BlockGroup bodyGroup = win.getBlockGroup("body");
    
    
    
    Head headInfo(headGroup);

    
    string oldScriptFile = readFileWithSpaces("SFUI/userScript.h");
    string oldIdFile = readFileWithSpaces("SFUI/id.h");
    
    string newIdFile = createIdFile(bodyGroup)+'\n';
    
    if (oldScriptFile != parseScript(headInfo.scriptPath) || oldIdFile != newIdFile) {
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
    Group Gbody(bodyGroup, styles);
    mainScene.append(&Gbody);

    drawer.setSize(winSize);
    
    initID();
    onLoad();
    sf::Clock clock;
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

       
        
        window.draw(mainScene.update(inputInfo));
        //window.draw(drawer.sprite);

        window.display();
        sf::Time elapsed = clock.restart();
        float fps = 1.0f / elapsed.asSeconds();
        FPS->setText(to_string(int(fps))+" fps");
    }
    return 0;
}


