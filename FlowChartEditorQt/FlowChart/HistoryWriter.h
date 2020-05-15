#ifndef _HISTORYWRITER_H
#define _HISTORYWRITER_H

typedef signed long int Long;
class HistoryBook;
class NShape;

class HistoryWriter {
public:
	HistoryWriter();
	HistoryWriter(const HistoryWriter& source);
	~HistoryWriter();
	HistoryWriter& operator=(const HistoryWriter& source);
	
	Long RememberAdd(NShape (*shapes), Long count); //For Undo
	Long RememberRemove(NShape(*shapes), Long count); //For Undo
	Long RememberOther(NShape(*shapes), Long count); //For Undo
	Long RememberRedo(); //For Undo
	Long RememberUndo(); //For Redo

	//200422 여러 개의 메모리 데이터를 관리할 필요가 있음.
	void ChangeHistoryBook(HistoryBook *undoHistoryBook, HistoryBook *redoHistoryBook);

	HistoryBook* GetUndoHistoryBook() const;
	HistoryBook* GetRedoHistoryBook() const;
private:
	HistoryBook *undoHistoryBook;
	HistoryBook *redoHistoryBook;
};

inline HistoryBook* HistoryWriter::GetUndoHistoryBook() const {
	return const_cast<HistoryBook*>(this->undoHistoryBook);
}

inline HistoryBook* HistoryWriter::GetRedoHistoryBook() const {
	return const_cast<HistoryBook*>(this->redoHistoryBook);
}

#endif //_HistoryWriter_H