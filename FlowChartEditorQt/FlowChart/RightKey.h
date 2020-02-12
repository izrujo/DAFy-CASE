// _RightKEY_H

#ifndef _RIGHTKEY_H
#define _RIGHTKEY_H

#include <afxwin.h>
#include "AccessKey.h"

class DrawingPaper;

class RightKey : public AccessKey {
public:
	static RightKey* Instance();
	static void Destroy();
	virtual void OnKeyDown(DrawingPaper *canvas, UINT nChar, UINT nRepCnt, UINT nFlags);	
protected:
	RightKey();
private:
	static RightKey *instance;
};

#endif // _RIGHTKEY_H