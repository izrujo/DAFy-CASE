#include "SketchBook.h"
#include "Shape.h"

SketchBook::SketchBook(Long capacity)
	: canvasList(capacity), flowChartList(capacity), 
	fileOpenPathList(capacity) {
	this->capacity = capacity;
	this->length = 0;
	this->current = 0;
}

SketchBook::SketchBook(const SketchBook& source)
	: canvasList(source.canvasList), flowChartList(source.flowChartList),
	fileOpenPathList(source.fileOpenPathList) {
	Long i = 0;
	while (i < source.length) {
		this->canvasList.Modify(i, (const_cast<SketchBook&>(source)).canvasList[i]->Clone());
		this->flowChartList.Modify(i, (const_cast<SketchBook&>(source)).flowChartList[i]->Clone());
		i++;
	}
	this->capacity = source.capacity;
	this->length = source.length;
	this->current = source.current;
}

SketchBook::~SketchBook() {
	Long i = 0;
	while (i < this->length) {
		if (this->canvasList[i] != 0) {
			delete this->canvasList[i];
		}
		if (this->flowChartList[i] != 0) {
			delete this->flowChartList[i];
		}
		i++;
	}
}

SketchBook& SketchBook::operator=(const SketchBook& source) {
	NShape *canvas;
	NShape *flowChart;

	Long i = 0;
	while (i < this->length) {
		canvas = this->canvasList.GetAt(i);
		if (canvas != 0) {
			delete canvas;
		}
		flowChart = this->flowChartList.GetAt(i);
		if (flowChart != 0) {
			delete flowChart;
		}
		i++;
	}

	this->canvasList = source.canvasList;
	this->flowChartList = source.flowChartList;
	this->fileOpenPathList = source.fileOpenPathList;

	i = 0;
	while (i < source.GetLength()) {
		canvas = const_cast<SketchBook&>(source).canvasList.GetAt(i)->Clone();
		this->canvasList.Modify(i, canvas);
		flowChart = const_cast<SketchBook&>(source).flowChartList.GetAt(i)->Clone();
		this->flowChartList.Modify(i, flowChart);
		i++;
	}

	this->capacity = source.capacity;
	this->length = source.length;
	this->current = source.current;

	return *this;
}

Long SketchBook::Add(NShape *canvas, NShape *flowChart, QString fileOpenPath) {
	if (this->length < this->capacity) {
		this->current = this->canvasList.Store(this->length, canvas);
		this->flowChartList.Store(this->length, flowChart);
		this->fileOpenPathList.Store(this->length, fileOpenPath);
	}
	else {
		this->current = this->canvasList.AppendFromRear(canvas);
		this->flowChartList.AppendFromRear(flowChart);
		this->fileOpenPathList.AppendFromRear(fileOpenPath);
		this->capacity++;
	}
	this->length++;

	return this->current;
}

Long SketchBook::Insert(Long index, NShape *canvas, NShape *flowChart, QString fileOpenPath) {
	this->current = -1;
	this->current = this->canvasList.Insert(index, canvas);
	this->flowChartList.Insert(index, flowChart);
	this->fileOpenPathList.Insert(index, fileOpenPath);
	if (this->length >= this->capacity) {
		this->capacity += 128;
	}
	this->length++;

	return this->current;
}

Long SketchBook::Remove(Long index) {
	if (index >= 0 && index < this->GetLength()) {
		delete this->canvasList[index];
		this->current = this->canvasList.Delete(index);
		
		delete this->flowChartList[index];
		this->flowChartList.Delete(index);
		
		this->fileOpenPathList.Delete(index);

		this->length--;
	}
	return this->current;
}

Long SketchBook::ModifyFileOpenPath(QString fileName) {
	return this->fileOpenPathList.Modify(this->current, fileName);
}


NShape* SketchBook::GetCanvas(Long index) {
	return this->canvasList.GetAt(index);
}

NShape* SketchBook::GetFlowChart(Long index) {
	return this->flowChartList.GetAt(index);
}

QString& SketchBook::GetFileOpenPath(Long index) {
	return this->fileOpenPathList.GetAt(index);
}

void SketchBook::Draw(FlowChartVisitor *visitor) {
	Long i = 0;
	while (i< this->length) {
		this->canvasList.GetAt(i)->Accept(visitor);
		i++;
	}
}

Long SketchBook::Fold(QPoint point) {
	Long i = 0;

	while (i < this->length) {
		if (this->canvasList[i]->IsIncluded(point)) {
			this->current = i;
		}
		i++;
	}

	return this->current;
}

void SketchBook::Unfold(NShape *flowChart) {
	this->flowChartList[this->current] = flowChart;
}

void SketchBook::Update() {
	this->canvasList[this->current]->Paint(QColor(102, 204, 204), Qt::SolidLine, QColor(102, 204, 204));
	Long i = 0;
	while (i < this->length) {
		if (i != this->current) {
			this->canvasList[i]->Paint(QColor(235, 235, 235), Qt::SolidLine, QColor(235, 235, 235));
		}
		i++;
	}


}

void SketchBook::Arrange(Long x) {
	NShape *current;
	Long y = this->canvasList[0]->GetY();
	Long i = 0;
	while (i < this->length) {
		current = this->canvasList[i];
		current->Move(x, y);
		x += current->GetWidth();
		i++;
	}
}