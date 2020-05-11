#include "EditorIntroForm.h"
#include "../GObject/GObject.h"
#include "../GObject/QtPainter.h"
#include "../GObject/QtGObjectFactory.h"

#include <qpainter.h>
#include <qimage.h>

EditorIntroForm::EditorIntroForm(QWidget *parent)
	: QFrame(parent) {
	ui.setupUi(this);

	this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
}

void EditorIntroForm::closeEvent(QCloseEvent *event) {
	QFrame::closeEvent(event);
}

void EditorIntroForm::paintEvent(QPaintEvent *event) {
	QPainter dc(this);

	QRect rect = this->frameRect();
	GObject *painter = new QtPainter(rect.width(), rect.height(), QColor(102, 204, 204));

	float sizeWidth = rect.width() / 8.0F;
	float sizeHeight = rect.height() / 8.0F;
	float x;
	float y;
	float width;
	float height;
	
	/*
	QImage image("icon ver.3.bmp");

	x = rect.x() + sizeWidth * 3;
	y = rect.y() + sizeHeight * 1;
	width = sizeWidth * 2;
	height = sizeHeight * 2;
	QRect imageRect(x, y, width, height);

	painter->DrawImage(rect, "icon ver.3.bmp", imageRect, Qt::AutoColor);
	*/

	QtGObjectFactory factory;
	//==========Title of App==========
	GObject *font = factory.MakeFont("Malgun Gothic", 20, 70, false);
	GObject *oldFont = painter->SelectObject(*font);
	GObject *pen = factory.MakePen(QBrush(QColor(255, 255, 255)), 3);
	painter->SelectObject(*pen);
	painter->Update();

	x = rect.x() + sizeWidth * 2;
	y = rect.y() + sizeHeight * 2.5;
	width = sizeWidth * 4;
	height = sizeHeight * 1 + 10;
	QRect rect2(x, y, width, height);
	
	painter->DrawTextQ(rect2, Qt::AlignCenter, "DAFy CASE");

	painter->SelectObject(*oldFont);
	painter->Update();
	if (font != 0) {
		delete font;
	}
	//==========Title of App==========

	//==========Version of App==========
	x = rect.x() + sizeWidth * 3;
	y = rect.y() + sizeHeight * 3.5 + 10;
	width = sizeWidth * 2;
	height = sizeHeight * 1 / 3;
	QRectF rect3(x, y, width, height);
	
	painter->DrawTextQ(rect3, Qt::AlignCenter, "ver 1.05");
	//==========Version of App==========

	//==========Company Name of App==========
	font = factory.MakeFont("Malgun Gothic", 14, 70, false);
	oldFont = painter->SelectObject(*font);
	painter->Update();

	x = rect.x() + sizeWidth * 2;
	y = rect.y() + sizeHeight * 4.5;
	width = sizeWidth * 4;
	height = sizeHeight * 1;
	QRect rect4(x, y, width, height);
	
	painter->DrawTextQ(rect4, Qt::AlignCenter, "NaA Coaching");
	
	painter->SelectObject(*oldFont);
	painter->Update();
	if (font != 0) {
		delete font;
	}
	//==========Company Name of App==========

	painter->Render(&dc, 0, 0);

	if (painter != NULL) {
		delete painter;
	}
}