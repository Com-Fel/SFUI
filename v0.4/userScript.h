#include<iostream>
#include<vector>
#include"SFUI/UI.h"


vector<XY> tablePoses = { XY(269,80),XY(269,270), XY(269,446),XY(489,80), XY(489,270), XY(489,446) };


Application app;


class Human {
public:
    XY pos = XY(55, 55);
    string id;
    bool moving = false;
    XY target = pos;
    float speed = 4;
    float dx, dy, distanceForTarget = 0, speedX = 0, speedY = 0;
    Human() {}
    Human(string id) {
        pos;
        this->id = id;
    }
    void move(float x, float y) {
        this->pos.x += x;
        this->pos.y += y;
    }
    void moveTo(float x, float y) {

        if (!moving) {

            target.x = x;
            target.y = y;
            dx = target.x - pos.x;
            dy = target.y - pos.y;
            moving = true;

            distanceForTarget = sqrt(pow(dx, 2) + pow(dy, 2));


            if (distanceForTarget != 0) {
                speedX = (speed * dx) / distanceForTarget;
                speedY = (speed * dy) / distanceForTarget;
            }
            else {
                //cout << dy << " " << dx << endl;
            }
            //cout << distanceForTarget;

        }
        else if (distanceForTarget > speed) {
            dx = target.x - pos.x;
            dy = target.y - pos.y;

            distanceForTarget = sqrt(pow(dx, 2) + pow(dy, 2));
            move(speedX, speedY);
        }
        else {
            pos.x = target.x;
            pos.y = target.y;
            target.x = pos.x;
            target.y = pos.y;

            moving = false;
        }

    }

    void moveToTarget() {
        if (target.x != pos.x || target.y != pos.y) {
            moveTo(target.x, target.y);
        }
        else {
            moving = false;
        }
    }
};

class Waiter : public Human {
public:
    int targetTable = 0;
    Waiter() {

    }

};




vector<Human> humans = {};
vector<Waiter> waiters = {};
void onLoad() {

    Human off1("off1");

    humans.push_back(off1);

    Waiter off2,off3,off4;


    waiters.push_back(off2);
    waiters.push_back(off3);
    waiters.push_back(off4);

    body->createBlock("Player");
    body->createBlock("Player");
    body->createBlock("Player");
    body->createBlock("Player");


}

void drawPol() {

}

void moveToTable() {
    for (int i = 0;i < tables->groups.size();i++) {
        string id = "tabBut";

        if (tables->groups[i]->findButtonById(id)->isclicked) {
            for (int j = 0;j < waiters.size();j++) {
                cout << waiters[j].moving;  
                if (!waiters[j].moving) {
                    waiters[j].moving = false;
                    waiters[j].target.x = tablePoses[i].x + tables->getPos().x;
                    waiters[j].target.y = tablePoses[i].y + tables->getPos().y;
                    break;
                }
            }
        }

    }


}




void onUpdate() {



    for (int i = 0;i < humans.size();i++) {
        humans[i].moveToTarget();
    }
    for (int i = 0;i < waiters.size();i++) {
        waiters[i].moveToTarget();
    }
    pl1->setPos(Vector2f(waiters[0].pos.x, waiters[0].pos.y));
    pl2->setPos(Vector2f(waiters[1].pos.x, waiters[1].pos.y));
    pl3->setPos(Vector2f(waiters[2].pos.x, waiters[2].pos.y));



}


void loadChanges(){
	functionsDictionary = {Function("onLoad", &onLoad),Function("drawPol", &drawPol),Function("moveToTable", &moveToTable),Function("onUpdate", &onUpdate)};
}