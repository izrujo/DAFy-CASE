#include "HistoryController.h"
#include "DrawingPaper.h"
#include "HistoryBook.h"
#include "Registrar.h"
#include "Historys.h"

HistoryController::HistoryController(DrawingPaper *canvas)
	: registrar(),
	undoHistoryBook(), redoHistoryBook() {
	this->canvas = canvas;
	this->previousFlowChart = this->canvas->flowChart->Clone();
	this->canvas->AttachObserver(this);
}

HistoryController::HistoryController(const HistoryController& source)
	: registrar(source.registrar),
	undoHistoryBook(source.undoHistoryBook), redoHistoryBook(source.redoHistoryBook) {
	this->canvas = source.canvas;
	this->previousFlowChart = this->canvas->flowChart->Clone();
}

HistoryController::~HistoryController() {
	if (this->registrar != 0) {
		delete this->registrar;
	}
	if (this->undoHistoryBook != 0) {
		delete this->undoHistoryBook;
	}
	if (this->redoHistoryBook != 0) {
		delete this->redoHistoryBook;
	}
	if (this->previousFlowChart != 0) {
		delete this->previousFlowChart;
	}
	this->canvas->DetachObserver(this);
}

HistoryController& HistoryController::operator=(const HistoryController& source) {
	this->canvas = source.canvas;
	this->registrar = source.registrar;
	this->undoHistoryBook = source.undoHistoryBook;
	this->redoHistoryBook = source.redoHistoryBook;
	this->previousFlowChart = this->canvas->flowChart->Clone();

	return *this;
}

void HistoryController::Update() {
	History *history;

	Long i;
	NShape *shape;
	SHAPE id;
	Long registrationNumber;
	Long index;

	NShape *currentFlowChart = this->canvas->flowChart;
	Long previousLength = this->previousFlowChart->GetLength();
	Long currentLength = currentFlowChart->GetLength();
	//1. 직전 순서도의 개수가 현재 순서도의 개수보다 적으면
	if (previousLength < currentLength) {
		//1.1.추가 역사를 만들다.
		history = new AddHistory;
		//1.2.현재 순서도 개수만큼 반복하다.
		i = 0;
		while (i < currentLength) {
			//1.2.1.shape를 가져오다.
			shape = currentFlowChart->GetAt(i);
			id = shape->GetIdentify();
			registrationNumber = shape->GetRegistrationNumber();
			//1.2.2.직전 순서도에서 찾다.
			index = this->previousFlowChart->FindByRegistrationNumber(id, registrationNumber);
			//1.2.3.못찾았으면 역사에 추가하다.
			if (index < 0) {
				history->Add(shape);
			}
			i++;
		}
	}
	//2. 직전 순서도의 개수가 현재 순서도의 개수보다 많으면
	else if (previousLength > currentLength) {
		//2.1.삭제 역사를 만들다.
		history = new RemoveHistory;
		//2.2.직전 순서도 개수만큼 반복하다.
		i = 0;
		while (i < previousLength) {
			//2.2.1.shape를 가져오다.
			shape = this->previousFlowChart->GetAt(i);
			id = shape->GetIdentify();
			registrationNumber = shape->GetRegistrationNumber();
			//2.2.2.현재 순서도에서 찾다.
			index = currentFlowChart->FindByRegistrationNumber(id, registrationNumber);
			//2.2.3.못찾았으면 역사에 추가하다.
			if (index < 0) {
				history->Add(shape);
			}
			i++;
		}
	}
	//3. 직전 순서도의 개수가 현재 순서도의 개수와 같으면
	else {
		//3.1.기타 역사를 만들다.
		history = new OtherHistory;
		//3.2.직전 순서도 개수만큼 반복하다.
		i = 0;
		while (i < previousLength) {
			//3.2.1.shape를 가져오다.
			shape = this->previousFlowChart->GetAt(i);
			id = shape->GetIdentify();
			registrationNumber = shape->GetRegistrationNumber();
			//3.2.2.현재 순서도에서 찾다.
			index = currentFlowChart->FindByRegistrationNumber(id, registrationNumber);
			//3.2.3.shape와 찾은 shape가 동일하지 않으면 shape를 역사에 추가하다.
			if (shape != currentFlowChart->GetAt(index)) {
				history->Add(shape);
			}
			i++;
		}
	}
	//4. 실행 취소 역사책에 역사를 추가하다.
	this->undoHistoryBook->Add(history);
	//5. 다시 실행 역사책을 비운다.
	if (this->redoHistoryBook->GetLength() > 0) {
		this->redoHistoryBook->RemoveAll();
	}
	//6. 직전 순서도를 현재 순서도로 바꾸다.
	this->previousFlowChart = currentFlowChart->Clone();
}

