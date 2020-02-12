#ifndef _CREATOR_H
#define _CREATOR_H

typedef signed long int Long;

class Shape;

class Creator
{
public:
	Creator();
	~Creator();	
	Shape* Create(Long shapeID, Long x, Long y, Long width, Long height, Long width2, Long height2, char (*contents)); // FactoryMethod 
	
};
#endif // CREATOR_H