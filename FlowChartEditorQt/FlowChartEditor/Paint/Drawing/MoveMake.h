// MoveMake.h

#ifndef _MOVEMAKE_H
#define _MOVEMAKE_H

class DrawingPaper;

class MoveMake{
public:
	MoveMake();
	~MoveMake();
	static void Create(DrawingPaper *canvas);
};
#endif // _MOVEMAKE_H