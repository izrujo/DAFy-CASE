//SequenceMake.h

#ifndef _SEQUENCEMAKE_H
#define _SEQUENCEMAKE_H

class DrawingPaper;

class SequenceMake{
public:
	SequenceMake();

	static void Create(DrawingPaper *canvas);

	~SequenceMake();
};
#endif //_SEQUENCEMAKE_H