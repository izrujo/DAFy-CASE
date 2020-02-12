#include "TutorialController.h"
#include "TutorialForm.h"
#include "FlowChartEditor.h"
#include "Tutorials.h"
#include "TutorialMarkFactory.h"
#include "Expressions.h"
#include "ExpressionFactory.h"

TutorialController::TutorialController(TutorialForm *tutorialForm) {
	this->tutorialForm = tutorialForm;
}

TutorialController::TutorialController(const TutorialController& source) {
	this->tutorialForm = source.tutorialForm;
}

TutorialController::~TutorialController() {

}

TutorialController& TutorialController::operator=(const TutorialController& source) {
	this->tutorialForm = source.tutorialForm;

	return *this;
}

void TutorialController::Update() {
	FlowChartEditor *editor = static_cast<FlowChartEditor*>(this->tutorialForm->GetParent());
	ExpressionFactory expFactory(editor);
	ScenarioCheckExpression *expression = expFactory.Make(this->tutorialForm->lastConcrete);
	bool ret = expression->Evaluate();
	if (ret == true && this->tutorialForm->main->GetLength() > 0) {
		this->tutorialForm->main->Execute();
		if (this->tutorialForm->lastConcrete != NULL) { //lastConcrete를 갱신하기 전에 없애줘야 메모리 누수 없음.
			delete this->tutorialForm->lastConcrete;
		}

		this->tutorialForm->lastConcrete = this->tutorialForm->main->Top()->TakeOut();

		if (dynamic_cast<SymbolSelectTutorial*>(this->tutorialForm->lastConcrete) ||
			dynamic_cast<GroupTutorial*>(this->tutorialForm->lastConcrete)) {
			if (this->tutorialForm->current != NULL) { //얘넨 현재 시나리오를 시작할 때 하는건데.
				delete this->tutorialForm->current;
			}
			TutorialMarkFactory factory(this->tutorialForm->sample);
			this->tutorialForm->current = factory.Make(this->tutorialForm->main->GetLength());
			this->tutorialForm->Invalidate();
			this->tutorialForm->SetFocus();
		}

		if (this->tutorialForm->main->Top()->GetLength() < 1) {
			Tutorial *current = this->tutorialForm->main->TakeOut();
			if (current != NULL) {
				delete current;
			}
		}

		if (this->tutorialForm->main->GetLength() < 1) {
			this->tutorialForm->OnClose();
		}
	}
}