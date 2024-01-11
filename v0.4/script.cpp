
#include<iostream>
#include<vector>
#include"SFUI/UI.h"
int i;

void fun1() {
	int val1, val2;

	Group* body = mainScene.findGroupById("body");
	 
	val1 = stoi(body->findTextboxById("va1")->stText);
	val2 = stoi(body->findTextboxById("va2")->stText);
	body->findLabelById("ans")->setText(to_string(val1 + val2));
	
}
