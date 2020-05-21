#ifndef _SHEETMANAGER_H
#define _SHEETMANAGER_H

typedef signed long int Long;
#include <qpoint.h>
#include <qstring.h>

class DrawingPaper;
class NShape;
class SheetBinder;
class FlowChartVisitor;

class SheetManager {
public:
	SheetManager(DrawingPaper *canvas = 0);
	SheetManager(const SheetManager& source);
	~SheetManager();
	SheetManager& operator=(const SheetManager& source);

	Long Select(QPoint point); //get index of sheet binder by point of window title
	Long Change(Long index); //change current sheet
	Long New(); //make and add empty sheet
	Long Close(); //remove current sheet

	Long Open(QString fileOpenPath); //load and add sheet

	void ModifyFileOpenPath(QString fileOpenPath);
	void ModifyTitles();
	void ModifyPreviousFlowChart(NShape *previousFlowChart);
	void Draw(FlowChartVisitor *draw);

	NShape* GetTitle(Long index);
	QString& GetFileOpenPath(Long index);
	Long GetBinderLength();
	Long GetBinderCurrent();

private:
	DrawingPaper *canvas;
	SheetBinder *sheetBinder;
};

#endif //_SHEETMANAGER_H