// _DownKEY_H

#ifndef _DOWNKEY_H
#define _DOWNKEY_H

#include <afxwin.h>
#include "AccessKey.h"

class DrawingPaper;
class DownKey : public AccessKey {
public:
	static DownKey* Instance();
	static void Destroy();	
	virtual void OnKeyDown(DrawingPaper *canvas, UINT nChar, UINT nRepCnt, UINT nFlags);	
protected:
	DownKey();
private:
	static DownKey *instance;
};

#endif // _DOWNKEY_H