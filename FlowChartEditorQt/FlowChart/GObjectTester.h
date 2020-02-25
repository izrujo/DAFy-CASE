#pragma once

#include <QtWidgets/QFrame>
#include "ui_GObjectTester.h"

class GObject;

class GObjectTester : public QFrame
{
	Q_OBJECT

public:
	GObjectTester(QFrame *parent = Q_NULLPTR);

private:
	Ui::GObjectTesterClass ui;

protected:
	void paintEvent(QPaintEvent *event);
	void closeEvent(QCloseEvent *event);
	void resizeEvent(QResizeEvent *event);
public:
	GObject *painter;
};
