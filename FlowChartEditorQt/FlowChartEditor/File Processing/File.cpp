// File.cpp

#include "File.h"
#include "Tokenizer.h"
#include "../Interface/DrawingPaper.h"
#include "../Shapes/Composite/FlowChart.h"
#include "../Shapes/Shape.h"
#include "../Shapes/Creator.h"
#include "../Shapes/Symbols/Preparation.h"
#include "../Paint/Zoom/Zoom.h"
#include "../Rule/VariableList.h"
#include "../Rule/RuleKeeper.h"
#include "../Rule/ContentsAnalyzer.h"
#include "../History/Registrar.h"

#include "../../Graphic Objects/Composite/Painter.h"

#include <qfile.h>
#include <qtextstream.h>
#include <qdebug.h>

File::File() {}

File::~File() {}

Long File::Load(DrawingPaper *canvas, QString fileName) {
	QFile file(fileName);
	String lineRead;
	//char line[513];

	Long count = 0;

	NShape * shape;

	Creator creator;
	Tokenizer tokenizer;
	QString qContents("");

	canvas->flowChart = new FlowChart;
	canvas->registrar = new Registrar;

	bool isOpen = file.open(QIODevice::ReadOnly | QIODevice::Text);
	if (isOpen == true) {
		//줌 처리
		QTextStream textStream(&file);
		qContents = textStream.readLine();
		lineRead = qContents.toLocal8Bit().data();
		canvas->zoom->Set(atoi(lineRead));
		//변수 목록
		qContents = textStream.readLine();
		lineRead = qContents.toLocal8Bit().data();

		if (lineRead == "TRUE") {
			canvas->variableList = new VariableList;
		}
		else {
			if (canvas->variableList != NULL) {
				delete canvas->variableList;
				canvas->variableList = NULL;
			}
		}
		//내용 처리
		while (!textStream.atEnd()) {
			qContents = textStream.readLine();
			while (qContents.at(qContents.length() - 1) != ';') {
				qContents += '\n';
				qContents += textStream.readLine();
			}
			lineRead = qContents.toLocal8Bit().data();
			tokenizer.Scan(lineRead, '\t');
			String contents(" ");
			if (!(tokenizer.GetAt(7) == " ")) {
				contents = String(tokenizer.GetAt(7));
			}
			contents.Remove(';');
			shape = creator.Create(atof(tokenizer.GetAt(0)), atof(tokenizer.GetAt(1)), atof(tokenizer.GetAt(2)), atof(tokenizer.GetAt(3)),
				atof(tokenizer.GetAt(4)), atof(tokenizer.GetAt(5)), atof(tokenizer.GetAt(6)), contents);

			canvas->registrar->Register(shape);
			canvas->flowChart->Attach(shape);

			//=====================intellisense========================
			if (canvas->variableList != NULL && dynamic_cast<Preparation*>(shape)) {
				if (canvas->variableList != NULL) {
					delete canvas->variableList;
					canvas->variableList = NULL;
				}
				ContentsAnalyzer analyzer;
				RuleKeeper ruleKeeper;
				Array<String> variables = analyzer.MakeVariables(contents);
				canvas->variableList = ruleKeeper.CheckVariableNamingRule(variables);
			}
			//=========================================================

			count++;
		}
		file.close();
	}

	return count;
}

Long File::Save(DrawingPaper *canvas, QString fileName) {
	QFile file(fileName);
	Long i = 0;
	Long end;
	Long count = 0;
	char line[256];
	char(*variableList);
	NShape *shape;
	Long rate;
	// 3. 저장한다.
	bool isOpen = file.open(QIODevice::WriteOnly | QIODevice::Text);
	if (isOpen == true) {
		QTextStream textStream(&file);
		//줌
		rate = canvas->zoom->GetRate();
		textStream << rate << "\n"; //개행문자 실험 요망

		//변수 목록
		(canvas->variableList != NULL) ? (variableList = "TRUE") : (variableList = "FALSE");
		textStream << QString::fromLocal8Bit(variableList) << "\n";

		end = canvas->flowChart->GetLength();
		while (i < end) {
			shape = canvas->flowChart->GetAt(i);
			shape->GetLine(line);
			textStream << QString::fromLocal8Bit(line); //개행문자 ?
			count++;
			i++;
		}
		file.close();
	}

	return count;
}