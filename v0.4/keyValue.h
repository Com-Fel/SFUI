#pragma once

#include<iostream>
#include<vector>
#include <string>
using namespace std;

using namespace sf;

class FloatKeyValue {
public:
	string key;
	float value;
	FloatKeyValue(string key, float value) {
		this->key = key;
		this->value = value;
	}

	FloatKeyValue() {}
};
class IntKeyValue {
public:
	string key;
	int value;
	IntKeyValue(string key, int value) {
		this->key = key;
		this->value = value;
	}

	IntKeyValue() {}
};
class StringKeyValue {
public:
	string key;
	string value;
	StringKeyValue(string key, string value) {
		this->key = key;
		this->value = value;
	}

	StringKeyValue() {}
};