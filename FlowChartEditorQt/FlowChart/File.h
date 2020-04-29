// FILE_H
#ifndef FILE_H
#define FILE_H

#include <qstring.h>

typedef signed long int Long;

class DrawingPaper;

class File{
public:
	File();
	~File();
	Long Load(DrawingPaper *canvas, QString fileName);
	Long Save(DrawingPaper *canvas, QString fileName);
};
#endif // FILE_H