void HistoryController::Undo() {
	Long i;
	NShape *shape;
	Long index = -1;
	SHAPE id;
	Long registrationNumber;
	NShape *temp;

	//1. 실행 취소 역사책의 마지막 역사를 가져오다.
	Long historyLength = this->undoHistoryBook->GetLength();
	History *lastHistory = this->undoHistoryBook->GetAt(historyLength - 1);
	//2. 역사의 shape 개수만큼 반복하다.
	i = 0;
	while (i < lastHistory->GetLength()) {
		//2.1.shape를 가져오다.
		shape = lastHistory->GetShape(i);
		id = shape->GetIdentify();
		registrationNumber = shape->GetRegistrationNumber();
		//2.2.추가 역사면
		if (dynamic_cast<AddHistory*>(lastHistory)) {
			//2.2.1.shape를 캔버스의 순서도에서 찾다.
			index = this->canvas->flowChart->FindByRegistrationNumber(id, registrationNumber);
			//2.2.2.찾은 shape를 캔버스의 순서도에서 지우다.
			this->canvas->flowChart->Detach(index);
		}
		//2.3.삭제 역사면
		else if (dynamic_cast<RemoveHistory*>(lastHistory)) {
			//2.3.1.shape를 캔버스의 순서도에 추가하다.
			this->canvas->flowChart->Attach(shape->Clone());
		}
		//2.4.기타 역사면
		else if (dynamic_cast<OtherHistory*>(lastHistory)) {
			//2.4.1.shape를 캔버스의 순서도에서 찾다.
			index = this->canvas->flowChart->FindByRegistrationNumber(id, registrationNumber);
			//2.4.2.찾은 shape를 shape와 서로 바꾸다.
			temp = shape->Clone();
			shape = this->canvas->flowChart->GetAt(index)->Clone();
			this->canvas->flowChart->Swap(index, temp);
		}
		i++;
	}
	//3. 다시 실행 역사책에 역사를 추가하다.
	this->redoHistoryBook->Add(lastHistory->Clone());
	//4. 실행 취소 역사책에서 역사를 지우다.
	this->undoHistoryBook->Remove(historyLength - 1);
}

void HistoryController::Redo() {
	Long i;
	NShape *shape;
	Long index = -1;
	SHAPE id;
	Long registrationNumber;
	NShape *temp;

	//1. 다시 실행 역사책의 마지막 역사를 가져오다.
	Long historyLength = this->redoHistoryBook->GetLength();
	History *lastHistory = this->redoHistoryBook->GetAt(historyLength - 1);
	//2. 역사의 shape 개수만큼 반복하다.
	i = 0;
	while (i < historyLength) {
		//2.1.shape를 가져오다.
		shape = lastHistory->GetShape(i);
		id = shape->GetIdentify();
		registrationNumber = shape->GetRegistrationNumber();
		//2.2.추가 역사면
		if (dynamic_cast<AddHistory*>(lastHistory)) {
			//2.2.1.shape를 캔버스의 순서도에 추가하다.
			this->canvas->flowChart->Attach(shape->Clone());
		}
		//2.3.삭제 역사면
		else if (dynamic_cast<RemoveHistory*>(lastHistory)) {
			//2.3.1.shape를 캔버스의 순서도에서 찾다.
			index = this->canvas->flowChart->FindByRegistrationNumber(id, registrationNumber);
			//2.3.2.찾은 shape를 캔버스의 순서도에서 지우다.
			this->canvas->flowChart->Detach(index);
		}
		//2.4.기타 역사면
		else if (dynamic_cast<OtherHistory*>(lastHistory)) {
			//2.4.1.shape를 캔버스의 순서도에서 찾다.
			index = this->canvas->flowChart->FindByRegistrationNumber(id, registrationNumber);
			//2.4.2.찾은 shape를 shape와 서로 바꾸다.
			temp = shape->Clone();
			shape = this->canvas->flowChart->GetAt(index)->Clone();
			this->canvas->flowChart->Swap(index, temp);
		}
		i++;
	}
	//3. 실행 취소 역사책에 역사를 추가하다.
	this->undoHistoryBook->Add(lastHistory);
	//4. 다시 실행 역사책에서 역사를 지우다.
	this->redoHistoryBook->Remove(historyLength - 1);
}