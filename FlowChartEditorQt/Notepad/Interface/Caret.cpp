//Caret.cpp
#include "Caret.h"

#include <qwidget.h>
#include <qpainter.h>

Caret::Caret(QWidget *parent)
	: parent(parent) {
	timer.setParent(this);
	connect(&timer, SIGNAL(timeout()), this, SLOT(onTimer()));
	timer.start(500);
}

Caret::Caret(const Caret& source) 
	: parent(source.parent) {
	timer.setParent(this);
	connect(&timer, SIGNAL(timeout()), this, SLOT(onTimer()));
	timer.start(500);
}

Caret::~Caret() {

}

Caret& Caret::operator=(const Caret& source) {
	this->parent = source.parent;
	this->timer.setParent(this);
	connect(&this->timer, SIGNAL(timeout()), this, SLOT(onTimer()));
	this->timer.start(500);

	return *this;
}

void Caret::Show() {
	this->isVisible = true;
	this->parent->update(this->rect);
}

void Caret::Hide() {
	this->isVisible = false;
	this->parent->update(this->rect);
}

void Caret::Set(QRect rect) {
	this->rect = rect;
	//rect.setWidth(1);
	this->parent->update(this->rect);
}

void Caret::Paint(QPainter& painter) {
	if (this->isVisible && this->isBlink) {
		painter.save();
		painter.setPen(Qt::NoPen);
		painter.setBrush(Qt::black);
		painter.drawRect(this->rect);
		painter.restore();
	}
}

void Caret::onTimer() {
	this->isBlink = !this->isBlink;
	//(this->isBlink == true) ? (this->isBlink = false) : (this->isBlink = true);
	this->parent->update(this->rect);
}