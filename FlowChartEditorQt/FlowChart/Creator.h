#ifndef _CREATOR_H
#define _CREATOR_H

typedef signed long int Long;

#include "Shape.h"

class Creator
{
public:
	Creator();
	~Creator();	
	NShape* Create(Long shapeID, Long x, Long y, Long width, Long height, 
		Long width2, Long height2, char (*contents)); // FactoryMethod 
	
};
#endif // CREATOR_H