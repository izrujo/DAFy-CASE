#ifndef CHARACTERMETRICS_H
#define CHARACTERMETRICS_H

#include <string>

using namespace std;
typedef signed long int Long;
class Notepad;
class Glyph;

class CharacterMetrics {
public:
	CharacterMetrics(Notepad *notepad = 0);
	CharacterMetrics(const CharacterMetrics& source);
	~CharacterMetrics();
	Long GetX(Glyph *line);
	Long GetX(Glyph *line, Long index);
	Long GetX(const string& buffer);
	Long GetY(Long index);
	Long GetColumn(Glyph *line, Long x);
	Long GetRow(Long y);

	CharacterMetrics& operator=(const CharacterMetrics& source);

	Long GetWidth(Long index) const;
	Long GetDoubleByteWidth() const;
	Long GetHeight() const;
	Long GetDescent() const;
private:
	Notepad *notepad;
	Long widths[129];
	Long height;
	Long descent;
};

inline Long CharacterMetrics::GetWidth(Long index) const {
	return this->widths[index];
}

inline Long CharacterMetrics::GetDoubleByteWidth() const {
	return this->widths[128];
}

inline Long CharacterMetrics::GetHeight() const {
	return this->height;
}

inline Long CharacterMetrics::GetDescent() const {
	return this->descent;
}

#endif // !CHARACTERMETRICS_H
