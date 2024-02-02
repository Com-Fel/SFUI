
#include <fstream>
#include "UI.h"


using namespace UI;

string readValueFromGroup(BlockGroup gr) {

	string type = "Group", id = gr.getValue("id");
	
	string out = type + "* " + id + ";\n";
	if (!gr.isPref) {
		for (int i = 0;i < gr.innerGroups.size();i++) {
			out += readValueFromGroup(gr.innerGroups[i]);
		}

		for (int i = 0;i < gr.innerElements.size();i++) {
			Block el = gr.innerElements[i];
			

			string typeName = gr.innerElements[i].type;
			if (typeName == "image") {
				typeName = "ImageBox";
			}
			typeName[0] = char(int(gr.innerElements[i].type[0]) - 32);

			out += typeName+ "*" +gr.innerElements[i].getValue("id") + ";\n";
		}
	}
	return out;
}


string readFunctionFromGroup(BlockGroup gr,string parent) {

	string type = "Group", id = gr.getValue("id");

	string out =    id + " = " + parent + "find" + type+ "ById(\"" + id + "\");\n";
	if (!gr.isPref) {
		for (int i = 0;i < gr.innerGroups.size();i++) {
			out += readFunctionFromGroup(gr.innerGroups[i], id + "->");
		}

		for (int i = 0;i < gr.innerElements.size();i++) {
			Block el = gr.innerElements[i];
			

			string typeName = gr.innerElements[i].type;

			if (typeName == "image") {
				typeName = "ImageBox";
			}
			typeName[0] = char(int(gr.innerElements[i].type[0]) - 32);

			out +=  gr.innerElements[i].getValue("id") + " = " + id + "->find" + typeName + "ById(\"" + gr.innerElements[i].getValue("id") + "\");\n";
		}
	}
	return out;
}




string createIdFile(BlockGroup  body) {
	string idText;

	ofstream out("SFUI/id.h");
	idText += "#include \"UI.h\"\nusing namespace UI;\n";

	idText += readValueFromGroup(body) ;
	
	idText +=	"\nvoid initID(){\n";

	idText+= readFunctionFromGroup(body,"mainScene.")+ "\n}";

	out << idText;

	return idText;
} 