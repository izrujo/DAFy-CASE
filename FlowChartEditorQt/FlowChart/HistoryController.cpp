#include "HistoryController.h"
#include "DrawingPaper.h"
#include "HistoryBook.h"
#include "Registrar.h"
#include "Historys.h"
#include "Block.h"

#include "../FlowChartEditor.h"
#include "Sheet.h"
#include "SheetBinder.h"
#include "SheetManager.h"

HistoryController::HistoryController(DrawingPaper *canvas) {
	this->canvas = canvas;
	this->undoHistoryBook = new HistoryBook;
	this->redoHistoryBook = new HistoryBook;
	this->previousFlowChart = this->canvas->flowChart->Clone();
	this->canvas->AttachObserver(this);
}

HistoryController::HistoryController(const HistoryController& source) {
	this->canvas = source.canvas;
	this->undoHistoryBook = new HistoryBook(*const_cast<HistoryController&>(source).undoHistoryBook);
	this->redoHistoryBook = new HistoryBook(*const_cast<HistoryController&>(source).redoHistoryBook);
	this->previousFlowChart = const_cast<HistoryController&>(source).previousFlowChart->Clone();
}

HistoryController::~HistoryController() {
	//HistoryBook, previousFlowChart 관리의 주체는 Sheet이다. 따라서 소멸시키지 않는다.
	this->canvas->DetachObserver(this);
}

HistoryController& HistoryController::operator=(const HistoryController& source) {
	this->canvas = source.canvas;
	this->undoHistoryBook = source.undoHistoryBook->Clone();
	this->redoHistoryBook = source.redoHistoryBook->Clone();
	this->previousFlowChart = source.previousFlowChart->Clone();

	return *this;
}

void HistoryController::Update() {
	History *history = 0;

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
				history->Add(shape->Clone());
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
				history->Add(shape->Clone());
			}
			i++;
		}
	}
	//3. 직전 순서도의 개수가 현재 순서도의 개수와 같고 직전 순서도와 현재 순서도가 같지 않으면
	else if (!(this->previousFlowChart->IsSame(*currentFlowChart))) {
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
				history->Add(shape->Clone());
			}
			i++;
		}
	}
	if (history != 0) {
		//4. 실행 취소 역사책에 역사를 추가하다.
		this->undoHistoryBook->Add(history);
		//5. 다시 실행 역사책을 비운다.
		if (this->redoHistoryBook->GetLength() > 0) {
			this->redoHistoryBook->RemoveAll();
		}
		//6. 직전 순서도를 현재 순서도로 바꾸다.
		this->previousFlowChart = currentFlowChart->Clone();
		FlowChartEditor *editor = static_cast<FlowChartEditor*>(this->canvas->parentWidget());
		editor->sheetManager->ModifyPreviousFlowChart(this->previousFlowChart);
	}
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
			lastHistory->Modify(i, this->canvas->flowChart->GetAt(index)->Clone());
			this->canvas->flowChart->Swap(index, temp);
		}
		i++;
	}
	if (historyLength > 0) {
		//3. 다시 실행 역사책에 역사를 추가하다.
		this->redoHistoryBook->Add(lastHistory->Clone());
		//4. 실행 취소 역사책에서 역사를 지우다.
		this->undoHistoryBook->Remove(historyLength - 1);

		this->previousFlowChart = this->canvas->flowChart->Clone();
		FlowChartEditor *editor = static_cast<FlowChartEditor*>(this->canvas->parentWidget());
		editor->sheetManager->ModifyPreviousFlowChart(this->previousFlowChart);
	}
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
	while (i < lastHistory->GetLength()) {
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
			lastHistory->Modify(i, this->canvas->flowChart->GetAt(index)->Clone());
			this->canvas->flowChart->Swap(index, temp);
		}
		i++;
	}
	if (historyLength > 0) {
		//3. 실행 취소 역사책에 역사를 추가하다.
		this->undoHistoryBook->Add(lastHistory->Clone());
		//4. 다시 실행 역사책에서 역사를 지우다.
		this->redoHistoryBook->Remove(historyLength - 1);

		this->previousFlowChart = this->canvas->flowChart->Clone();
		
		FlowChartEditor *editor = static_cast<FlowChartEditor*>(this->canvas->parentWidget());
		editor->sheetManager->ModifyPreviousFlowChart(this->previousFlowChart);
	}
}

void HistoryController::ChangeAll(HistoryBook *undoHistoryBook, HistoryBook *redoHistoryBook, 
	NShape *previousFlowChart) {
	this->undoHistoryBook = undoHistoryBook;
	this->redoHistoryBook = redoHistoryBook;
	this->previousFlowChart = previousFlowChart;
}