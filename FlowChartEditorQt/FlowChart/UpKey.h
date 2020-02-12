// _UPKEY_H

#ifndef _UPKEY_H
#define _UPKEY_H

#include <afxwin.h>
#include "AccessKey.h"

class DrawingPaper;

class UpKey : public AccessKey {
public:
	static UpKey* Instance();
	static void Destroy();
	virtual void OnKeyDown(DrawingPaper *canvas, UINT nChar, UINT nRepCnt, UINT nFlags);	
protected:
	UpKey();
private:
	static UpKey *instance;
};

#endif // _UPKEY_H