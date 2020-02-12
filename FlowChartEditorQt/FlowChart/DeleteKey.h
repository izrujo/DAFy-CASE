// _DELETEKEY_H

#ifndef _DELETEKEY_H
#define _DELETEKEY_H

#include "AccessKey.h"
#include <afxwin.h>

class DrawingPaper;

class DeleteKey : public AccessKey{
public:
	static DeleteKey* Instance();
	static void Destroy();
	virtual void OnKeyDown(DrawingPaper *canvas, UINT nChar, UINT nRepCnt, UINT nFlags);
protected:
	DeleteKey();
private:
	static DeleteKey* instance;	
};

#endif // _DELETEKEY_H