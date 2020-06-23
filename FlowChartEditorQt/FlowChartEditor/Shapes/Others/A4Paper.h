
#ifndef _A4PAPER_H
#define _A4PAPER_H

#include "../Shape.h"

class A4Paper : public NShape {
public:
	A4Paper(float x, float y, float width, float height,
		QColor backGroundColor = QColor(255, 255, 255), Qt::PenStyle borderLine = Qt::SolidLine,
		QColor borderColor = QColor(0, 0, 0), String contents = static_cast<String>(""));
	virtual ~A4Paper();

	A4Paper(const A4Paper& source);
	A4Paper& operator =(const A4Paper& source);

	virtual void Accept(FlowChartVisitor *draw);

	virtual NShape* Clone();

	//마우스 드래그로 여러 도형 한번에 선택시 사용
	virtual QRegion GetRegion() { QRegion region; return region; };
	virtual QRegion GetRegion(Long thickness) { QRegion region; return region; };

	void SetIsMarking(bool isMarking);
	bool GetIsMarking() const;

	void ChangeMargin(float leftmargin, float topMargin, float rightMargin, float bottomMargin);
	float GetLeftMargin() const;
	float GetTopMargin() const;
	float GetRightMargin() const;
	float GetBottomMargin() const;
private:
	bool isMarking;
	float leftMargin;
	float topMargin;
	float rightMargin;
	float bottomMargin;
};

inline bool A4Paper::GetIsMarking() const {
	return this->isMarking;
}

inline float A4Paper::GetLeftMargin() const {
	return this->leftMargin;
}

inline float A4Paper::GetTopMargin() const {
	return this->topMargin;
}

inline float A4Paper::GetRightMargin() const {
	return this->rightMargin;
}

inline float A4Paper::GetBottomMargin() const {
	return this->bottomMargin;
}

#endif //_A4PAPER_H