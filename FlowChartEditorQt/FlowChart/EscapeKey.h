// _ESCAPEKEY_H

#ifndef _ESCAPEKEY_H
#define _ESCAPEKEY_H

#include <afxwin.h>
#include "AccessKey.h"

class DrawingPaper;
class EscapeKey : public AccessKey {
public:
	static EscapeKey* Instance();
	static void Destroy();
	virtual void OnKeyDown(DrawingPaper *canvas, UINT nChar, UINT nRepCnt, UINT nFlags);	
protected:
	EscapeKey();
private:
	static EscapeKey *instance;
};

#endif // _ESCAPEKEY_H