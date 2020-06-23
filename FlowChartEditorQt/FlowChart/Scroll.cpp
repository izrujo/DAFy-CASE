#include "Scroll.h"

#include <qscrollbar.h>
#include <qframe.h>

Scroll::Scroll(Qt::Orientation orientation, QWidget *parent)
	: QScrollBar(orientation, parent)
{
	QObject::connect(this, &QScrollBar::valueChanged, this, &Scroll::Move);
	this->isFromConstructor = false;
}

Scroll::Scroll(const Scroll& source)
	: QScrollBar(source.orientation(), parentWidget())
{
	QObject::connect(this, &QScrollBar::valueChanged, this, &Scroll::Move);
	this->isFromConstructor = source.isFromConstructor;
}

Scroll::~Scroll()
{
	//QObject::disconnect(this, &QScrollBar::valueChanged, this, &Scroll::Move);
}

void Scroll::Move(Long value) {
	Long minimum = this->minimum();
	Long maximum = this->maximum();
	if (value < minimum) {
		value = minimum;
	}
	else if (value > maximum) {
		value = maximum;
	}
	this->setValue(value);

	//ScrollController 생성자에서 불러짐 - value가 음수, 그리면 오류
	if (this->isFromConstructor == false) {
		static_cast<QFrame*>(this->parent())->repaint();
	}

	emit valueChanged(value);
}

bool Scroll::SetFromConstructorFlag(bool flag) {
	this->isFromConstructor = flag;

	return this->isFromConstructor;
}