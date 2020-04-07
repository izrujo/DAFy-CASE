#ifndef _TUTORIALMARKFACTORY_H
#define _TUTORIALMARKFACTORY_H

typedef signed long int Long;
class TutorialMark;
#include "Shape.h"

using namespace FlowChartShape;

class TutorialMarkFactory {
public:
	TutorialMarkFactory(Shape *sample = 0);
	TutorialMarkFactory(const TutorialMarkFactory& source);
	~TutorialMarkFactory();
	TutorialMarkFactory& operator=(const TutorialMarkFactory& source);

	TutorialMark* Make(Long length); //튜토리얼 시나리오의 남은 개수(현재 어떤 시나리오인지)에 따라 표시를 달리 함.
private:
	Shape *sample;
};

#endif //_TUTORIALMARKFACTORY_H