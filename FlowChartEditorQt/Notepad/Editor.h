#ifndef _EDITOR_H
#define _EDITOR_H

typedef signed long int Long;
class NotepadForm;
class Selector;

class Editor {
public:
	Editor(NotepadForm *notepadForm = 0);
	Editor(const Editor& source);
	~Editor();

	void UpSelect(Long noteCurrent, Long lineCurrent, Long row, Long column);
	void DownSelect(Long noteCurrent, Long lineCurrent, Long row, Long column);
	void Copy();
	void Paste();
	void Delete();

	Editor& operator=(const Editor& source);
private:
	NotepadForm *notepadForm;
public:
	Selector *selector;
};

#endif //_EDITOR_H