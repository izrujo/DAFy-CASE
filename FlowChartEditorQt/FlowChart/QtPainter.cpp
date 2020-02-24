#include "QtPainter.h"
#include "QtBrush.h"

#include <qpainter.h>
#include <qpixmap.h>

QtPainter::QtPainter(Long width, Long height, Long capacity)
	: Painter(capacity) {
	this->qPixmap = new QPixmap(width, height);
	this->qPainter = new QPainter(this->qPixmap);
}

QtPainter::QtPainter(const QtPainter& source)
	: Painter(source) {
	this->qPixmap = source.qPixmap;
	this->qPainter = source.qPainter;
}

QtPainter::~QtPainter() {
	if (this->qPixmap != NULL) {
		delete this->qPixmap;
	}
	if (this->qPainter != NULL) {
		delete this->qPainter;
	}
}

QtPainter& QtPainter::operator=(const QtPainter& source) {
	Painter::operator=(source);

	return *this;
}

void QtPainter::Update(Long index) {
	GObject *object = this->objects.GetAt(index);
	object->SetObject(this->qPainter);
}

GObject* QtPainter::Clone() {
	return new QtPainter(*this);
}

//QPainter 함수 구현
void QtPainter::Render(QPainter *painter, int x, int y) {
	painter->drawPixmap(x, y, *this->qPixmap);
}

void QtPainter::Resize(Long width, Long height) {
	if (this->qPixmap != NULL) {
		delete this->qPixmap;
		this->qPixmap = new QPixmap(width, height);
	}
	if (this->qPainter != NULL) {
		delete this->qPainter;
		this->qPainter = new QPainter(this->qPixmap);
	}
}

QRectF& QtPainter::BoundingRect(const QRectF& rectangle, int flags, const QString& text) {
	return this->qPainter->boundingRect(rectangle, flags, text);
}

QRect& QtPainter::BoundingRect(const QRect& rectangle, int flags, const QString& text) {
	return this->qPainter->boundingRect(rectangle, flags, text);
}

void QtPainter::DrawArc(const QRectF& rectangle, int startAngle, int spanAngle) {
	this->qPainter->drawArc(rectangle, startAngle, spanAngle);
}

void QtPainter::DrawArc(const QRect& rectangle, int startAngle, int spanAngle) {
	this->qPainter->drawArc(rectangle, startAngle, spanAngle);
}

void QtPainter::DrawChord(const QRectF& rectangle, int startAngle, int spanAngle) {
	this->qPainter->drawChord(rectangle, startAngle, spanAngle);
}

void QtPainter::DrawChord(const QRect& rectangle, int startAngle, int spanAngle) {
	this->qPainter->drawChord(rectangle, startAngle, spanAngle);
}

void QtPainter::DrawConvexPolygon(const QPointF *points, int pointCount) {
	this->qPainter->drawConvexPolygon(points, pointCount);
}

void QtPainter::DrawConvexPolygon(const QPoint *points, int pointCount) {
	this->qPainter->drawConvexPolygon(points, pointCount);
}

void QtPainter::DrawEllipse(const QRectF& rectangle) {
	this->qPainter->drawEllipse(rectangle);
}

void QtPainter::DrawEllipse(const QRect& rectangle) {
	this->qPainter->drawEllipse(rectangle);
}

void QtPainter::DrawEllipse(const QPointF& center, float radiusX, float radiusY) {
	this->qPainter->drawEllipse(center, radiusX, radiusY);
}

void QtPainter::DrawEllipse(const QPoint& center, int radiusX, int radiusY) {
	this->qPainter->drawEllipse(center, radiusX, radiusY);
}

void QtPainter::DrawImage(const QRectF& target, const QString& fileName, const QRectF& source, int flags) {
	this->qPainter->drawImage(target, QImage(fileName), source, (Qt::ImageConversionFlags)flags);
}

void QtPainter::DrawImage(const QRect& target, const QString& fileName, const QRect& source, int flags) {
	this->qPainter->drawImage(target, QImage(fileName), source, (Qt::ImageConversionFlags)flags);
}

void QtPainter::DrawLine(const QPointF& point1, const QPointF& point2) {
	this->qPainter->drawLine(point1, point2);
}

void QtPainter::DrawLine(const QPoint& point1, const QPoint& point2) {
	this->qPainter->drawLine(point1, point2);
}

void QtPainter::DrawLines(const QPointF(*points1), const QPointF(*points2), int lineCount) {
	QPointF(*pointPairs);
	int i = 0;
	while (i < lineCount) {
		pointPairs[i] = points1[i];
		pointPairs[i + 1] = points2[i];
		i += 2;
	}
	this->qPainter->drawLines(pointPairs, lineCount);
}

