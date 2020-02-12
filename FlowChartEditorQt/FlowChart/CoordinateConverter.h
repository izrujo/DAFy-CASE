#ifndef _COORDINATECONVERTER_H
#define _COORDINATECONVERTER_H

#include <afxwin.h>

typedef signed long int Long;
class Shape;

class CoordinateConverter {
public:
	CoordinateConverter();
	CoordinateConverter(const CoordinateConverter& source);
	~CoordinateConverter();
	CoordinateConverter& operator=(const CoordinateConverter& source);

	void Update(Shape *a4Paper);
	POINT ConvertVirtual(POINT realPoint);
	POINT ConvertReal(POINT virtualPoint);

	POINT GetZeroPoint() const;
private:
	POINT zeroPoint;
};

inline POINT CoordinateConverter::GetZeroPoint() const {
	return this->zeroPoint;
}

#endif //_COORDINATECONVERTER_H