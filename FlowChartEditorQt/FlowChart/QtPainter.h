#ifndef _QTPAINTER_H
#define _QTPAINTER_H

#include "Painter.h"

class QPixmap;
class QPainter;

class QtPainter : public Painter {
public:
	QtPainter(Long width, Long height, Long capacity = 3);
	QtPainter(const QtPainter& source);
	virtual ~QtPainter();
	QtPainter& operator=(const QtPainter& source);

	virtual void Update(Long index);

	virtual GObject* Clone();

	//QPainter 함수 구현
	QRectF BoundingRect(const QRectF& rectangle, int flags, const QString& text);
	QRect BoundingRect(const QRect& rectangle, int flags, const QString& text);
	
	void DrawArc(const QRectF& rectangle, int startAngle, int spanAngle);
	void DrawArc(const QRect& rectangle, int startAngle, int spanAngle);
	
	void DrawChord(const QRectF& rectangle, int startAngle, int spanAngle);
	void DrawChord(const QRect& rectangle, int startAngle, int spanAngle);

	void DrawConvexPolygon(const QPointF *points, int pointCount);
	void DrawConvexPolygon(const QPoint *points, int pointCount);

	void DrawEllipse(const QRectF& rectangle);
	void DrawEllipse(const QRect& rectangle);
	void DrawEllipse(const QPointF& center, float rediusX, float rediusY);
	void DrawEllipse(const QPoint& center, int rediusX, int rediusY);
	
	void DrawImage(const QRectF& target, const QString& fileName, const QRectF& source, int flags);
	void DrawImage(const QRect& target, const QString& fileName, const QRect& source, int flags);

	void DrawLine(const QPointF& p1, const QPointF& p2);
	void DrawLine(const QPoint& p1, const QPoint& p2);

	void DrawLines(const QPointF *pointPairs, int lineCount);
	void DrawLines(const QPoint *pointPairs, int lineCount);
	//속성 Flags 설정 함수
private:
	QPixmap *qPixmap;
	QPainter *qPainter;
};

#endif //_QTPAINTER_H