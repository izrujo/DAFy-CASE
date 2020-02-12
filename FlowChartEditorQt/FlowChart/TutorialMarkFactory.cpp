#include "TutorialMarkFactory.h"
#include "TutorialForm.h"
#include "FlowChart.h"
#include "Shape.h"
#include "TutorialMark.h"

TutorialMarkFactory::TutorialMarkFactory(FlowChart *sample) {
	this->sample = sample;
}

TutorialMarkFactory::TutorialMarkFactory(const TutorialMarkFactory& source) {
	this->sample = source.sample;
}

TutorialMarkFactory::~TutorialMarkFactory() {

}

TutorialMarkFactory& TutorialMarkFactory::operator=(const TutorialMarkFactory& source) {
	this->sample = source.sample;

	return *this;
}

TutorialMark* TutorialMarkFactory::Make(Long length) {
	TutorialMark *tutorialMark = 0;
	Shape *current;

	if (length <= 17 && length >= 10) {
		current = this->sample->GetAt((length - 17) * -2);
		tutorialMark = new TutorialMark(current->GetX(), current->GetY(), current->GetWidth(), current->GetHeight());
	}
	else if (length == 9) {
		FlowChart temp(15);
		Long i = 0;
		while (i <= 14) {
			temp.Attach(this->sample->GetAt(i)->Clone());
			i++;
		}
		CRect rect;
		temp.GetRange(rect);
		tutorialMark = new TutorialMark(rect.left, rect.top, rect.Width(), rect.Height());
	}
	else if (length == 8) {
		current = this->sample->GetAt(17);
		tutorialMark = new TutorialMark(current->GetX(), current->GetY(), current->GetWidth(), current->GetHeight());
	}
	else if (length == 7) {
		current = this->sample->GetAt(18);
		tutorialMark = new TutorialMark(current->GetX(), current->GetY(), current->GetWidth(), current->GetHeight());
	}
	else if (length == 6) {
		FlowChart temp(7);
		Long i = 14;
		while (i <= 20) {
			temp.Attach(this->sample->GetAt(i)->Clone());
			i++;
		}
		CRect rect;
		temp.GetRange(rect);
		tutorialMark = new TutorialMark(rect.left, rect.top, rect.Width(), rect.Height());
	}
	else if (length == 5) {
		current = this->sample->GetAt(21);
		tutorialMark = new TutorialMark(current->GetX(), current->GetY(), current->GetWidth(), current->GetHeight());
	}
	else if (length == 4) {
		current = this->sample->GetAt(23);
		tutorialMark = new TutorialMark(current->GetX(), current->GetY(), current->GetWidth(), current->GetHeight());
	}
	else if (length == 3) {
		FlowChart temp(3);
		Long i = 21;
		while (i <= 23) {
			temp.Attach(this->sample->GetAt(i)->Clone());
			i++;
		}
		CRect rect;
		temp.GetRange(rect);
		tutorialMark = new TutorialMark(rect.left, rect.top, rect.Width(), rect.Height());
	}
	else if (length == 2) {
		FlowChart temp(21);
		Long i = 6;
		while (i <= 25) {
			temp.Attach(this->sample->GetAt(i)->Clone());
			i++;
		}
		CRect rect;
		temp.GetRange(rect);
		tutorialMark = new TutorialMark(rect.left, rect.top, rect.Width(), rect.Height());
	}
	else if (length == 1) {
		current = this->sample->GetAt(26);
		tutorialMark = new TutorialMark(current->GetX(), current->GetY(), current->GetWidth(), current->GetHeight());
	}

	return tutorialMark;
}