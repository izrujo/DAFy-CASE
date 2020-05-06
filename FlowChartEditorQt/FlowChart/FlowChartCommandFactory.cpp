#include "FlowChartCommandFactory.h"
#include "FlowChartCommands.h"

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

FlowChartCommand* FlowChartCommandFactory::Make(string text) {
	FlowChartCommand *command = 0;

	if (text == "Save") {
		command = new SaveCommand(this->editor);
	}
	else if (text == "SaveAs") {
		command = new SaveAsCommand(this->editor);
	}
	else if (text == "Open") {
		command = new OpenCommand(this->editor);
	}
	else if (text == "New") {
		command = new NewCommand(this->editor);
	}
	else if (text == "Undo") {
		command = new UndoCommand(this->editor);
	}
	else if (text == "Redo") {
		command = new RedoCommand(this->editor);
	}
	else if (text == "FontSet") {
		command = new FontSetCommand(this->editor);
	}
	else if (text == "Print") {
		command = new PreviewCommand(this->editor);
	}
	else if (text == "SaveAsImage") {
		command = new SaveAsImageCommand(this->editor);
	}
	else if (text == "DrawingMode") {
		command = new DrawingModeCommand(this->editor);
	}
	else if (text == "DrawingUnMode") {
		command = new DrawingUnModeCommand(this->editor);
	}
	else if (text == "Copy") {
		command = new CopyCommand(this->editor);
	}
	else if (text == "Paste") {
		command = new PasteCommand(this->editor);
	}
	else if (text == "Cut") {
		command = new CutCommand(this->editor);
	}
	else if (text == "Delete") {
		command = new DeleteCommand(this->editor);
	}
	else if (text == "SelectAll") {
		command = new SelectAllCommand(this->editor);
	}
	else if (text == "StartSymbol") {
		command = new StartCommand(this->editor);
	}
	else if (text == "PreparationSymbol") {
		command = new PreparationCommand(this->editor);
	}
	else if (text == "InputSymbol") {
		command = new InputCommand(this->editor);
	}
	else if (text == "ProcessSymbol") {
		command = new ProcessCommand(this->editor);
	}
	else if (text == "DecisionSymbol") {
		command = new DecisionCommand(this->editor);
	}
	else if (text == "OutputSymbol") {
		command = new OutputCommand(this->editor);
	}
	else if (text == "StopTerminalSymbol") {
		command = new StopCommand(this->editor);
	}
	else if (text == "PageSet") {
		command = new PageSetCommand(this->editor);
	}
	else if (text == "Position") {
		command = new PositionCommand(this->editor);
	}
	else if (text == "Size") {
		command = new SizeCommand(this->editor);
	}
	else if (text == "Interval") {
		command = new IntervalCommand(this->editor);
	}
	else if (text == "SequenceArchitecture") {
		command = new SequenceCommand(this->editor);
	}
	else if (text == "IterationArchitecture") {
		command = new IterationCommand(this->editor);
	}
	else if (text == "SelectionArchitecture") {
		command = new SelectionCommand(this->editor);
	}
	else if (text == "Close") {
		command = new CloseCommand(this->editor);
	}
	else if (text == "RuleKeep") {
		command = new RuleKeepCommand(this->editor);
	}

	return command;
}