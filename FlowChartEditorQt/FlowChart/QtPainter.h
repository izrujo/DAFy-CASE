#ifndef _QTPAINTER_H
#define _QTPAINTER_H

#include "Painter.h"

class QPixmap;
class QPainter;

class QtPainter : public Painter {
public:
	QtPainter(Long width, Long height, QColor backgroundColor = QColor(255, 255, 255), Long capacity = 3);
	QtPainter(const QtPainter& source);
	virtual ~QtPainter();
	QtPainter& operator=(const QtPainter& source);

	virtual void Update(); //SetObject(QPainter Link)

	virtual GObject* Clone();

	//QPainter 함수 구현
	virtual void Render(QPainter *painter, int x, int y); //painter : 실제 화면
	virtual void Resize(Long width, Long height, QColor color = QColor(255, 255, 255));

	virtual QRectF& BoundingRect(const QRectF& rectangle, int flags, const QString& text);
	virtual QRect& BoundingRect(const QRect& rectangle, int flags, const QString& text);

	virtual void DrawArc(const QRectF& rectangle, int startAngle, int spanAngle);
	virtual void DrawArc(const QRect& rectangle, int startAngle, int spanAngle);

	virtual void DrawChord(const QRectF& rectangle, int startAngle, int spanAngle);
	virtual void DrawChord(const QRect& rectangle, int startAngle, int spanAngle);

	virtual void DrawConvexPolygon(const QPointF(*points), int pointCount);
	virtual void DrawConvexPolygon(const QPoint(*points), int pointCount);

	virtual void DrawEllipse(const QRectF& rectangle);
	virtual void DrawEllipse(const QRect& rectangle);
	virtual void DrawEllipse(const QPointF& center, float radiusX, float radiusY);
	virtual void DrawEllipse(const QPoint& center, int radiusX, int radiusY);

	virtual void DrawImage(const QRectF& target, const QString& fileName, const QRectF& source, int flags);
	virtual void DrawImage(const QRect& target, const QString& fileName, const QRect& source, int flags);

	virtual void DrawLine(const QPointF& point1, const QPointF& point2);
	virtual void DrawLine(const QPoint& point1, const QPoint& point2);

	virtual void DrawLines(const QPointF(*points1), const QPointF(*points2), int lineCount);
	virtual void DrawLines(const QPoint(*points1), const QPoint(*points2), int lineCount);

	virtual void DrawPath(const QPointF& start, const QPointF& end, const QPointF& control1, const QPointF& control2);

	virtual void DrawPie(const QRectF& rectangle, int startAngle, int spanAngle);
	virtual void DrawPie(const QRect& rectangle, int startAngle, int spanAngle);

	virtual void DrawPoint(const QPointF& point);
	virtual void DrawPoint(const QPoint& point);

	virtual void DrawPoints(const QPointF(*points), int pointCount);
	virtual void DrawPoints(const QPoint(*points), int pointCount);

	virtual void DrawPolygon(const QPointF(*points), int pointCount);
	virtual void DrawPolygon(const QPoint(*points), int pointCount);

	virtual void DrawPolyline(const QPointF(*points), int pointCount);
	virtual void DrawPolyline(const QPoint(*points), int pointCount);

	virtual void DrawRect(const QRectF& rectangle);
	virtual void DrawRect(const QRect& rectangle);

	virtual void DrawRects(const QRectF(*rectangles), int rectCount);
	virtual void DrawRects(const QRect(*rectangles), int rectCount);

	virtual void DrawRoundedRect(const QRectF& rectangle, float radiusX, float radiusY);
	virtual void DrawRoundedRect(const QRect& rectangle, float radiusX, float radiusY);

	virtual void DrawText(const QRectF& rectangle, int flags, const QString& text);
	virtual void DrawText(const QRect& rectangle, int flags, const QString& text);
	virtual void DrawText(int x, int y, const QString& text);

	virtual void EraseRect(const QRectF& rectangle);
	virtual void EraseRect(const QRect& rectangle);

	virtual void FillPath(const QPointF& start, const QPointF& end, const QPointF& control1, const QPointF& control2, const GObject& brush);

	virtual void FillRect(const QRectF& rectangle, const GObject& brush);
	virtual void FillRect(const QRect& rectangle, const GObject& brush);

	//속성 Flags 설정 함수
	virtual int GetBackgroundMode();
	virtual void SetBackgroundMode(int mode);

	virtual int GetCompositionMode();
	virtual void SetCompositionMode(int mode);

	virtual int GetRenderHints();
	virtual void SetRenderHints(int hints);
private:
	QPixmap *qPixmap;
	QPainter *qPainter;
};

#endif //_QTPAINTER_H