#ifndef _REGISTRAR_H
#define _REGISTRAR_H

#define SHAPECOUNT 12

#include "../Shapes/Shape.h"

class Registrar {
public:
	Registrar();
	Registrar(const Registrar& source);
	~Registrar();
	Registrar& operator=(const Registrar& source);

	Long Register(NShape *shape);
	Long GetAt(SHAPE id);
private:
	Long lastNumbers[SHAPECOUNT];
};

#endif //_REGISTRAR_H