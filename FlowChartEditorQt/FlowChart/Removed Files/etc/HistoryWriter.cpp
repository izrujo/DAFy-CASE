#include "HistoryWriter.h"
#include "HistoryBook.h"
#include "Historys.h"
#include "FlowChart.h"
#include "SelectingTool.h"

HistoryWriter::HistoryWriter() {
	this->undoHistoryBook = new HistoryBook;
	this->redoHistoryBook = new HistoryBook;
}

HistoryWriter::HistoryWriter(const HistoryWriter& source) {
	this->undoHistoryBook = new HistoryBook(*source.undoHistoryBook);
	this->redoHistoryBook = new HistoryBook(*source.redoHistoryBook);
}

HistoryWriter::~HistoryWriter() {
	if (this->undoHistoryBook != NULL) {
		delete this->undoHistoryBook;
	}
	if (this->redoHistoryBook != NULL) {
		delete this->redoHistoryBook;
	}
}

HistoryWriter& HistoryWriter::operator=(const HistoryWriter& source) {
	this->undoHistoryBook = new HistoryBook(*source.undoHistoryBook);
	this->redoHistoryBook = new HistoryBook(*source.redoHistoryBook);

	return *this;
}
#if 0
void HistoryWriter::Undo() {
	//=========실행 취소하면 마지막으로 실행했던 것만 되돌린다.===================
	History *History = this->undoHistoryBook->GetAt(this->undoHistoryBook->GetLength() - 1);

	//1. 처리했던 기호의 개수만큼 반복하다.
	Long i = History->GetLength() - 1;
	while (i >= 0) {
		//1.1. 현재 기호의 위치를 구하다.
		if (dynamic_cast<AddHistory*>(History)) { //1.2. 실행했던 처리가 '추가'였으면 지운다.
			//지울 때 기준을 positions으로 잡으면 positions 값이 더 작은 shape를 먼저 지우면 더 큰 positions이 망가짐.
			//NShape *shape = History->GetShape(i);
			//Long index = dynamic_cast<FlowChart*>(this->drawingPaper->flowChart)->Find(shape);
			Long index = History->GetPosition(i);
			this->drawingPaper->flowChart->Detach(index);
		}
		else if (dynamic_cast<RemoveHistory*>(History)) { //1.3. 실행했던 처리가 '삭제'였으면 현재 기호를 추가한다.
			Long position = History->GetPosition(History->GetLength() - (i + 1)); //더해야할때는 앞에부터
			if (position > this->drawingPaper->flowChart->GetLength()) {
				position = this->drawingPaper->flowChart->GetLength();
			}
			NShape *shape = History->GetShape(History->GetLength() - (i + 1));
			this->drawingPaper->flowChart->Insert(position, shape->Clone());
			/*
			//추가한 뒤 선택처리(DrawingTool LbuttonUp 참고)
			if (this->drawingPaper->templateSelected != NULL) {
				delete this->drawingPaper->templateSelected;
				this->drawingPaper->templateSelected = NULL;
			}
			this->drawingPaper->mode = DrawingPaper::SELECT;
			this->drawingPaper->tool = SelectingTool::Instance();
			*/
		}
		else if (dynamic_cast<OtherHistory*>(History)) { //1.4. 실행했던 처리가 '변경'이었으면 현재 기호로 치환한다.
			Long position = History->GetPosition(i);
			NShape *cloneShape = History->GetShape(i);
			NShape *shape = dynamic_cast<FlowChart*>(this->drawingPaper->flowChart)->GetAt(position);
			shape->Move(cloneShape->GetX(), cloneShape->GetY());
			shape->ReSize(cloneShape->GetWidth(), cloneShape->GetHeight());
			shape->Rewrite(cloneShape->GetContents());
			/*
			//변경한 뒤 선택처리(MovingTool, ResizingTool LButtonUp 참고)
			this->drawingPaper->mode = DrawingPaper::SELECT;
			this->drawingPaper->tool = SelectingTool::Instance();
			*/
		}
		this->undoHistoryBook->Quadrate(this->drawingPaper->flowChart);
		i--;
	}
	//처리가 끝나면 없애준다. (여기서 History의 소멸자 호출)
	this->undoHistoryBook->Remove(this->undoHistoryBook->GetLength() - 1);
}

