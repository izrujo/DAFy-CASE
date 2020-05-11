#include "FlowChartEditor.h"
#include "FlowChart/EditorIntroForm.h"
#include <QtWidgets/QApplication>
#include <qthread.h>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	EditorIntroForm flashWindow;
	flashWindow.show();
	QThread thread;
	thread.sleep(5);
	flashWindow.close();

	FlowChartEditor w;
	w.show();

	return a.exec();
}