void QtPainter::DrawLines(const QPoint(*points1), const QPoint(*points2), int lineCount) {
	QPoint(*pointPairs);
	int i = 0;
	while (i < lineCount) {
		pointPairs[i] = points1[i];
		pointPairs[i + 1] = points2[i];
		i += 2;
	}
	this->qPainter->drawLines(pointPairs, lineCount);
}

void QtPainter::DrawPath(const QPointF& start, const QPointF& end, const QPointF& control1, const QPointF& control2) {
	QPainterPath path(start);
	path.cubicTo(control1, control2, end);
	this->qPainter->drawPath(path);
}

void QtPainter::DrawPie(const QRectF& rectangle, int startAngle, int spanAngle) {
	this->qPainter->drawPie(rectangle, startAngle, spanAngle);
}

void QtPainter::DrawPie(const QRect& rectangle, int startAngle, int spanAngle) {
	this->qPainter->drawPie(rectangle, startAngle, spanAngle);
}

void QtPainter::DrawPoint(const QPointF& point) {
	this->qPainter->drawPoint(point);
}
void QtPainter::DrawPoint(const QPoint& point) {
	this->qPainter->drawPoint(point);
}

void QtPainter::DrawPoints(const QPointF(*points), int pointCount) {
	this->qPainter->drawPoints(points, pointCount);
}

void QtPainter::DrawPoints(const QPoint(*points), int pointCount) {
	this->qPainter->drawPoints(points, pointCount);
}

void QtPainter::DrawPolygon(const QPointF(*points), int pointCount) {
	this->qPainter->drawPolygon(points, pointCount);
}

void QtPainter::DrawPolygon(const QPoint(*points), int pointCount) {
	this->qPainter->drawPolygon(points, pointCount);
}

void QtPainter::DrawPolyline(const QPointF(*points), int pointCount) {
	this->qPainter->drawPolyline(points, pointCount);
}

void QtPainter::DrawPolyline(const QPoint(*points), int pointCount) {
	this->qPainter->drawPolyline(points, pointCount);
}

void QtPainter::DrawRect(const QRectF& rectangle) {
	this->qPainter->drawRect(rectangle);
}

void QtPainter::DrawRect(const QRect& rectangle) {
	this->qPainter->drawRect(rectangle);
}

void QtPainter::DrawRects(const QRectF(*rectangles), int rectCount) {
	this->qPainter->drawRects(rectangles, rectCount);
}

void QtPainter::DrawRects(const QRect(*rectangles), int rectCount) {
	this->qPainter->drawRects(rectangles, rectCount);
}

void QtPainter::DrawRoundedRect(const QRectF& rectangle, float radiusX, float radiusY) {
	this->qPainter->drawRoundedRect(rectangle, radiusX, radiusY);
}

void QtPainter::DrawRoundedRect(const QRect& rectangle, float radiusX, float radiusY) {
	this->qPainter->drawRoundedRect(rectangle, radiusX, radiusY);
}

void QtPainter::DrawText(const QRectF& rectangle, int flags, const QString& text) {
	this->qPainter->drawText(rectangle, flags, text);
}

void QtPainter::DrawText(const QRect& rectangle, int flags, const QString& text) {
	this->qPainter->drawText(rectangle, flags, text);
}

void QtPainter::DrawText(int x, int y, const QString& text) {
	this->qPainter->drawText(x, y, text);
}

void QtPainter::EraseRect(const QRectF& rectangle) {
	this->qPainter->eraseRect(rectangle);
}

void QtPainter::EraseRect(const QRect& rectangle) {
	this->qPainter->eraseRect(rectangle);
}

void QtPainter::FillPath(const QPointF& start, const QPointF& end, const QPointF& control1, const QPointF& control2, const GObject& brush) {
	QPainterPath path(start);
	path.cubicTo(control1, control2, end);
	this->qPainter->fillPath(path, QBrush(dynamic_cast<QtBrush&>(const_cast<GObject&>(brush))));
}

void QtPainter::FillRect(const QRectF& rectangle, const GObject& brush) {
	this->qPainter->fillRect(rectangle, QBrush(dynamic_cast<QtBrush&>(const_cast<GObject&>(brush))));
}

void QtPainter::FillRect(const QRect& rectangle, const GObject& brush) {
	this->qPainter->fillRect(rectangle, QBrush(dynamic_cast<QtBrush&>(const_cast<GObject&>(brush))));
}

int QtPainter::GetBackgroundMode() {
	return this->qPainter->backgroundMode();
}

void QtPainter::SetBackgroundMode(int mode) {
	this->qPainter->setBackgroundMode((Qt::BGMode)mode);
}

int QtPainter::GetCompositionMode() {
	return this->qPainter->compositionMode();
}

void QtPainter::SetCompositionMode(int mode) {
	this->qPainter->setCompositionMode((QPainter::CompositionMode)mode);
}