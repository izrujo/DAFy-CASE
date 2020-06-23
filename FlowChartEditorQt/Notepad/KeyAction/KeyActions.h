#ifndef _KEYACTIONS_H
#define _KEYACTIONS_H

class Notepad;

class KeyAction {
public:
	KeyAction(Notepad *notepad = 0);
	KeyAction(const KeyAction& source);
	virtual ~KeyAction() = 0;
	virtual void OnKeyDown() = 0;
	KeyAction& operator=(const KeyAction& source);
protected:
	Notepad *notepad;
};

class LeftKeyAction : public KeyAction {
public:
	LeftKeyAction(Notepad *notepad = 0);
	LeftKeyAction(const LeftKeyAction& source);
	virtual ~LeftKeyAction();
	virtual void OnKeyDown();
	LeftKeyAction& operator =(const LeftKeyAction& source);
};

class RightKeyAction : public KeyAction {
public:
	RightKeyAction(Notepad *notepad = 0);
	RightKeyAction(const RightKeyAction& source);
	virtual ~RightKeyAction();
	virtual void OnKeyDown();
	RightKeyAction& operator =(const RightKeyAction& source);
};

class UpKeyAction : public KeyAction {
public:
	UpKeyAction(Notepad *notepad = 0);
	UpKeyAction(const UpKeyAction& source);
	virtual ~UpKeyAction();
	virtual void OnKeyDown();
	UpKeyAction& operator = (const UpKeyAction& source);
};

class DownKeyAction : public KeyAction {
public:
	DownKeyAction(Notepad *notepad = 0);
	DownKeyAction(const DownKeyAction& source);
	virtual ~DownKeyAction();
	virtual void OnKeyDown();
	DownKeyAction& operator=(const DownKeyAction& source);
};

class HomeKeyAction : public KeyAction {
public:
	HomeKeyAction(Notepad *notepad = 0);
	HomeKeyAction(const HomeKeyAction& source);
	virtual ~HomeKeyAction();
	virtual void OnKeyDown();
	HomeKeyAction& operator =(const HomeKeyAction& source);
};

class EndKeyAction : public KeyAction {
public:
	EndKeyAction(Notepad *notepad = 0);
	EndKeyAction(const EndKeyAction& source);
	virtual ~EndKeyAction();
	virtual void OnKeyDown();
	EndKeyAction& operator =(const EndKeyAction& source);
};

class CtrlLeftKeyAction : public KeyAction {
public:
	CtrlLeftKeyAction(Notepad *notepad = 0);
	CtrlLeftKeyAction(const CtrlLeftKeyAction& source);
	virtual ~CtrlLeftKeyAction();
	virtual void OnKeyDown();
	CtrlLeftKeyAction& operator =(const CtrlLeftKeyAction& source);
};

class CtrlRightKeyAction : public KeyAction {
public:
	CtrlRightKeyAction(Notepad *notepad = 0);
	CtrlRightKeyAction(const CtrlRightKeyAction& source);
	virtual ~CtrlRightKeyAction();
	virtual void OnKeyDown();
	CtrlRightKeyAction& operator =(const CtrlRightKeyAction& source);
};

class CtrlHomeKeyAction : public KeyAction {
public:
	CtrlHomeKeyAction(Notepad *notepad = 0);
	CtrlHomeKeyAction(const CtrlHomeKeyAction& source);
	virtual ~CtrlHomeKeyAction();
	virtual void OnKeyDown();
	CtrlHomeKeyAction& operator =(const CtrlHomeKeyAction& source);
};

class CtrlEndKeyAction : public KeyAction {
public:
	CtrlEndKeyAction(Notepad *notepad = 0);
	CtrlEndKeyAction(const CtrlEndKeyAction& source);
	virtual ~CtrlEndKeyAction();
	virtual void OnKeyDown();
	CtrlEndKeyAction& operator =(const CtrlEndKeyAction& source);
};

class DeleteKeyAction : public KeyAction {
public:
	DeleteKeyAction(Notepad *notepad = 0);
	DeleteKeyAction(const DeleteKeyAction& source);
	virtual ~DeleteKeyAction();
	virtual void OnKeyDown();
	DeleteKeyAction& operator =(const DeleteKeyAction& source);
};

class BackSpaceKeyAction : public KeyAction {
public:
	BackSpaceKeyAction(Notepad *notepad = 0);
	BackSpaceKeyAction(const BackSpaceKeyAction& source);
	virtual ~BackSpaceKeyAction();
	virtual void OnKeyDown();
	BackSpaceKeyAction& operator =(const BackSpaceKeyAction& source);
};

class ShiftLeftKeyAction : public KeyAction {
public:
	ShiftLeftKeyAction(Notepad *notepad = 0);
	ShiftLeftKeyAction(const ShiftLeftKeyAction& source);
	virtual ~ShiftLeftKeyAction();
	virtual void OnKeyDown();
	ShiftLeftKeyAction& operator =(const ShiftLeftKeyAction& source);
};

