// IterationMake.h

#ifndef _ITERATIONMAKE_H
#define _ITERATIONMAKE_H

class DrawingPaper;
class IterationMake{
public:
	IterationMake();

	~IterationMake();

	static void Create(DrawingPaper *canvas);
};

#endif //_ITERATIONMAKE_H