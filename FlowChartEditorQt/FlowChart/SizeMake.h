//SizeMake.h

#ifndef _SIZEMAKE_H
#define _SIZEMAKE_H

class DrawingPaper;
class SizeMake{
public:
	SizeMake();
	~SizeMake();
	static void Create(DrawingPaper *canvas);
};
#endif // _SIZEMAKE_H