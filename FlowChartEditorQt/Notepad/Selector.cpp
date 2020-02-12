#include "Selector.h"
#include "NotepadForm.h"
#include "GlyphFactory.h"
#include "Composite.h"

Selector::Selector(NotepadForm *notepadForm, Long noteStartPosition, Long lineStartPosition, Long noteEndPosition, Long lineEndPosition) {
	this->notepadForm = notepadForm;
	this->noteStartPosition = noteStartPosition;
	this->lineStartPosition = lineStartPosition;
	this->noteEndPosition = noteEndPosition;
	this->lineEndPosition = lineEndPosition;
}

Selector::Selector(const Selector& source) {
	this->notepadForm = source.notepadForm;
	this->noteStartPosition = source.noteStartPosition;
	this->lineStartPosition = source.lineStartPosition;
	this->noteEndPosition = source.noteEndPosition;
	this->lineEndPosition = source.lineEndPosition;
}

Selector::~Selector() {

}

Selector& Selector::operator=(const Selector& source) {
	this->notepadForm = source.notepadForm;
	this->noteStartPosition = source.noteStartPosition;
	this->lineStartPosition = source.lineStartPosition;
	this->noteEndPosition = source.noteEndPosition;
	this->lineEndPosition = source.lineEndPosition;
	return *this;
}

void Selector::Left(Long row, Long startColumn, Long endColumn) {
	Glyph *line;
	//1. 지우는 중이 아니면
	if (this->noteStartPosition >= this->noteEndPosition &&
		(this->noteStartPosition != this->noteEndPosition || this->lineStartPosition >= this->lineEndPosition)) {
		//1.1. 하이라이트가 없거나 위로 올라왔으면
		if (this->notepadForm->highlight->GetLength() < 1 || row < this->noteEndPosition) {
			//1.1.1. 줄을 만들다.
			GlyphFactory glyphFactory;
			line = glyphFactory.Make("\r\n");
			//1.1.2. 줄을 하이라이트에 추가하다.
			this->notepadForm->highlight->Add(0, line);
		}
		//1.2. 하이라이트의 첫 번째 줄을 가져오다.
		line = this->notepadForm->highlight->GetAt(0);
	}
	//2. 지우는 중이면
	else {
		//2.1. 위로 올라왔으면 하이라이트의 마지막 줄을 지우다.
		if (row < this->noteEndPosition) {
			this->notepadForm->highlight->Remove(this->notepadForm->highlight->GetLength() - 1);
		}
		//2.2. 하이라이트의 마지막 줄을 가져오다.
		line = this->notepadForm->highlight->GetAt(this->notepadForm->highlight->GetLength() - 1);
	}
	Glyph *currentLine = this->notepadForm->note->GetAt(row);
	//3. 위로 올라왔으면 현재 줄의 개수부터, 안올라왔으면 줄끝자리부터 시작열까지 반복하다.
	Long i = this->lineEndPosition;
	if (row < this->noteEndPosition) {
		i = currentLine->GetLength();
	}
	while (i > startColumn) {
		//3.1. 줄의 끝을 지우다.
		line->Remove(line->GetLength() - 1);
		i--;
	}
	//4. 시작열부터 끝열까지 반복하다.
	i = startColumn;
	while (i > endColumn) {
		//4.1. 현재 줄에서 현재 열의 글자를 가져오다.
		Glyph *character = currentLine->GetAt(i - 1);
		//4.2. 가져온 줄에 글자의 클론을 추가하다.
		line->Add(0, character->Clone());
		i--;
	}
	//5. 문서끝자리를 구하다.
	this->noteEndPosition = row;
	//6. 줄끝자리를 구하다.
	this->lineEndPosition = endColumn;
}

void Selector::Right(Long row, Long startColumn, Long endColumn) {
	Glyph *line;
	//1. 지우는 중이 아니면
	if (this->noteStartPosition <= this->noteEndPosition &&
		(this->noteStartPosition != this->noteEndPosition || this->lineStartPosition <= this->lineEndPosition)) {
		//1.1. 하이라이트가 없거나 아래로 내려왔으면
		if (this->notepadForm->highlight->GetLength() < 1 || row > this->noteEndPosition) {
			//1.1.1. 줄을 만들다.
			GlyphFactory glyphFactory;
			line = glyphFactory.Make("\r\n");
			//1.1.2. 줄을 하이라이트에 추가하다.
			this->notepadForm->highlight->Add(line);
		}
		//1.2. 하이라이트의 마지막 줄을 가져오다.
		line = this->notepadForm->highlight->GetAt(this->notepadForm->highlight->GetLength() - 1);
	}
	//2. 지우는 중이면
	else {
		//2.1. 아래려 내려왔으면 하이라이트의 첫 줄을 지우다.
		if (row > this->noteEndPosition) {
			this->notepadForm->highlight->Remove(0);
		}
		//2.2. 하이라이트의 첫 줄을 가져오다.
		line = this->notepadForm->highlight->GetAt(0);
	}
	Glyph *currentLine = this->notepadForm->note->GetAt(row);
	//3. 아래로 내려왔으면 0부터, 안올라왔으면 줄끝자리부터 시작열까지 반복하다.
	Long i = this->lineEndPosition;
	if (row > this->noteEndPosition) {
		i = 0;
	}
	while (i < startColumn) {
		//3.1. 줄의 처음을 지우다.
		line->Remove(0);
		i++;
	}
	//4. 시작열부터 끝열까지 반복하다.
	i = startColumn;
	while (i < endColumn) {
		//4.1. 현재 줄에서 현재 열의 글자를 가져오다.
		Glyph *character = currentLine->GetAt(i);
		//4.2. 가져온 줄에 글자의 클론을 추가하다.
		line->Add(character->Clone());
		i++;
	}
	//5. 문서끝자리를 구하다.
	this->noteEndPosition = row;
	//6. 줄끝자리를 구하다.
	this->lineEndPosition = endColumn;
}