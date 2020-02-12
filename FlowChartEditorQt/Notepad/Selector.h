#ifndef _SELECTOR_H
#define _SELECTOR_H

typedef signed long int Long;

class NotepadForm;

class Selector {
public:
	Selector(NotepadForm *notepadForm = 0, Long noteStartPosition = 0, Long lineStartPosition = 0, Long noteEndPosition = 0, Long lineEndPosition = 0);
	Selector(const Selector& source);
	~Selector();
	Selector& operator=(const Selector& source);

	void Left(Long row, Long startColumn, Long endColumn);
	void Right(Long row, Long startColumn, Long endColumn);

	Long GetNoteStartPosition() const;
	Long GetLineStartPosition() const;
	Long GetNoteEndPosition() const;
	Long GetLineEndPosition() const;
private:
	NotepadForm *notepadForm;
	Long noteStartPosition;
	Long lineStartPosition;
	Long noteEndPosition;
	Long lineEndPosition;
};

inline Long Selector::GetNoteStartPosition() const {
	return this->noteStartPosition;
}
inline Long Selector::GetLineStartPosition() const {
	return this->lineStartPosition;
}
inline Long Selector::GetNoteEndPosition() const {
	return this->noteEndPosition;
}
inline Long Selector::GetLineEndPosition() const {
	return this->lineEndPosition;
}

#endif //_SELECTOR_H