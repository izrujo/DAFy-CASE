#ifndef _SHEET_H
#define _SHEET_H

#include <qstring.h>

class NShape;
class HistoryBook;
class Registrar;
class VariableList;

class Sheet {
	friend class SheetManager;
public:
	Sheet(NShape *title, QString fileOpenPath, NShape *flowChart, 
		HistoryBook *undoHistoryBook, HistoryBook *redoHistoryBook, NShape *previousFlowChart,
		Registrar *registrar, VariableList *variableList);
	Sheet(const Sheet& source);
	~Sheet();
	Sheet& operator=(const Sheet& source);

	Sheet* Clone();

	NShape* GetTitle() const;
	QString& GetFileOpenPath() const;
	NShape* GetFlowChart() const;
	HistoryBook* GetUndoHistoryBook() const;
	HistoryBook* GetRedoHistoryBook() const;
	NShape* GetPreviousFlowChart() const;
	Registrar* GetRegistrar() const;
	VariableList* GetVariableList() const;

private:
	NShape *title;
	QString fileOpenPath;
	NShape *flowChart;
	HistoryBook *undoHistoryBook;
	HistoryBook *redoHistoryBook;
	NShape *previousFlowChart;
	Registrar *registrar;
	VariableList *variableList;
};

#endif //_SHEET_H