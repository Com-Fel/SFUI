#include "UI.h"
using namespace UI;
Group* body;
Group* tables;
Group* t1;
Group* t2;
Group* t3;
Group* t4;
Group* t5;
Group* t6;
Group* kitchen;
Group* bar;
Group* walls;
ImageBox*wallIm;
Group* canvas;
Button*esc_button;
Label*FPS;
Group* pl1;
Group* pl2;
Group* pl3;
Label*FPS1;

void initID(){
body = mainScene.findGroupById("body");
tables = body->findGroupById("tables");
t1 = tables->findGroupById("t1");
t2 = tables->findGroupById("t2");
t3 = tables->findGroupById("t3");
t4 = tables->findGroupById("t4");
t5 = tables->findGroupById("t5");
t6 = tables->findGroupById("t6");
kitchen = body->findGroupById("kitchen");
bar = body->findGroupById("bar");
walls = body->findGroupById("walls");
wallIm = walls->findImageBoxById("wallIm");
canvas = body->findGroupById("canvas");
esc_button = canvas->findButtonById("esc_button");
FPS = canvas->findLabelById("FPS");
pl1 = body->findGroupById("pl1");
pl2 = body->findGroupById("pl2");
pl3 = body->findGroupById("pl3");
FPS1 = body->findLabelById("FPS1");

}