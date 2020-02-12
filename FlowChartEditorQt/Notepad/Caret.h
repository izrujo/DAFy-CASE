//Caret.h

#ifndef _CARET_H
#define _CARET_H

typedef signed long int Long;

class NotepadForm;
class Caret {
public:
	Caret(NotepadForm *notepadForm = 0);
	Caret(const Caret& source);
	~Caret();
	void Create(Long width, Long height);
	void Move(Long x, Long y);
	void Show(bool isShow = true);
	Caret& operator=(const Caret& source);
	Long GetX() const;
	Long GetY() const;

private:
	NotepadForm *notepadForm;
	Long x;
	Long y;

};

#endif // !_CARET_H

inline Long Caret::GetX() const {
	return this->x;
}

inline Long Caret::GetY() const {
	return this->y;
}
