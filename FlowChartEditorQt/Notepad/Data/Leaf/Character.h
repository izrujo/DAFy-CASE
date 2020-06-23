#ifndef _CHARACTER_H
#define _CHARACTER_H

#include "../Glyph.h"

class Character : public Glyph {
public:
	Character();
	Character(const Character& source);
	virtual ~Character() = 0;
};

class SingleByteCharacter : public Character {
public:
	SingleByteCharacter();
	SingleByteCharacter(char content);
	SingleByteCharacter(const SingleByteCharacter& source);
	virtual ~SingleByteCharacter();

	bool IsEqual(const SingleByteCharacter& other);
	bool IsNotEqual(const SingleByteCharacter& other);
	bool operator ==(const SingleByteCharacter& other);
	bool operator !=(const SingleByteCharacter& other);
	SingleByteCharacter& operator =(const SingleByteCharacter& source);

	virtual string GetContent();
	virtual Glyph* Clone();
private:
	char content;
};

class DoubleByteCharacter : public Character {
public:
	DoubleByteCharacter();
	DoubleByteCharacter(const char(*content));
	DoubleByteCharacter(const DoubleByteCharacter& source);
	virtual ~DoubleByteCharacter();

	bool IsEqual(const DoubleByteCharacter& other);
	bool IsNotEqual(const DoubleByteCharacter& other);
	bool operator ==(const DoubleByteCharacter& other);
	bool operator !=(const DoubleByteCharacter& other);
	DoubleByteCharacter& operator =(const DoubleByteCharacter& source);

	virtual string GetContent();
	virtual Glyph* Clone();
private:
	char content[2];
};

#endif //_CHARACTER_H