#ifndef _TUTORIALCONTROLLER_H
#define _TUTORIALCONTROLLER_H

class TutorialForm;

class TutorialController {
public:
	TutorialController(TutorialForm *tutorialForm = 0);
	TutorialController(const TutorialController& source);
	~TutorialController();
	TutorialController& operator=(const TutorialController& source);

	void Update();
private:
	TutorialForm *tutorialForm;
};


#endif //_TUTORIALCONTROLLER_H