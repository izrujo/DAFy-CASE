#include "CoordinateConverter.h"

CoordinateConverter::CoordinateConverter() {
	this->zeroPoint = QPoint(0, 0);
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
	Long x = a4Paper->GetX();
	Long y = a4Paper->GetY();
	Long width = a4Paper->GetWidth();
	Long height = a4Paper->GetHeight();

	this->zeroPoint.setX(x + width / 2);
	this->zeroPoint.setY(y + height / 2);
}

QPoint CoordinateConverter::ConvertVirtual(QPoint realPoint) {
	QPoint virtualPoint;
	virtualPoint.setX(realPoint.x() - this->zeroPoint.x());
	virtualPoint.setY((realPoint.y() - this->zeroPoint.y()) * -1);

	return virtualPoint;
}

QPoint CoordinateConverter::ConvertReal(QPoint virtualPoint) {
	QPoint realPoint;
	realPoint.setX(virtualPoint.x() + this->zeroPoint.x());
	realPoint.setY(virtualPoint.y() * -1 + this->zeroPoint.y());

	return realPoint;
}