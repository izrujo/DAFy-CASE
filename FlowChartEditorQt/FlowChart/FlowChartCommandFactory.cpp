#include "FlowChartCommandFactory.h"
#include "FlowChartCommands.h"
#include "resource.h"

FlowChartCommandFactory::FlowChartCommandFactory(FlowChartEditor *editor) {
	this->editor = editor;
}

FlowChartCommandFactory::FlowChartCommandFactory(const FlowChartCommandFactory& source) {
	this->editor = source.editor;
}

FlowChartCommandFactory::~FlowChartCommandFactory() {

}

FlowChartCommandFactory& FlowChartCommandFactory::operator=(const FlowChartCommandFactory& source) {
	this->editor = source.editor;

	return *this;
}

FlowChartCommand* FlowChartCommandFactory::Make(int uID) {
	FlowChartCommand *command = 0;

	switch (uID) {
	case IDM_FILE_SAVE:
		command = new SaveCommand(this->editor);
		break;
	case IDM_FILE_SAVEAS:
		command = new SaveAsCommand(this->editor);
		break;
	case IDM_FILE_OPEN:
		command = new OpenCommand(this->editor);
		break;
	case IDM_FILE_NEW:
		command = new NewCommand(this->editor);
		break;
	case IDM_EDIT_UNDO:
		command = new UndoCommand(this->editor);
		break;
	case IDM_EDIT_REDO:
		command = new RedoCommand(this->editor);
		break;
	case IDM_FORMAT_FONT:
		command = new FontSetCommand(this->editor);
		break;
	case IDM_FILE_PRINT:
		command = new PreviewCommand(this->editor);
		break;
	case IDM_FILE_SAVEASIMAGE:
		command = new SaveAsImageCommand(this->editor);
		break;
	case IDM_ADD_MODE:
		command = new DrawingModeCommand(this->editor);
		break;
	case IDM_ADD_UNMODE:
		command = new DrawingUnModeCommand(this->editor);
		break;
	case IDM_EDIT_COPY:
		command = new CopyCommand(this->editor);
		break;
	case IDM_EDIT_PASTE:
		command = new PasteCommand(this->editor);
		break;
	case IDM_EDIT_CUT:
		command = new CutCommand(this->editor);
		break;
	case IDM_EDIT_DELETE:
		command = new DeleteCommand(this->editor);
		break;
	case IDM_EDIT_SELECTALL:
		command = new SelectAllCommand(this->editor);
		break;
	case IDM_ADD_START:
		command = new StartCommand(this->editor);
		break;
	case IDM_ADD_PREPARATION:
		command = new PreparationCommand(this->editor);
		break;
	case IDM_ADD_INPUT:
		command = new InputCommand(this->editor);
		break;
	case IDM_ADD_PROCESS:
		command = new ProcessCommand(this->editor);
		break;
	case IDM_ADD_DECISION:
		command = new DecisionCommand(this->editor);
		break;
	case IDM_ADD_OUTPUT:
		command = new OutputCommand(this->editor);
		break;
	case IDM_ADD_STOP:
		command = new StopCommand(this->editor);
		break;
	case IDM_FORMAT_PAGESET:
		command = new PageSetCommand(this->editor);
		break;
	case IDM_EDIT_POSITION:
		command = new PositionCommand(this->editor);
		break;
	case IDM_EDIT_SIZE:
		command = new SizeCommand(this->editor);
		break;
	case IDM_EDIT_INTERVAL:
		command = new IntervalCommand(this->editor);
		break;
	case IDM_CONTROL_SEQUENCE:
		command = new SequenceCommand(this->editor);
		break;
	case IDM_CONTROL_ITERATION:
		command = new IterationCommand(this->editor);
		break;
	case IDM_CONTROL_SELECTION:
		command = new SelectionCommand(this->editor);
		break;
	case IDM_HELP_TUTORIAL:
		command = new TutorialCommand(this->editor);
		break;
	default:
		break;
	}

	return command;
}