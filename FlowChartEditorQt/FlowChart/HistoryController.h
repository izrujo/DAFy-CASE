#ifndef _HISTORYCONTROLLER_H
#define _HISTORYCONTROLLER_H

#include "../Notepad/Observer.h"

class DrawingPaper;
class HistoryBook;
class Registrar;

class HistoryController : public Observer {
public:
	HistoryController(DrawingPaper *canvas = 0);
	HistoryController(const HistoryController& source);
	~HistoryController();
	HistoryController& operator=(const HistoryController& source);

	void Update();
	void Undo();
	void Redo();

	HistoryBook* GetUndoHistoryBook() const;
	HistoryBook* GetRedoHistoryBook() const;
	Registrar* GetRegistrar() const;
private:
	DrawingPaper *canvas;
	Registrar *registrar;
	HistoryBook *undoHistoryBook;
	HistoryBook *redoHistoryBook;
	NShape *previousFlowChart;
};

inline HistoryBook* HistoryController::GetUndoHistoryBook() const {
	return const_cast<HistoryBook*>(this->undoHistoryBook);
}
inline HistoryBook* HistoryController::GetRedoHistoryBook() const {
	return const_cast<HistoryBook*>(this->redoHistoryBook);
}
inline Registrar* HistoryController::GetRegistrar() const {
	return const_cast<Registrar*>(this->registrar);
}

#endif //_HISTORYCONTROLLER_H