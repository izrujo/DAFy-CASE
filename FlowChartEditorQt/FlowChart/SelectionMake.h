// SelectionMake.h

#ifndef _SELECTIONMAKE_H
#define _SELECTIONMAKE_H

class DrawingPaper;
class SelectionMake {
public:
	SelectionMake();
	~SelectionMake();
	
	static void Create(DrawingPaper *canvas);
};

#endif //_SELECTIONMAKE_H