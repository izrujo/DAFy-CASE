#include "ResolutionConverter.h"
#include <cmath>

ResolutionConverter::ResolutionConverter(Long dpi, Long paperWidth, Long paperHeight) {
	this->dpi = dpi;
	this->paperWidth = paperWidth;
	this->paperHeight = paperHeight;
}

ResolutionConverter::ResolutionConverter(const ResolutionConverter& source) {
	this->dpi = source.dpi;
	this->paperWidth = source.paperWidth;
	this->paperHeight = source.paperHeight;
}

ResolutionConverter::~ResolutionConverter() {

}

ResolutionConverter& ResolutionConverter::operator=(const ResolutionConverter& source) {
	this->dpi = source.dpi;
	this->paperWidth = source.paperWidth;
	this->paperHeight = source.paperHeight;

	return *this;
}

Long ResolutionConverter::ConvertHorizontal(Long value, Long pixelWidth) {
	Long quotient = this->paperWidth * value / pixelWidth;
	Long remainder = this->paperWidth * value % pixelWidth;
	if (remainder >= pixelWidth / 2) quotient++;
	value = quotient;

	float inch = value / 25.4;
	value = static_cast<Long>(round(inch * this->dpi));

	return value;
}

Long ResolutionConverter::ConvertVertical(Long value, Long pixelHeight) {
	Long quotient = this->paperHeight * value / pixelHeight;
	Long remainder = this->paperHeight * value % pixelHeight;
	if (remainder >= pixelHeight / 2) quotient++;
	value = quotient;

	float inch = value / 25.4;
	value = static_cast<Long>(round(inch * this->dpi));

	return value;
}