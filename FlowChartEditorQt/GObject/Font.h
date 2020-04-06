#ifndef _FONT_H
#define _FONT_H

#include "GObject.h"

class Font : public GObject {
public:
	Font();
	Font(const Font& source);
	virtual ~Font() = 0;
	Font& operator=(const Font& source);

	virtual void SetObject(QPainter *qPainter);

	virtual string GetIdentify();
};

#endif //_FONT_H