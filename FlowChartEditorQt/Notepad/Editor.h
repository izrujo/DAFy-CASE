#ifndef _EDITOR_H
#define _EDITOR_H

typedef signed long int Long;
class Notepad;
class Selector;

class Editor {
public:
	Editor(Notepad *notepad = 0);
	Editor(const Editor& source);
	~Editor();

	void UpSelect(Long noteCurrent, Long lineCurrent, Long row, Long column);
	void DownSelect(Long noteCurrent, Long lineCurrent, Long row, Long column);
	void Copy();
	void Paste();
	void Delete();

	Editor& operator=(const Editor& source);
private:
	Notepad *notepad;
public:
	Selector *selector;
};

#endif //_EDITOR_H