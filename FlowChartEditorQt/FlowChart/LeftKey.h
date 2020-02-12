// _DownKEY_H

#ifndef _LEFTKEY_H
#define _LEFTKEY_H

#include <afxwin.h>
#include "AccessKey.h"

class DrawingPaper;
class LeftKey : public AccessKey {
public:
	static LeftKey* Instance();
	static void Destroy();
	virtual void OnKeyDown(DrawingPaper *canvas, UINT nChar, UINT nRepCnt, UINT nFlags);	
protected:
	LeftKey();
private:
	static LeftKey *instance;
};

#endif // _LEFTKEY_H