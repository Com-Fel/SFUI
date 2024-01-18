
#include<iostream>
#include<vector>
#include"SFUI/UI.h"


vector<Vector2f> snakepos = {Vector2f(0,0)};
Vector2f eatPos(rand()%12, rand() % 12);

int dirX = 1, dirY = 0;
int ticker = 0,score = 0;
bool isDead = false;

Group* body;
void die() {
	

	isDead = true;
}

void moveSnake() {
	Vector2f bPos = snakepos[snakepos.size() - 1];
	Vector2f aPos = Vector2f(bPos.x + dirX, bPos.y + dirY);

	
	for (int i = 0;i < snakepos.size() - 1;i++) {
		if (aPos == snakepos[i]) {

			die();
			return;
		}
	}
	if (aPos.x < 0 || aPos.x > 11 || aPos.y < 0 || aPos.y > 11) {

		die();
		return;
	}
	snakepos.push_back(aPos);

	if (snakepos[snakepos.size() - 1] != eatPos) {
		snakepos.erase(snakepos.begin());
	}
	else {
		bool inSnake = true;
		while (inSnake) {
			eatPos.x = rand() % 12;
			eatPos.y = rand() % 12;
			inSnake = false;
			for (int i = 0;i < snakepos.size();i++) {
				if (eatPos == snakepos[i]) {
					inSnake = true;
				}
			}
		}
		score += 100;
	    body->findGroupById("menu")->findLabelById("score")->setText("Score: "+to_string(score));
	}

	

	ticker = 0;
}


void drawSnake() {
	for (int i = 0;i < snakepos.size()-1;i++) {

		drawer.drawRect(Vector2f(snakepos[i].x* 50 + 10, snakepos[i].y * 50 + 10), Vector2f(30, 30), Color(255* isDead, 255*!isDead, 0));

	}
	drawer.drawRect(Vector2f(snakepos[snakepos.size()-1].x * 50 + 10, snakepos[snakepos.size() - 1].y * 50 + 10), Vector2f(30, 30), Color(255 * !isDead+100*isDead, 255 * !isDead, 0));
}


void drawPlayBoard() {

	
	for (int x = 0;x < 12;x++) {

		for (int y = 0;y < 12;y++) {
			drawer.drawRect(Vector2f(x*50+20,y*50+20),Vector2f(10,10),Color(25,25,25));
		}
	}
}

void input() {
	for (int i = 0;i < inputInfo.clickedKeyCodes.size();i++) {

		int code = inputInfo.pressedKeyCodes[i];

		if (code == keyCode.A && (dirX == 0 || dirX == -1)) {
			dirX = -1;
			dirY = 0;
			moveSnake();

		}
		if (code == keyCode.D && (dirX == 0 || dirX == 1)) {
			dirX = 1;
			dirY = 0;
			moveSnake();
		}
		if (code == keyCode.S && (dirY == 0 || dirY == 1)) {
			dirY = 1;
			dirX = 0;
			moveSnake();
		}
		if (code == keyCode.W && (dirY == 0 || dirY == -1)) {
			dirY = -1;
			dirX = 0;
			moveSnake();
		}
	}
}

void onLoad() {

}

void onUpdate() {
	body = mainScene.findGroupById("body");

	if (!isDead) {
		input();

		if (ticker >= 15) {
			moveSnake();
		}
		ticker++;
	}

	drawer.clear();
	drawPlayBoard();
	if (!isDead) {
		drawer.drawRect(Vector2f(eatPos.x * 50 + 10, eatPos.y * 50 + 10), Vector2f(30, 30), Color(255, 0, 0));
	}

	drawSnake();


}



void restart() {
	snakepos = { Vector2f(0,0) };
	eatPos.x = rand() % 12;eatPos.y=rand() % 12;

	dirX = 1, dirY = 0;
	ticker = 0, score = 0;
    isDead = false;
	body->findGroupById("menu")->findLabelById("score")->setText("Score: " + to_string(score));


}

void loadChanges(){
	functionsDictionary = {Function("die", &die),Function("moveSnake", &moveSnake),Function("drawSnake", &drawSnake),Function("drawPlayBoard", &drawPlayBoard),Function("input", &input),Function("onLoad", &onLoad),Function("onUpdate", &onUpdate),Function("restart", &restart)};
}