#pragma once
#include<iostream>
#include <fstream>
#include <string>
#include <vector>

class Block {
public:
	string type;
	vector<KeyValue> params;

	



	void info() {
		

		cout << endl << type << "--------\n";
		for (int i = 0;i < params.size();i++){
			cout << params[i].key << ": " << params[i].value << endl;
		}
		cout << endl << type << "--------\n";


		
	}
	string getValue(string key) {
		for (int i = 0;i < params.size();i++) {
			if (params[i].key == key) {
				return params[i].value;
			}
		}
		return "";
	}
	void copy(Block eBlock) {
		for (int i = 0;i < eBlock.params.size();i++) {
			if (getValue(eBlock.params[i].key) == "") {
				params.push_back(eBlock.params[i]);
			}
			else {
				for (int j = 0;j < params.size();j++) {
					if (params[j].key == eBlock.params[i].key) {
						params[j].value = eBlock.params[i].value;
					}
				}
			}
		}
	}
};

class BlockGroup : public Block {
public:
	vector<Block> innerElements;
	vector<BlockGroup> innerGroups;

	vector<IntKeyValue> intVar;
	vector<FloatKeyValue> floatVar;
	vector<StringKeyValue> stringVar;

	bool isPref = false;
	void info() {
		

		cout << endl << type << "-------------\n";
		cout << "PARAMS:" << endl;
		for (int i = 0;i < params.size();i++) {
			cout << params[i].key << ": " << params[i].value << endl;
		}

		cout << "INNNER:" << endl;

		for (int i = 0;i < innerGroups.size();i++) {
			innerGroups[i].info();
		}
		for (int i = 0;i < innerElements.size();i++) {
			innerElements[i].info();
		}

		cout << endl << type << "-------------\n";

	}
	BlockGroup getBlockGroup(string name) {   
		for (int i = 0;i < innerGroups.size();i++) {
			if (innerGroups[i].type == name) {
				return innerGroups[i];
			}
		}
	}


};
class Head {
public:
	string stylePath;
	string scriptPath;

	Head(BlockGroup headBlock){
		if (headBlock.type == "head") {
			for (int i = 0;i < headBlock.innerElements.size();i++) {
				if (headBlock.innerElements[i].type == "include") {
					if (headBlock.innerElements[i].getValue("type") == "style") {
						stylePath = headBlock.innerElements[i].getValue("path");
					}
					if (headBlock.innerElements[i].getValue("type") == "script") {
						scriptPath = headBlock.innerElements[i].getValue("path");
					}
				}
			}
		}
	}

};


Block readBlock(string inp) {
	Block out;

	out.type = readFromTo(inp, '>', '(');
	out.params = ConvertTokeyValueVector(readFromTo(inp, '(', ')'));
	return out;
}




BlockGroup readBlockGroup(string inp, int start, vector<BlockGroup> staticGroups) {
	BlockGroup out;
	bool named = false, varStarted = false;
	int d = 0, blockStart = 0;
	string temp;
	for (int i = start;i < inp.size();i++) {

		if (d == 0) {
			if (!named && inp[i] == '{') { // BlockGroup start
				out.type = readFromTo(temp, '>', '(');
				out.params = ConvertTokeyValueVector(readFromTo(temp, '(', ')'));
				named = true;	
				temp = "";

			}
			else if (inp[i] == '>') { // Start of single Group
				temp += inp[i];
				blockStart = i;
			}
			else if (named && inp[i] == '{') { // BlockGroup in BlockGroup start
				out.innerGroups.push_back(readBlockGroup(inp, blockStart, staticGroups));
				d++;
				temp = "";

			}
			else if (inp[i] == ';') { // End of single block
				Block block = readBlock(temp);

				for (int j = 0;j < staticGroups.size();j++) {// Castom block
					if (block.type == staticGroups[j].type) {
						
						BlockGroup statCopy = staticGroups[j];
						statCopy.isPref = true;
						statCopy.copy(block);
						out.innerGroups.push_back(statCopy);
						temp = "";

					}
				}
				// standart block
				if (!temp.empty()) {
					out.innerElements.push_back(block);
					temp = "";
				}
			}
			else if (inp[i] == '*') { // Var start/end
				varStarted = !varStarted;

				if (!varStarted) {
					string typeName;
					for (int j = 0;j < temp.size();j++) {

						typeName += temp[j];
						if (typeName == "int") {
							string name = readFromTo(readFromToInd(temp, j+1, temp.size()), '|', '=');
							int value = stoi(readFromTo(temp, '=', '|'));

							out.intVar.push_back(IntKeyValue(name, value));
						}
						if (typeName == "string") {
							string name = readFromTo(readFromToInd(temp, j + 1, temp.size()), '|', '=');
							string value = readFromTo(temp, '=', '|');

							out.stringVar.push_back(StringKeyValue(name, value));
						}
						if (typeName == "float") {
							string name = readFromTo(readFromToInd(temp, j + 1, temp.size()), '|', '=');
							float value = stof(readFromTo(temp, '=', '|'));

							out.floatVar.push_back(FloatKeyValue(name, value));
						}

					}
					temp = "";

				}
			}

			else { // Temp++
				temp += inp[i];
			}
			if (inp[i] == '}') {
				break;
			}
		}
		else {
			if (inp[i] == '{') {
				d++;
			}
			if (inp[i] == '}') {
				d--;
			}
		}
	}
	

	return out;
}

Vector2f getVector2f(string inp) {
	return Vector2f(stof(readFromTo(inp,'|','^')), stof(readFromTo(inp, '^', '|')));
}
 
vector<BlockGroup> staticGroups;

BlockGroup parseFile(string fileName) {


	string text = readFile(fileName);
	text = ">fileGroup(){" + text + "}";
	
	BlockGroup fileGroup = readBlockGroup(text, 0, staticGroups);

	for (int i = 0;i < fileGroup.innerGroups.size();i++) {
		fileGroup = readBlockGroup(text, 0, staticGroups);
		if (fileGroup.innerGroups[i].type != "window") {
			staticGroups.push_back(fileGroup.innerGroups[i]);
		}
	}
	fileGroup = readBlockGroup(text, 0, staticGroups);


	BlockGroup win = fileGroup.getBlockGroup("window");


	return win;
}


float getPX(string inp) {
	string type,temp;
	float value;
	bool isT = false;

	for (int i = 0;i < inp.size();i++) {
		if (((int(inp[i]) > 57 || int(inp[i]) < 48) && inp[i] != '.') && !isT) {
			value = stof(temp);
			temp = "";
			isT = true;
			
		}
		temp += inp[i];

	}
	type = temp;
	if (type == "px") {
		return value;
	}
	else {
		return stoi(inp);

	}

}
float getPX(string inp,float parentSize) {
	string type, temp;
	float value=0;
	bool isT = false;

	for (int i = 0;i < inp.size();i++) {
		
		if (((int(inp[i]) > 57 || int(inp[i]) < 48) && inp[i] != '.') && !isT) {
			
			value = stof(temp);
			temp = "";
			isT = true;

		}
		temp += inp[i];

	}
	type = temp;
	if (type == "px") {
		return value;
	}
	else if (type == "%") {
		return value/100 * parentSize;
	}
	
	
}


vector<string> getStrSize(string inp) {

 	return { readFromTo(inp, '|', '^'), readFromTo(inp, '^', '|') };
}