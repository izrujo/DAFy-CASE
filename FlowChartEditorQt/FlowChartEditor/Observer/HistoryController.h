#ifndef _HISTORYCONTROLLER_H
#define _HISTORYCONTROLLER_H

#include "../../Notepad/Observer/Observer.h"

class DrawingPaper;
class HistoryBook;
class NShape;

class HistoryController : public Observer {
public:
	HistoryController(DrawingPaper *canvas = 0);
	HistoryController(const HistoryController& source);
	~HistoryController();
	HistoryController& operator=(const HistoryController& source);

	void Update();
	void Undo();
	void Redo();
	void ChangeAll(HistoryBook *undoHistoryBook, HistoryBook *redoHistoryBook, NShape *previosuFlowChart);

	HistoryBook* GetUndoHistoryBook() const;
	HistoryBook* GetRedoHistoryBook() const;
	NShape* GetPreviousFlowChart() const;
private:
	DrawingPaper *canvas;
	HistoryBook *undoHistoryBook;
	HistoryBook *redoHistoryBook;
	NShape *previousFlowChart;
};

inline HistoryBook* HistoryController::GetUndoHistoryBook() const {
	return this->undoHistoryBook;
}
inline HistoryBook* HistoryController::GetRedoHistoryBook() const {
	return this->redoHistoryBook;
}
inline NShape* HistoryController::GetPreviousFlowChart() const {
	return this->previousFlowChart;
}

#endif //_HISTORYCONTROLLER_H