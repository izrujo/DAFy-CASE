#ifndef _TUTORIALMARK_H
#define _TUTORIALMARK_H

#include "Shape.h"

class TutorialMark : public Shape {
public:
	TutorialMark(Long x, Long y, Long width, Long height, 
		QColor backGroundColor = QColor(255, 255, 255), QPen borderLine = QPen(Qt::SolidLine),
		QColor borderColor = QColor(0, 0, 0), String contents = static_cast<String>(""));

	virtual ~TutorialMark();

	TutorialMark(const TutorialMark& source);
	TutorialMark& operator =(const TutorialMark& source);

	virtual void Accept(FlowChartVisitor *draw);

	virtual Shape* Clone();

	virtual void GetRegion(Painter *painter, QRegion *region) {};
	virtual void GetRegion(Painter *painter, Long thickness, QRegion *region) {};
};

#endif //_TUTORIALMARK_H