#ifndef _ZOOM_H
#define _ZOOM_H

typedef signed long int Long;
//class Memory;

class Zoom {
public:
	Zoom(Long rate = 100);
	Zoom(const Zoom& source);
	~Zoom();
	Zoom& operator=(const Zoom& source);

	void Set(Long changeRate);
	//void SetAt(Long position);
	//void SetBack();
	//void SetMemory(float changeRate, Memory *memory);

	Long GetRate() const;
private:
	Long rate;
};

inline Long Zoom::GetRate() const {
	return this->rate;
}

#endif //_ZOOM_H