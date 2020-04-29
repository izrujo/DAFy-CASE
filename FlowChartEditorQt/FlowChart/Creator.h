#ifndef _CREATOR_H
#define _CREATOR_H

typedef signed long int Long;

#include "Shape.h"

class Creator
{
public:
	Creator();
	~Creator();	
	NShape* Create(Long shapeID, float x, float y, float width, float height,
		float width2, float height2, char (*contents)); // FactoryMethod 
	
};
#endif // CREATOR_H