// KeyFactory.h

#ifndef _KEYFACTORY_H
#define _KEYFACTORY_H

#include <afxwin.h>

class AccessKey;
class DrawingPaper;

class KeyFactory{
public:	
	static AccessKey* Create(DrawingPaper *canvas, UINT nChar, UINT nRepCnt, UINT nFlags);
protected:
	KeyFactory();
};
#endif // _KEYFACOTRY_H