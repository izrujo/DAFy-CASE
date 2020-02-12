#include "CoordinateConverter.h"
#include "Shape.h"

CoordinateConverter::CoordinateConverter() {
	this->zeroPoint = { 0, 0 };
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

void CoordinateConverter::Update(Shape *a4Paper) {
	Long x = a4Paper->GetX();
	Long y = a4Paper->GetY();
	Long width = a4Paper->GetWidth();
	Long height = a4Paper->GetHeight();

	this->zeroPoint.x = x + width / 2;
	this->zeroPoint.y = y + height / 2;
}

POINT CoordinateConverter::ConvertVirtual(POINT realPoint) {
	POINT virtualPoint;
	virtualPoint.x = realPoint.x - this->zeroPoint.x;
	virtualPoint.y = (realPoint.y - this->zeroPoint.y) * -1;

	return virtualPoint;
}

POINT CoordinateConverter::ConvertReal(POINT virtualPoint) {
	POINT realPoint;
	realPoint.x = virtualPoint.x + this->zeroPoint.x;
	realPoint.y = virtualPoint.y * -1 + this->zeroPoint.y;

	return realPoint;
}