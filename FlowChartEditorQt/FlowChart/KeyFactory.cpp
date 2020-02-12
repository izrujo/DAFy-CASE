// KeyFactory.cpp

#include "KeyFactory.h"
#include "AccessKey.h"
#include "DrawingPaper.h"

#include "DeleteKey.h"
#include "UpKey.h"
#include "DownKey.h"
#include "LeftKey.h"
#include "RightKey.h"
#include "EscapeKey.h"

KeyFactory::KeyFactory(){
}

AccessKey* KeyFactory::Create(DrawingPaper *canvas, UINT nChar, UINT nRepCnt, UINT nFlags){
	AccessKey *accessKey = 0;

	switch( nChar ){		
		case VK_DELETE:
			accessKey = DeleteKey::Instance(); 
			canvas->mode = DrawingPaper::IDLE;
			canvas->indexOfSelected = -1;
			break;
		case VK_UP:			
			accessKey = UpKey::Instance();
			break;
		case VK_DOWN:			
			accessKey = DownKey::Instance();
			break;
		case VK_LEFT:
			accessKey = LeftKey::Instance();
			break;
		case VK_RIGHT:
			accessKey = RightKey::Instance();
			break;
		case VK_ESCAPE:
			accessKey = EscapeKey::Instance();			
			break;
		default: break;
	}
	return accessKey;
}