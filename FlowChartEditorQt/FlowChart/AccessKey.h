// AccessKey.h

#ifndef _ACCESSKEY_H
#define _ACCESSKEY_H

#include <afxwin.h>
#define DISTANCE 5
class DrawingPaper;

class AccessKey{
public:
	static AccessKey* Instance();
	virtual void OnKeyDown(DrawingPaper *canvas, UINT nChar, UINT nRepCnt, UINT nFlags) = 0;
	virtual ~AccessKey() = 0;
protected:
	AccessKey();	
};
#endif _ACCESSKEY_H