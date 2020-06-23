#include "../FlowChartEditor/Interface/FlowChartEditor.h"
#include "../FlowChartEditor/Interface/EditorIntroForm.h"
#include <QtWidgets/QApplication>
#include <qthread.h>
#include <qicon.h>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QIcon icon("iconTrans_ver.3");
	a.setWindowIcon(icon);

	EditorIntroForm flashWindow;
	flashWindow.show();
	QThread thread;
	//thread.sleep(5);
	thread.sleep(1);
	flashWindow.close();

	FlowChartEditor w;
	w.show();

	return a.exec();
}