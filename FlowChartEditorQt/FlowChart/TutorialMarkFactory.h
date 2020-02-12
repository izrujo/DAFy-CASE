#ifndef _TUTORIALMARKFACTORY_H
#define _TUTORIALMARKFACTORY_H

typedef signed long int Long;
class TutorialMark;
class FlowChart;

class TutorialMarkFactory {
public:
	TutorialMarkFactory(FlowChart *sample=0);
	TutorialMarkFactory(const TutorialMarkFactory& source);
	~TutorialMarkFactory();
	TutorialMarkFactory& operator=(const TutorialMarkFactory& source);

	TutorialMark* Make(Long length); //튜토리얼 시나리오의 남은 개수(현재 어떤 시나리오인지)에 따라 표시를 달리 함.
private:
	FlowChart *sample;
};

#endif //_TUTORIALMARKFACTORY_H