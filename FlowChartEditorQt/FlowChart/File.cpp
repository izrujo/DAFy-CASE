// File.cpp

#include "File.h"
#include "DrawingPaper.h"
#include "FlowChart.h"
#include "Shape.h"
#include "Creator.h"
#include "Tokenizer.h"
#include "Preparation.h"
#include "VariableList.h"
#include "Zoom.h"
#include "../GObject/Painter.h"

#include <qfile.h>
#include <qtextstream.h>

File::File() {}

File::~File() {}

Long File::Load(DrawingPaper *canvas, const char(*fileName)) {
	QFile file(fileName);
	char (*line) = new char[513];

	Long count = 0;

	Shape * shape;

	Creator creator;
	Tokenizer tokenizer;
	QString qContents;

	canvas->flowChart->Clear();
	bool isOpen = file.open(QIODevice::ReadOnly | QIODevice::Text);
	if (isOpen == true) {
		QTextStream textStream(&file);
		qContents = textStream.readLine();
		line = const_cast<char*>(qContents.toLocal8Bit().constData());
		canvas->zoom->Set(atoi(line));

		qContents = textStream.readLine();
		line = const_cast<char*>(qContents.toLocal8Bit().constData());
		//file.getline(line, 512);
		while (!textStream.atEnd()) {
			tokenizer.Scan(line, '\t');
			String contents(" ");
			if (!(tokenizer.GetAt(7) == " ")) {
				contents = String(tokenizer.GetAt(7));
			}
			contents.Replace('\r', '\n');
			shape = creator.Create(atoi(tokenizer.GetAt(0)), atoi(tokenizer.GetAt(1)), atoi(tokenizer.GetAt(2)), atoi(tokenizer.GetAt(3)),
				atoi(tokenizer.GetAt(4)), atoi(tokenizer.GetAt(5)), atoi(tokenizer.GetAt(6)), contents);
			canvas->flowChart->Attach(shape);

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
			qContents = textStream.readLine();
			line = const_cast<char*>(qContents.toLocal8Bit().constData());
		}
		file.close();
	}

	return count;
}

Long File::Save(DrawingPaper *canvas, const char(*fileName)) {
	QFile file(fileName);
	Long i = 0;
	Long end;
	Long count = 0;
	char line[256];
	Shape *shape;
	Long rate;
	// 3. 저장한다.
	bool isOpen = file.open(QIODevice::WriteOnly | QIODevice::Text);
	if (isOpen == true) {
		QTextStream textStream(&file);

		rate = canvas->zoom->GetRate();
		textStream << rate << "\n"; //개행문자 실험 요망
		end = canvas->flowChart->GetLength();
		while (i < end) {
			shape = canvas->flowChart->GetAt(i);
			shape->GetLine(line);
			textStream << line; //개행문자 ?
			count++;
			i++;
		}
		file.close();
	}

	return count;
}