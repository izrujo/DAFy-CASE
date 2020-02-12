// FILE_H
#ifndef FILE_H
#define FILE_H

typedef signed long int Long;

class DrawingPaper;

class File{
public:
	File();
	~File();
	Long Load(DrawingPaper *canvas, const char (*fileName));
	Long Save(DrawingPaper *canvas, const char (*fileName));
};
#endif // FILE_H