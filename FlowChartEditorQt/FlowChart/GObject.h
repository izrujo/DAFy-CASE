#ifndef _GOBJECT_H
#define _GOBJECT_H

#include <string>

#include <qrect.h>
#include <qstring.h>
#include <qpoint.h>	
#include <qbrush.h>

using namespace std;

typedef signed long int Long;

class QPainter;

class GObject {
public:
	GObject();
	GObject(const GObject& source);
	virtual ~GObject() = 0;
	GObject& operator=(const GObject& source);

	virtual void SetObject(QPainter *qPainter);

	virtual GObject* Clone() = 0;
	virtual string GetIdentify(); //Pen, Brush, Font

	//Painter 가상 함수 선언
	virtual GObject* SelectObject(const GObject& object);
	virtual GObject* CurrentObject(string identify);
	virtual void Update();

	virtual GObject* GetAt(Long index);
	virtual Long GetCapacity() const;
	virtual Long GetLength() const;

	//QtPainter 가상 함수 선언 및 정의
	virtual void Render(QPainter *painter, int x, int y) {}; //painter : 실제 화면
	virtual void Resize(Long width, Long height) {};

	virtual QRectF& BoundingRect(const QRectF& rectangle, int flags, const QString& text) { return QRectF(); };
	virtual QRect& BoundingRect(const QRect& rectangle, int flags, const QString& text) { return QRect(); };

	virtual void DrawArc(const QRectF& rectangle, int startAngle, int spanAngle) {};
	virtual void DrawArc(const QRect& rectangle, int startAngle, int spanAngle) {};

	virtual void DrawChord(const QRectF& rectangle, int startAngle, int spanAngle) {};
	virtual void DrawChord(const QRect& rectangle, int startAngle, int spanAngle) {};

	virtual void DrawConvexPolygon(const QPointF(*points), int pointCount) {};
	virtual void DrawConvexPolygon(const QPoint(*points), int pointCount) {};

	virtual void DrawEllipse(const QRectF& rectangle) {};
	virtual void DrawEllipse(const QRect& rectangle) {};
	virtual void DrawEllipse(const QPointF& center, float radiusX, float radiusY) {};
	virtual void DrawEllipse(const QPoint& center, int radiusX, int radiusY) {};

	virtual void DrawImage(const QRectF& target, const QString& fileName, const QRectF& source, int flags) {};
	virtual void DrawImage(const QRect& target, const QString& fileName, const QRect& source, int flags) {};

	virtual void DrawLine(const QPointF& point1, const QPointF& point2) {};
	virtual void DrawLine(const QPoint& point1, const QPoint& point2) {};

	virtual void DrawLines(const QPointF *points1, const QPointF *points2, int lineCount) {};
	virtual void DrawLines(const QPoint *points1, const QPoint *points2, int lineCount) {};

	virtual void DrawPath(const QPointF& start, const QPointF& end, const QPointF& control1, const QPointF& control2) {};

	virtual void DrawPie(const QRectF& rectangle, int startAngle, int spanAngle) {};
	virtual void DrawPie(const QRect& rectangle, int startAngle, int spanAngle) {};

	virtual void DrawPoint(const QPointF& point) {};
	virtual void DrawPoint(const QPoint& point) {};

	virtual void DrawPoints(const QPointF(*points), int pointCount) {};
	virtual void DrawPoints(const QPoint(*points), int pointCount) {};

	virtual void DrawPolygon(const QPointF(*points), int pointCount) {};
	virtual void DrawPolygon(const QPoint(*points), int pointCount) {};

	virtual void DrawPolyline(const QPointF(*points), int pointCount) {};
	virtual void DrawPolyline(const QPoint(*points), int pointCount) {};

	virtual void DrawRect(const QRectF& rectangle) {};
	virtual void DrawRect(const QRect& rectangle) {};

	virtual void DrawRects(const QRectF(*rectangles), int rectCount) {};
	virtual void DrawRects(const QRect(*rectangles), int rectCount) {};

	virtual void DrawRoundedRect(const QRectF& rectangle, float radiusX, float radiusY) {};
	virtual void DrawRoundedRect(const QRect& rectangle, float radiusX, float radiusY) {};

	virtual void DrawText(const QRectF& rectangle, int flags, const QString& text) {};
	virtual void DrawText(const QRect& rectangle, int flags, const QString& text) {};
	virtual void DrawText(int x, int y, const QString& text) {};

	virtual void EraseRect(const QRectF& rectangle) {};
	virtual void EraseRect(const QRect& rectangle) {};

	virtual void FillPath(const QPointF& start, const QPointF& end, const QPointF& control1, const QPointF& control2, const GObject& brush) {};

	virtual void FillRect(const QRectF& rectangle, const GObject& brush) {};
	virtual void FillRect(const QRect& rectangle, const GObject& brush) {};

	virtual int GetBackgroundMode() { return -1; };
	virtual void SetBackgroundMode(int mode) {};

	virtual int GetCompositionMode() { return -1; };
	virtual void SetCompositionMode(int mode) {};

	virtual int GetRenderHints() { return -1; };
	virtual void SetRenderHints(int hint) {};
};

#endif //_GOBJECT_H