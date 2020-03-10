#include "EditorIntroForm.h"
#include "GObject.h"
#include "QtPainter.h"
#include "QtGObjectFactory.h"

#include <qpainter.h>
#include <qimage.h>

EditorIntroForm::EditorIntroForm(QWidget *parent = Q_NULLPTR) {

}

EditorIntroForm::~EditorIntroForm() {

}

void EditorIntroForm::paintEvent(QPaintEvent *event) {
	QPainter dc(this);

	QRect rect = this->frameRect();
	GObject *painter = new QtPainter(rect.width(), rect.height());

	QImage image("icon ver.3.bmp");

	QRect rect(270, 80, 330, 140);
	
	painter->DrawImage(rect, "icon ver.3.bmp", rect, Qt::AutoColor);

	QtGObjectFactory factory;
	GObject *font = factory.MakeFont("Malgun Gothic", 14, 70, false);
	painter->SelectObject(*font);
	painter->Update();
	
	QRect rect2(100, 150, 500, 200);
	painter->DrawText(rect2, Qt::AlignCenter, "FlowChartEditor");

	QRect rect3(100, 200, 500, 250);
	painter->DrawText(rect3, Qt::AlignCenter, "ver 0.05");

	QRect rect4(100, 300, 500, 350);
	painter->DrawText(rect4, Qt::AlignCenter, "NaACoaching.com");

	if (painter != NULL) {
		delete painter;
	}
}