class ShiftRightKeyAction : public KeyAction {
public:
	ShiftRightKeyAction(Notepad *notepad = 0);
	ShiftRightKeyAction(const ShiftRightKeyAction& source);
	virtual ~ShiftRightKeyAction();
	virtual void OnKeyDown();
	ShiftRightKeyAction& operator =(const ShiftRightKeyAction& source);
};

class ShiftUpKeyAction : public KeyAction {
public:
	ShiftUpKeyAction(Notepad *notepad = 0);
	ShiftUpKeyAction(const ShiftUpKeyAction& source);
	virtual ~ShiftUpKeyAction();
	virtual void OnKeyDown();
	ShiftUpKeyAction& operator =(const ShiftUpKeyAction& source);
};

class ShiftDownKeyAction : public KeyAction {
public:
	ShiftDownKeyAction(Notepad *notepad = 0);
	ShiftDownKeyAction(const ShiftDownKeyAction& source);
	virtual ~ShiftDownKeyAction();
	virtual void OnKeyDown();
	ShiftDownKeyAction& operator =(const ShiftDownKeyAction& source);
};

class ShiftHomeKeyAction : public KeyAction {
public:
	ShiftHomeKeyAction(Notepad *notepad = 0);
	ShiftHomeKeyAction(const ShiftHomeKeyAction& source);
	virtual ~ShiftHomeKeyAction();
	virtual void OnKeyDown();
	ShiftHomeKeyAction& operator =(const ShiftHomeKeyAction& source);
};

class ShiftEndKeyAction : public KeyAction {
public:
	ShiftEndKeyAction(Notepad *notepad = 0);
	ShiftEndKeyAction(const ShiftEndKeyAction& source);
	virtual ~ShiftEndKeyAction();
	virtual void OnKeyDown();
	ShiftEndKeyAction& operator =(const ShiftEndKeyAction& source);
};

class ShiftCtrlLeftKeyAction : public KeyAction {
public:
	ShiftCtrlLeftKeyAction(Notepad *notepad = 0);
	ShiftCtrlLeftKeyAction(const ShiftCtrlLeftKeyAction& source);
	virtual ~ShiftCtrlLeftKeyAction();
	virtual void OnKeyDown();
	ShiftCtrlLeftKeyAction& operator =(const ShiftCtrlLeftKeyAction& source);
};

class ShiftCtrlRightKeyAction : public KeyAction {
public:
	ShiftCtrlRightKeyAction(Notepad *notepad = 0);
	ShiftCtrlRightKeyAction(const ShiftCtrlRightKeyAction& source);
	virtual ~ShiftCtrlRightKeyAction();
	virtual void OnKeyDown();
	ShiftCtrlRightKeyAction& operator =(const ShiftCtrlRightKeyAction& source);
};

class ShiftCtrlHomeKeyAction : public KeyAction {
public:
	ShiftCtrlHomeKeyAction(Notepad *notepad = 0);
	ShiftCtrlHomeKeyAction(const ShiftCtrlHomeKeyAction& source);
	virtual ~ShiftCtrlHomeKeyAction();
	virtual void OnKeyDown();
	ShiftCtrlHomeKeyAction& operator =(const ShiftCtrlHomeKeyAction& source);
};

class ShiftCtrlEndKeyAction : public KeyAction {
public:
	ShiftCtrlEndKeyAction(Notepad *notepad = 0);
	ShiftCtrlEndKeyAction(const ShiftCtrlEndKeyAction& source);
	virtual ~ShiftCtrlEndKeyAction();
	virtual void OnKeyDown();
	ShiftCtrlEndKeyAction& operator =(const ShiftCtrlEndKeyAction& source);
};

class CtrlAKeyAction : public KeyAction {
public:
	CtrlAKeyAction(Notepad *notepad = 0);
	CtrlAKeyAction(const CtrlAKeyAction& source);
	virtual ~CtrlAKeyAction();
	virtual void OnKeyDown();
	CtrlAKeyAction& operator =(const CtrlAKeyAction& source);
};

class CtrlCKeyAction : public KeyAction {
public:
	CtrlCKeyAction(Notepad *notepad = 0);
	CtrlCKeyAction(const CtrlCKeyAction& source);
	virtual ~CtrlCKeyAction();
	virtual void OnKeyDown();
	CtrlCKeyAction& operator =(const CtrlCKeyAction& source);
};

class CtrlVKeyAction : public KeyAction {
public:
	CtrlVKeyAction(Notepad *notepad = 0);
	CtrlVKeyAction(const CtrlVKeyAction& source);
	virtual ~CtrlVKeyAction();
	virtual void OnKeyDown();
	CtrlVKeyAction& operator =(const CtrlVKeyAction& source);
};

class CtrlXKeyAction : public KeyAction {
public:
	CtrlXKeyAction(Notepad *notepad = 0);
	CtrlXKeyAction(const CtrlXKeyAction& source);
	virtual ~CtrlXKeyAction();
	virtual void OnKeyDown();
	CtrlXKeyAction& operator =(const CtrlXKeyAction& source);
};

#endif //_KEYACTIONS_H