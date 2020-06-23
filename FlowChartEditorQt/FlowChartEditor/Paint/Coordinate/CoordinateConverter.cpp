#include "CoordinateConverter.h"

CoordinateConverter::CoordinateConverter() {
	this->zeroPoint = QPointF(0.0F, 0.0F);
}

CoordinateConverter::CoordinateConverter(const CoordinateConverter& source) {
	this->zeroPoint = source.zeroPoint;
}

CoordinateConverter::~CoordinateConverter() {

}

CoordinateConverter& CoordinateConverter::operator=(const CoordinateConverter& source) {
	this->zeroPoint = source.zeroPoint;

	return *this;
}

void CoordinateConverter::Update(NShape *a4Paper) {
	float x = a4Paper->GetX();
	float y = a4Paper->GetY();
	float width = a4Paper->GetWidth();
	float height = a4Paper->GetHeight();

	this->zeroPoint.setX(x + width / 2);
	this->zeroPoint.setY(y + height / 2);
}

QPointF CoordinateConverter::ConvertVirtual(QPointF realPoint) {
	QPointF virtualPoint;
	virtualPoint.setX(realPoint.x() - this->zeroPoint.x());
	virtualPoint.setY((realPoint.y() - this->zeroPoint.y()) * -1);

	return virtualPoint;
}

QPointF CoordinateConverter::ConvertReal(QPointF virtualPoint) {
	QPointF realPoint;
	realPoint.setX(virtualPoint.x() + this->zeroPoint.x());
	realPoint.setY(virtualPoint.y() * -1 + this->zeroPoint.y());

	return realPoint;
}