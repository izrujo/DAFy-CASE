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