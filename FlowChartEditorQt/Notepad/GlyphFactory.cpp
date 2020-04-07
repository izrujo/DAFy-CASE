#include "GlyphFactory.h"
#include "Glyph.h"
#include "Note.h"
#include "Row.h"
#include "Character.h"

GlyphFactory::GlyphFactory() {
}
GlyphFactory::GlyphFactory(const GlyphFactory& source) {
}
GlyphFactory::~GlyphFactory() {
}
Glyph* GlyphFactory::Make(const char(*content)) {
	Glyph *glyph = 0;
	if (content[0] == '\0') {
		glyph = new Note;
	}
	else if (content[0] == '\r' && content[1] == '\n') {
		glyph = new Line;
	}
	else if (!(content[0] & 0x80)) {
		glyph = new SingleByteCharacter(content[0]);
	}
	else if (content[0] & 0x80) {
		glyph = new DoubleByteCharacter(content);
	}
	return glyph;
}
/*
#include <iostream>
#include "Character.h"
#include "Composite.h"

int main(int argc, char *argv[]) {
	GlyphFactory glyphFactory;
	Glyph *note = glyphFactory.Make("");
	Glyph *glyph = glyphFactory.Make("\r\n");
	Glyph *line;

	Long index = note->Add(glyph); //새 줄을 만든다.
	line = note->GetAt(index); //만든 줄의 주소를 가져온다.

	glyph = glyphFactory.Make("a"); //a를 입력받는다.
	index = line->Add(glyph); //a를 현재 줄에 추가한다.
	glyph = line->GetAt(index); //추가한 문자의 주소를 가져온다.
	cout << glyph->GetContent() << endl; //추가한 문자를 출력한다.

	glyph = glyphFactory.Make("한"); //한을 입력받는다.
	index = line->Add(glyph); //한을 현재 줄에 추가한다.
	cout << line->GetAt(index)->GetContent() << endl; //추가한 문자의 주소를 가져와 출력한다.

	glyph = glyphFactory.Make("\r\n"); //엔터키를 입력받는다.
	index = note->Add(glyph); //새 줄을 만든다.
	line = note->GetAt(index); //만든 줄의 주소를 가져온다.
	glyph = glyphFactory.Make("3"); //3을 입력받는다.
	index = line->Add(glyph); //3을 현재 줄에 추가한다.
	cout << line->GetAt(index)->GetContent() << endl; //추가한 문자의 주소를 가져와 출력한다.

	Glyph *otherNote(note); //복사
	cout << otherNote->GetContent() << endl; //복사한 노트의 모든 문자들을 출력한다.

	glyph = glyphFactory.Make("김"); //김을 입력받는다.
	line = otherNote->GetAt(0); //복사한 노트의 첫 번째 줄의 주소를 가져온다.
	index = line->Add(glyph); //김을 현재 줄에 추가한다.
	glyph = line->GetAt(index); //추가한 문자의 주소를 가져온다.
	cout << glyph->GetContent() << endl; //추가한 문자를 출력한다.

	Glyph *another(otherNote); //치환
	cout << another->GetContent() << endl; //치환한 노트의 모든 문자들을 출력한다.

	if (note != 0) {
		delete note;
	}

	return 0;
}*/