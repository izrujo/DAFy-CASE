#ifndef _COORDINATECONVERTER_H
#define _COORDINATECONVERTER_H

#include <qpoint.h>

typedef signed long int Long;
#include "Shape.h"
using namespace FlowChartShape;

class CoordinateConverter {
public:
	CoordinateConverter();
	CoordinateConverter(const CoordinateConverter& source);
	~CoordinateConverter();
	CoordinateConverter& operator=(const CoordinateConverter& source);

	void Update(Shape *a4Paper);
	QPoint ConvertVirtual(QPoint realPoint);
	QPoint ConvertReal(QPoint virtualPoint);

	QPoint GetZeroPoint() const;
private:
	QPoint zeroPoint;
};

inline QPoint CoordinateConverter::GetZeroPoint() const {
	return this->zeroPoint;
}

#endif //_COORDINATECONVERTER_H