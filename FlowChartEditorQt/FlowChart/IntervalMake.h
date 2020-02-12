// IntervalMake.h

#ifndef _INTERVALMAKE_H
#define _INTERVALMAKE_H

class DrawingPaper;

class IntervalMake {
public:
	IntervalMake();
	~IntervalMake();
	static void Create(DrawingPaper *canvas);
};

#endif // _INTERVALMAKE_H
