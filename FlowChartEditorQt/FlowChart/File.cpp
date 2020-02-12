// File.cpp

#include "File.h"
#include "DrawingPaper.h"
#include "FlowChart.h"
#include "Shape.h"
#include "Creator.h"
#include "Tokenizer.h"
#include <fstream>	//save  / load
#include "Preparation.h"
#include "VariableList.h"
#include "Zoom.h"
#include "Painter.h"

File::File() {}

File::~File() {}

Long File::Load(DrawingPaper *canvas, const char(*fileName)) {
	ifstream file;
	char line[513];

	Long count = 0;

	Shape * shape;

	Creator creator;
	Tokenizer tokenizer;

	(dynamic_cast<FlowChart *>(canvas->flowChart))->Clear();
	file.open(fileName);
	if (file.is_open()) {
		file.getline(line, 512);
		canvas->zoom->Set(atoi(line));

		file.getline(line, 512);
		while (!file.eof()) {
			tokenizer.Scan(line, '\t');
			String contents(" ");
			if (!(tokenizer.GetAt(7) == " ")) {
				contents = String(tokenizer.GetAt(7));
			}
			contents.Replace('\r', '\n');
			shape = creator.Create(atoi(tokenizer.GetAt(0)), atoi(tokenizer.GetAt(1)), atoi(tokenizer.GetAt(2)), atoi(tokenizer.GetAt(3)),
				atoi(tokenizer.GetAt(4)), atoi(tokenizer.GetAt(5)), atoi(tokenizer.GetAt(6)), contents);
			(dynamic_cast<FlowChart *>(canvas->flowChart))->Attach(shape);

			//=====================intellisense========================
			if (dynamic_cast<Preparation*>(shape)) {
				if (canvas->variableList != NULL) {
					delete canvas->variableList;
				}
				canvas->variableList = new VariableList;
				canvas->variableList->Add(shape->GetContents());
			}
			//=========================================================

			count++;
			file.getline(line, 512);
		}
		file.close();
	}
	return count;
}

Long File::Save(DrawingPaper *canvas, const char(*fileName)) {
	ofstream file;
	Long i = 0;
	Long end;
	Long count = 0;
	char line[256];
	Shape *shape;
	Long rate;
	// 3. 저장한다.
	file.open(fileName, ios::trunc);
	if (file.is_open()) {
		rate = canvas->zoom->GetRate();
		file << rate << "\n";
		end = (dynamic_cast<FlowChart *>(canvas->flowChart))->GetLength();
		while (i < end) {
			shape = dynamic_cast<FlowChart *>(canvas->flowChart)->GetAt(i);
			shape->GetLine(line);
			file << line;
			count++;
			i++;
		}
		file.close();
	}
	return count;
}