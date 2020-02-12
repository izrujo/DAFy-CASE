#ifndef _RESOLUTIONCONVERTER_H
#define _RESOLUTIONCONVERTER_H

typedef signed long int Long;

class ResolutionConverter {
public:
	ResolutionConverter(Long dpi = 600, Long paperWidth = 210, Long paperHeight = 297);
	ResolutionConverter(const ResolutionConverter& source);
	~ResolutionConverter();
	ResolutionConverter& operator=(const ResolutionConverter& source);

	Long ConvertHorizontal(Long value, Long pixelWidth);
	Long ConvertVertical(Long value, Long pixelHeight);
private:
	Long dpi;
	Long paperWidth;
	Long paperHeight;
};

#endif //_RESOLUTIONCONVERTER_H