#ifndef _COORDINATECONVERTER_H
#define _COORDINATECONVERTER_H

#include <qpoint.h>

typedef signed long int Long;
#include "Shape.h"

class CoordinateConverter {
public:
	CoordinateConverter();
	CoordinateConverter(const CoordinateConverter& source);
	~CoordinateConverter();
	CoordinateConverter& operator=(const CoordinateConverter& source);

	void Update(NShape *a4Paper);
	QPointF ConvertVirtual(QPointF realPoint);
	QPointF ConvertReal(QPointF virtualPoint);

	QPointF GetZeroPoint() const;
private:
	QPointF zeroPoint;
};

inline QPointF CoordinateConverter::GetZeroPoint() const {
	return this->zeroPoint;
}

#endif //_COORDINATECONVERTER_H