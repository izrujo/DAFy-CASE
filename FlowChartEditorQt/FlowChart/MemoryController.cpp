#include "MemoryController.h"
#include "Memory.h"
#include "Executions.h"
#include "FlowChart.h"
#include "DrawingPaper.h"
#include "SelectingTool.h"

MemoryController::MemoryController(DrawingPaper *drawingPaper) {
	this->drawingPaper = drawingPaper;
	this->undoMemory = new Memory;
	this->redoMemory = new Memory;
}

MemoryController::MemoryController(const MemoryController& source) {
	this->drawingPaper = source.drawingPaper;
	this->undoMemory = new Memory(*source.undoMemory);
	this->redoMemory = new Memory(*source.redoMemory);
}

MemoryController::~MemoryController() {
	if (this->undoMemory != NULL) {
		delete this->undoMemory;
	}
	if (this->redoMemory != NULL) {
		delete this->redoMemory;
	}
}

MemoryController& MemoryController::operator=(const MemoryController& source) {
	this->drawingPaper = source.drawingPaper;
	this->undoMemory = new Memory(*source.undoMemory);
	this->redoMemory = new Memory(*source.redoMemory);

	return *this;
}

void MemoryController::Undo() {
	//=========실행 취소하면 마지막으로 실행했던 것만 되돌린다.===================
	Execution *execution = this->undoMemory->GetAt(this->undoMemory->GetLength() - 1);

	//1. 처리했던 기호의 개수만큼 반복하다.
	Long i = execution->GetLength() - 1;
	while (i >= 0) {
		//1.1. 현재 기호의 위치를 구하다.
		if (dynamic_cast<AddExecution*>(execution)) { //1.2. 실행했던 처리가 '추가'였으면 지운다.
			//지울 때 기준을 positions으로 잡으면 positions 값이 더 작은 shape를 먼저 지우면 더 큰 positions이 망가짐.
			//Shape *shape = execution->GetShape(i);
			//Long index = dynamic_cast<FlowChart*>(this->drawingPaper->flowChart)->Find(shape);
			Long index = execution->GetPosition(i);
			this->drawingPaper->flowChart->Detach(index);
		}
		else if (dynamic_cast<RemoveExecution*>(execution)) { //1.3. 실행했던 처리가 '삭제'였으면 현재 기호를 추가한다.
			Long position = execution->GetPosition(execution->GetLength() - (i + 1)); //더해야할때는 앞에부터
			if (position > this->drawingPaper->flowChart->GetLength()) {
				position = this->drawingPaper->flowChart->GetLength();
			}
			Shape *shape = execution->GetShape(execution->GetLength() - (i + 1));
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
		else if (dynamic_cast<OtherExecution*>(execution)) { //1.4. 실행했던 처리가 '변경'이었으면 현재 기호로 치환한다.
			Long position = execution->GetPosition(i);
			Shape *cloneShape = execution->GetShape(i);
			Shape *shape = dynamic_cast<FlowChart*>(this->drawingPaper->flowChart)->GetAt(position);
			shape->Move(cloneShape->GetX(), cloneShape->GetY());
			shape->ReSize(cloneShape->GetWidth(), cloneShape->GetHeight());
			shape->Rewrite(cloneShape->GetContents());
			/*
			//변경한 뒤 선택처리(MovingTool, ResizingTool LButtonUp 참고)
			this->drawingPaper->mode = DrawingPaper::SELECT;
			this->drawingPaper->tool = SelectingTool::Instance();
			*/
		}
		this->undoMemory->Quadrate(this->drawingPaper->flowChart);
		i--;
	}
	//처리가 끝나면 없애준다. (여기서 execution의 소멸자 호출)
	this->undoMemory->Remove(this->undoMemory->GetLength() - 1);
}

void MemoryController::Redo() {
	//=========다시 실행하면 마지막으로 실행 취소했던 것만 다시 실행한다.===================
	Execution *execution = this->redoMemory->GetAt(this->redoMemory->GetLength() - 1);
	//1. 처리했던 기호의 개수만큼 반복하다.
	Long i = execution->GetLength() - 1;
	while (i >= 0) {
		//1.1. 현재 기호의 위치를 구하다.
		if (dynamic_cast<AddExecution*>(execution)) { //1.2. 실행 취소했던 처리가 '추가'였으면 현재 기호를 추가한다.
			Long position = execution->GetPosition(execution->GetLength() - (i + 1)); //더해야할때는 앞에부터
			if (position > dynamic_cast<FlowChart*>(this->drawingPaper->flowChart)->GetLength()) {
				position = dynamic_cast<FlowChart*>(this->drawingPaper->flowChart)->GetLength();
			}
			Shape *shape = execution->GetShape(execution->GetLength() - (i + 1));
			this->drawingPaper->flowChart->Insert(position, shape->Clone());
		}
		else if (dynamic_cast<RemoveExecution*>(execution)) { //1.3. 실행했던 처리가 '삭제'였으면 삭제한다.
			//Shape *shape = execution->GetShape(i);
			//Long index = dynamic_cast<FlowChart*>(this->drawingPaper->flowChart)->Find(shape);
			Long index = execution->GetPosition(i);
			this->drawingPaper->flowChart->Detach(index);
		}
		else if (dynamic_cast<OtherExecution*>(execution)) { //1.4. 실행했던 처리가 '변경'이었으면 현재 기호로 치환한다.
			Long position = execution->GetPosition(i);
			Shape *cloneShape = execution->GetShape(i);
			Shape *shape = this->drawingPaper->flowChart->GetAt(position);
			shape->Move(cloneShape->GetX(), cloneShape->GetY());
			shape->ReSize(cloneShape->GetWidth(), cloneShape->GetHeight());
			shape->Rewrite(cloneShape->GetContents());
		}
		this->redoMemory->Quadrate(this->drawingPaper->flowChart);
		i--;
	}
	//처리가 끝나면 없애준다. (여기서 execution의 소멸자 호출)
	this->redoMemory->Remove(this->redoMemory->GetLength() - 1);
}

Long MemoryController::RememberAdd(Long(*position), Long count) {
	//FlowChart에 Attach 등 기호를 추가한 처리 이후에 호출하기
	Execution *execution = new AddExecution;
	Long i = 0;
	while (i < count) {
		Shape *shape = this->drawingPaper->flowChart->GetAt(position[i]);
		execution->Add(shape->Clone(), position[i]);
		i++;
	}
	Long index = this->undoMemory->Add(execution);

	//undoMemory가 Redo가 아닌 다른 처리로 인해 추가될 경우 redoMemory는 없어진다.
	if (this->redoMemory != 0) {
		this->redoMemory->RemoveAll();
	}

	return index;
}

Long MemoryController::RememberRemove(Long(*position), Long count) {
	//FlowChart에 Erase 등 기호를 없앤 처리 이전에 호출하기
	Execution *execution = new RemoveExecution;
	Long i = 0;
	while (i < count) {
		Shape *shape = this->drawingPaper->flowChart->GetAt(position[i]);
		execution->Add(shape->Clone(), position[i]);
		i++;
	}
	Long index = this->undoMemory->Add(execution);

	//undoMemory가 Redo가 아닌 다른 처리로 인해 추가될 경우 redoMemory는 없어진다.
	if (this->redoMemory != 0) {
		this->redoMemory->RemoveAll();
	}

	return index;
}

Long MemoryController::RememberOther(Long(*position), Long count) {
	//FlowChart에 Move, ReSize, ReWirte 등 기호를 변경한 처리 이전에 호출하기
	Execution *execution = new OtherExecution;
	Long i = 0;
	while (i < count) {
		Shape *shape = this->drawingPaper->flowChart->GetAt(position[i]);
		execution->Add(shape->Clone(), position[i]);
		i++;
	}
	Long index = this->undoMemory->Add(execution);

	//undoMemory가 Redo가 아닌 다른 처리로 인해 추가될 경우 redoMemory는 없어진다.
	if (this->redoMemory != 0) {
		this->redoMemory->RemoveAll();
	}

	return index;
}

Long MemoryController::RememberRedo() {
	Long index;
	Execution *execution = this->redoMemory->GetAt(this->redoMemory->GetLength() - 1);
	if (dynamic_cast<OtherExecution*>(execution)) { //redoMemory의 마지막 execution이 other이면
		//해당 execution이 가지고 있는 flowChart에서의 위치에 해당하는 기호들의 현재(redo 전) 정보를 가진 execution을 만든다. 
		Execution *otherExecution = new OtherExecution;
		Long i = 0;
		while (i < execution->GetLength()) {
			Long position = execution->GetPosition(i);
			Shape *shape = this->drawingPaper->flowChart->GetAt(position);
			otherExecution->Add(shape->Clone(), position);
			i++;
		}
		index = this->undoMemory->Add(otherExecution);
	}
	else { //add or remove : clone 저장
		index = this->undoMemory->Add(execution->Clone());
	}
	return index;
}

Long MemoryController::RememberUndo() {
	Long index;
	Execution *execution = this->undoMemory->GetAt(this->undoMemory->GetLength() - 1);
	if (dynamic_cast<OtherExecution*>(execution)) { //undoMemory의 마지막 execution이 other이면
		//해당 execution이 가지고 있는 flowChart에서의 위치에 해당하는 기호들의 현재(undo 전) 정보를 가진 execution을 만든다. 
		Execution *otherExecution = new OtherExecution;
		Long i = 0;
		while (i < execution->GetLength()) {
			Long position = execution->GetPosition(i);
			Shape *shape = this->drawingPaper->flowChart->GetAt(position);
			otherExecution->Add(shape->Clone(), position);
			i++;
		}
		index = this->redoMemory->Add(otherExecution);
	}
	else { //add or remove : clone 저장
		index = this->redoMemory->Add(execution->Clone());
	}
	return index;
}

void MemoryController::Quadrate() {
	//1. undoMemory를 일치시킨다.
	this->undoMemory->Quadrate(this->drawingPaper->flowChart);
	//2. redoMemory를 일치시킨다.
	this->redoMemory->Quadrate(this->drawingPaper->flowChart);
}