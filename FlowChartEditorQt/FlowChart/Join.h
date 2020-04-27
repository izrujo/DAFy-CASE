/******************************************************************
* 파일 이름 : Join.h
* 기능 : 연결선 콘크리트 클래스
* 작성자 : 송윤창
* 작성일자 : 2015년 3월 31일
*******************************************************************/

#ifndef _JOIN_H
#define _JOIN_H

#include "Line.h"

class Join : public Line {
public:
	Join(Long x, Long y, Long width, Long height, Long height2,
		QColor backGroundColor = QColor(255, 255, 255), Qt::PenStyle borderLine = Qt::SolidLine,
		QColor borderColor = QColor(0, 0, 0), String contents = static_cast<String>(""));
	~Join();
	Join(const Join& source);
	Join& operator =(const Join& source);

	virtual bool IsEqual(const NShape& other);
	virtual bool IsNotEqual(const NShape& other);

	virtual bool operator ==(const NShape& other);
	virtual bool operator !=(const NShape& other);

	virtual void DrawActiveShape(GObject *painter);

	virtual void Accept(FlowChartVisitor *draw);

	virtual NShape* Clone();

	virtual QRegion GetRegion();
	virtual QRegion GetRegion(Long thickness);
	virtual QRegion GetSelectionMarkerAllRegion();

	void ReSize(Long width, Long height, Long height2);

	virtual bool IsIncluded(QPoint point);
	virtual bool IsIncluded(const QRect& rect);

	Long GetHeight2() const;

	virtual void Copy(NShape *object);
	virtual void GetSelectionMarkerRect(int marker, QRect *rect);
	virtual int GetHitCode(const QPoint& point, const QRegion& region);

	virtual void GetLine(char(*line));
	virtual bool Identify(SHAPE identify);
	virtual bool IsStyle(Long style);

	virtual Long CenterOfGravityY() const;
	virtual Long CenterOfGravityX() const;

	virtual void DrawSelectionMarkers(GObject *painter, ScrollController *scrollController);
	void GetAttribute(Attribute *attribute);
private:
	Long height2;
};

inline bool Join::Identify(SHAPE identify) {
	return (identify == LINE || identify == JOIN) ? (true) : (false);
}

inline Long Join::GetHeight2() const {
	return this->height2;
}

inline Long Join::CenterOfGravityY() const {
	return (this->height >= 0) ? (this->y + this->height) : (this->y);
}

inline Long Join::CenterOfGravityX() const {
	//return ( height >= 0 )?( x ):( x + width);
	return this->x + this->width / 2;
}

#endif // _JOIN_H