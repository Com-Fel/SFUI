#pragma once
#include "UI.h"
using namespace sf;
using namespace std;

namespace UI{
    string standartFont = "arial.ttf";




    ButtonStyle closeStyle({{ Color(255,255,255,0)  ,Color(255,0,0)    ,Color(100,100,100) },
                            { Color(255,255,255,0)  ,Color(255,0,0)    ,Color(100,100,100) },
                            { Color(255,255,255)    ,Color(255,255,255),Color(255,255,255)}},
                            2, Vector2f(5, -3), 17, standartFont, { 5,5,5,5 }              );


    ButtonStyle hideStyle({ { Color(255,255,255,0) ,Color(100,100,100),Color(100,100,100)  },
                            { Color(255,255,255,0) ,Color(100,100,100),Color(100,100,100)  },
                            { Color(255,255,255)   ,Color(255,255,255),Color(255,255,255) }},
                            2, Vector2f(6, -3), 17, standartFont, { 5,5,5,5 }              );


    LocalWindowStyle StandartWindowStyle(standartFont, 13,
                           {{Color(40,40,40),Color(80,80,80)   },
							{Color(50,50,50)   ,Color(50,50,50)},
							{Color(255,255,255),Color(0,0,0,0) },
							{Color(40,40,40),Color(80,80,80)}  }, closeStyle, hideStyle);


    ButtonStyle StandartContextMenuButtonStyle({{ Color(25,25,25)    ,Color(100,100,100)  ,Color(120,120,120) },
                                                { Color(150,150,150) ,Color(150,150,150)  ,Color(150,150,150) },
                                                { Color(255,255,255) ,Color(255,255,255)  ,Color(255,255,255)}},
                                                1, Vector2f(15, 1), 12, standartFont, { 0,0,0,0 });

    ContextMenuStyle StandartContextMenuStyle(250,20,1,Color(120,120,120), StandartContextMenuButtonStyle);
}



