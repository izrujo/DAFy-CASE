#include "Highlight.h"

Highlight::Highlight(Long capacity)
	: Composite(capacity) {
}

Highlight::Highlight(const Highlight& source)
	: Composite(source) {
}

Highlight::~Highlight() {

}

Highlight& Highlight::operator =(const Highlight& source) {
	Composite::operator=(source);

	return *this;
}

string Highlight::GetContent() {
	string content = "";
	Long i = 0;
	while (i < this->length) {
		content += this->glyphs[i]->GetContent();
		i++;
	}
	return content;
}

Glyph* Highlight::Clone() {
	return new Highlight(*this);
}