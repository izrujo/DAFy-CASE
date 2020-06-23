#ifndef _SCANNER_H
#define _SCANNER_H

#include <string>

using namespace std;
typedef signed long int Long;

class Scanner {
public:
	Scanner(string pattern);
	Scanner(const Scanner& source);
	~Scanner();
	string GetToken();
	Long Next();
	bool IsEnd();
	Scanner& operator=(const Scanner& source);
	string GetPattern() const;
	Long GetCurrent() const;
	Long GetLength() const;
private:
	string pattern;
	Long current;
	Long length;
};

inline string Scanner::GetPattern() const {
	return this->pattern;
}

inline Long Scanner::GetCurrent() const {
	return this->current;
}

inline Long Scanner::GetLength() const {
	return this->length;
}

#endif // !_SCANNER_H