void HistoryWriter::Redo() {
	//=========다시 실행하면 마지막으로 실행 취소했던 것만 다시 실행한다.===================
	History *History = this->redoHistoryBook->GetAt(this->redoHistoryBook->GetLength() - 1);
	//1. 처리했던 기호의 개수만큼 반복하다.
	Long i = History->GetLength() - 1;
	while (i >= 0) {
		//1.1. 현재 기호의 위치를 구하다.
		if (dynamic_cast<AddHistory*>(History)) { //1.2. 실행 취소했던 처리가 '추가'였으면 현재 기호를 추가한다.
			Long position = History->GetPosition(History->GetLength() - (i + 1)); //더해야할때는 앞에부터
			if (position > dynamic_cast<FlowChart*>(this->drawingPaper->flowChart)->GetLength()) {
				position = dynamic_cast<FlowChart*>(this->drawingPaper->flowChart)->GetLength();
			}
			NShape *shape = History->GetShape(History->GetLength() - (i + 1));
			this->drawingPaper->flowChart->Insert(position, shape->Clone());
		}
		else if (dynamic_cast<RemoveHistory*>(History)) { //1.3. 실행했던 처리가 '삭제'였으면 삭제한다.
			//NShape *shape = History->GetShape(i);
			//Long index = dynamic_cast<FlowChart*>(this->drawingPaper->flowChart)->Find(shape);
			Long index = History->GetPosition(i);
			this->drawingPaper->flowChart->Detach(index);
		}
		else if (dynamic_cast<OtherHistory*>(History)) { //1.4. 실행했던 처리가 '변경'이었으면 현재 기호로 치환한다.
			Long position = History->GetPosition(i);
			NShape *cloneShape = History->GetShape(i);
			NShape *shape = this->drawingPaper->flowChart->GetAt(position);
			shape->Move(cloneShape->GetX(), cloneShape->GetY());
			shape->ReSize(cloneShape->GetWidth(), cloneShape->GetHeight());
			shape->Rewrite(cloneShape->GetContents());
		}
		this->redoHistoryBook->Quadrate(this->drawingPaper->flowChart);
		i--;
	}
	//처리가 끝나면 없애준다. (여기서 History의 소멸자 호출)
	this->redoHistoryBook->Remove(this->redoHistoryBook->GetLength() - 1);
}
#endif
Long HistoryWriter::RememberAdd(NShape (*shapes), Long count) {
	//FlowChart에 Attach 등 기호를 추가한 처리 이후에 호출하기
	History *history = new AddHistory;
	Long i = 0;
	while (i < count) {
		history->Add(shapes[i].Clone());
		i++;
	}
	Long index = this->undoHistoryBook->Add(history);

	//undoHistoryBook가 Redo가 아닌 다른 처리로 인해 추가될 경우 redoHistoryBook는 없어진다.
	if (this->redoHistoryBook != 0) {
		this->redoHistoryBook->RemoveAll();
	}

	return index;
}

Long HistoryWriter::RememberRemove(NShape (*shapes), Long count) {
	//FlowChart에 Erase 등 기호를 없앤 처리 이전에 호출하기
	History *history = new RemoveHistory;
	Long i = 0;
	while (i < count) {
		history->Add(shapes[i].Clone());
		i++;
	}
	Long index = this->undoHistoryBook->Add(history);

	//undoHistoryBook가 Redo가 아닌 다른 처리로 인해 추가될 경우 redoHistoryBook는 없어진다.
	if (this->redoHistoryBook != 0) {
		this->redoHistoryBook->RemoveAll();
	}

	return index;
}

Long HistoryWriter::RememberOther(NShape (*shapes), Long count) {
	//FlowChart에 Move, ReSize, ReWirte 등 기호를 변경한 처리 이전에 호출하기
	History *history = new OtherHistory;
	Long i = 0;
	while (i < count) {
		history->Add(shapes[i].Clone());
		i++;
	}
	Long index = this->undoHistoryBook->Add(history);

	//undoHistoryBook가 Redo가 아닌 다른 처리로 인해 추가될 경우 redoHistoryBook는 없어진다.
	if (this->redoHistoryBook != 0) {
		this->redoHistoryBook->RemoveAll();
	}

	return index;
}

Long HistoryWriter::RememberRedo() {
	Long index;
	History *history = this->redoHistoryBook->GetAt(this->redoHistoryBook->GetLength() - 1);
	if (dynamic_cast<OtherHistory*>(history)) { //redoHistoryBook의 마지막 History이 other이면
		//해당 History이 가지고 있는 flowChart에서의 위치에 해당하는 기호들의 현재(redo 전) 정보를 가진 History을 만든다. 
		History *otherHistory = new OtherHistory;
		Long i = 0;
		while (i < history->GetLength()) {
			Long position = history->GetPosition(i);
			NShape *shape = this->drawingPaper->flowChart->GetAt(position);
			otherHistory->Add(shape->Clone(), position);
			i++;
		}
		index = this->undoHistoryBook->Add(otherHistory);
	}
	else { //add or remove : clone 저장
		index = this->undoHistoryBook->Add(history->Clone());
	}
	return index;
}

Long HistoryWriter::RememberUndo() {
	Long index;
	History *history = this->undoHistoryBook->GetAt(this->undoHistoryBook->GetLength() - 1);
	if (dynamic_cast<OtherHistory*>(history)) { //undoHistoryBook의 마지막 History이 other이면
		//해당 History이 가지고 있는 flowChart에서의 위치에 해당하는 기호들의 현재(undo 전) 정보를 가진 History을 만든다. 
		History *otherHistory = new OtherHistory;
		Long i = 0;
		while (i < history->GetLength()) {
			Long position = history->GetPosition(i);
			NShape *shape = this->drawingPaper->flowChart->GetAt(position);
			otherHistory->Add(shape->Clone(), position);
			i++;
		}
		index = this->redoHistoryBook->Add(otherHistory);
	}
	else { //add or remove : clone 저장
		index = this->redoHistoryBook->Add(history->Clone());
	}
	return index;
}

void HistoryWriter::ChangeHistoryBook(HistoryBook *undoHistoryBook, HistoryBook *redoHistoryBook) {
	this->undoHistoryBook = undoHistoryBook;
	this->redoHistoryBook = redoHistoryBook;
}