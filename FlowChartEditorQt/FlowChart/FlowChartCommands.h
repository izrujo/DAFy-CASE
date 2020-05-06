#ifndef _FLOWCHARTCOMMANDS_H
#define _FLOWCHARTCOMMANDS_H

class FlowChartEditor;

class FlowChartCommand {
public:
	FlowChartCommand(FlowChartEditor *editor = 0);
	FlowChartCommand(const FlowChartCommand& source);
	virtual ~FlowChartCommand() = 0;
	FlowChartCommand& operator=(const FlowChartCommand& source);

	virtual void Execute() = 0;
protected:
	FlowChartEditor *editor;
};

//SaveCommand
class SaveCommand : public FlowChartCommand {
public:
	SaveCommand(FlowChartEditor *editor = 0);
	SaveCommand(const SaveCommand& source);
	virtual ~SaveCommand();
	SaveCommand& operator=(const SaveCommand& source);

	virtual void Execute();
};

//SaveAsCommand
class SaveAsCommand : public FlowChartCommand {
public:
	SaveAsCommand(FlowChartEditor *editor = 0);
	SaveAsCommand(const SaveAsCommand& source);
	virtual ~SaveAsCommand();
	SaveAsCommand& operator=(const SaveAsCommand& source);

	virtual void Execute();
};

//OpenCommand
class OpenCommand : public FlowChartCommand {
public:
	OpenCommand(FlowChartEditor *editor = 0);
	OpenCommand(const OpenCommand& source);
	virtual ~OpenCommand();
	OpenCommand& operator=(const OpenCommand& source);

	virtual void Execute();
};

//NewCommand
class NewCommand : public FlowChartCommand {
public:
	NewCommand(FlowChartEditor *editor = 0);
	NewCommand(const NewCommand& source);
	virtual ~NewCommand();
	NewCommand& operator=(const NewCommand& source);

	virtual void Execute();
};

//UndoCommand
class UndoCommand : public FlowChartCommand {
public:
	UndoCommand(FlowChartEditor *editor = 0);
	UndoCommand(const UndoCommand& source);
	virtual ~UndoCommand();
	UndoCommand& operator=(const UndoCommand& source);

	virtual void Execute();
};

//RedoCommand
class RedoCommand : public FlowChartCommand {
public:
	RedoCommand(FlowChartEditor *editor = 0);
	RedoCommand(const RedoCommand& source);
	virtual ~RedoCommand();
	RedoCommand& operator=(const RedoCommand& source);

	virtual void Execute();
};

//FontSetCommand
class FontSetCommand : public FlowChartCommand {
public:
	FontSetCommand(FlowChartEditor *editor = 0);
	FontSetCommand(const FontSetCommand& source);
	virtual ~FontSetCommand();
	FontSetCommand& operator=(const FontSetCommand& source);

	virtual void Execute();
};

//PreviewCommand
class PreviewCommand : public FlowChartCommand {
public:
	PreviewCommand(FlowChartEditor *editor = 0);
	PreviewCommand(const PreviewCommand& source);
	virtual ~PreviewCommand();
	PreviewCommand& operator=(const PreviewCommand& source);

	virtual void Execute();
};

//SaveAsImageCommand
class SaveAsImageCommand : public FlowChartCommand {
public:
	SaveAsImageCommand(FlowChartEditor *editor = 0);
	SaveAsImageCommand(const SaveAsImageCommand& source);
	virtual ~SaveAsImageCommand();
	SaveAsImageCommand& operator=(const SaveAsImageCommand& source);

	virtual void Execute();
};

//DrawingModeCommand
class DrawingModeCommand : public FlowChartCommand {
public:
	DrawingModeCommand(FlowChartEditor *editor = 0);
	DrawingModeCommand(const DrawingModeCommand& source);
	virtual ~DrawingModeCommand();
	DrawingModeCommand& operator=(const DrawingModeCommand& source);

	virtual void Execute();
};

//DrawingUnModeCommand
class DrawingUnModeCommand : public FlowChartCommand {
public:
	DrawingUnModeCommand(FlowChartEditor *editor = 0);
	DrawingUnModeCommand(const DrawingUnModeCommand& source);
	virtual ~DrawingUnModeCommand();
	DrawingUnModeCommand& operator=(const DrawingUnModeCommand& source);

	virtual void Execute();
};

//CopyCommand
class CopyCommand : public FlowChartCommand {
public:
	CopyCommand(FlowChartEditor *editor = 0);
	CopyCommand(const CopyCommand& source);
	virtual ~CopyCommand();
	CopyCommand& operator=(const CopyCommand& source);

	virtual void Execute();
};

//PasteCommand
class PasteCommand : public FlowChartCommand {
public:
	PasteCommand(FlowChartEditor *editor = 0);
	PasteCommand(const PasteCommand& source);
	virtual ~PasteCommand();
	PasteCommand& operator=(const PasteCommand& source);

	virtual void Execute();
};

//CutCommand
class CutCommand : public FlowChartCommand {
public:
	CutCommand(FlowChartEditor *editor = 0);
	CutCommand(const CutCommand& source);
	virtual ~CutCommand();
	CutCommand& operator=(const CutCommand& source);

	virtual void Execute();
};


//DeleteCommand
class DeleteCommand : public FlowChartCommand {
public:
	DeleteCommand(FlowChartEditor *editor = 0);
	DeleteCommand(const DeleteCommand& source);
	virtual ~DeleteCommand();
	DeleteCommand& operator=(const DeleteCommand& source);

	virtual void Execute();
};

//SelectAllCommand
class SelectAllCommand : public FlowChartCommand {
public:
	SelectAllCommand(FlowChartEditor *editor = 0);
	SelectAllCommand(const SelectAllCommand& source);
	virtual ~SelectAllCommand();
	SelectAllCommand& operator=(const SelectAllCommand& source);

	virtual void Execute();
};

//StartCommand
class StartCommand : public FlowChartCommand {
public:
	StartCommand(FlowChartEditor *editor = 0);
	StartCommand(const StartCommand& source);
	virtual ~StartCommand();
	StartCommand& operator=(const StartCommand& source);

	virtual void Execute();
};

//PreparationCommand
class PreparationCommand : public FlowChartCommand {
public:
	PreparationCommand(FlowChartEditor *editor = 0);
	PreparationCommand(const PreparationCommand& source);
	virtual ~PreparationCommand();
	PreparationCommand& operator=(const PreparationCommand& source);

	virtual void Execute();
};

//InputCommand
class InputCommand : public FlowChartCommand {
public:
	InputCommand(FlowChartEditor *editor = 0);
	InputCommand(const InputCommand& source);
	virtual ~InputCommand();
	InputCommand& operator=(const InputCommand& source);

	virtual void Execute();
};

//ProcessCommand
class ProcessCommand : public FlowChartCommand {
public:
	ProcessCommand(FlowChartEditor *editor = 0);
	ProcessCommand(const ProcessCommand& source);
	virtual ~ProcessCommand();
	ProcessCommand& operator=(const ProcessCommand& source);

	virtual void Execute();
};

//DecisionCommand
class DecisionCommand : public FlowChartCommand {
public:
	DecisionCommand(FlowChartEditor *editor = 0);
	DecisionCommand(const DecisionCommand& source);
	virtual ~DecisionCommand();
	DecisionCommand& operator=(const DecisionCommand& source);

	virtual void Execute();
};

//OutputCommand
class OutputCommand : public FlowChartCommand {
public:
	OutputCommand(FlowChartEditor *editor = 0);
	OutputCommand(const OutputCommand& source);
	virtual ~OutputCommand();
	OutputCommand& operator=(const OutputCommand& source);

	virtual void Execute();
};

//StopCommand
class StopCommand : public FlowChartCommand {
public:
	StopCommand(FlowChartEditor *editor = 0);
	StopCommand(const StopCommand& source);
	virtual ~StopCommand();
	StopCommand& operator=(const StopCommand& source);

	virtual void Execute();
};

//PageSetCommand
class PageSetCommand : public FlowChartCommand {
public:
	PageSetCommand(FlowChartEditor *editor = 0);
	PageSetCommand(const PageSetCommand& source);
	virtual ~PageSetCommand();
	PageSetCommand& operator=(const PageSetCommand& source);

	virtual void Execute();
};

//PositionCommand
class PositionCommand : public FlowChartCommand {
public:
	PositionCommand(FlowChartEditor *editor = 0);
	PositionCommand(const PositionCommand& source);
	virtual ~PositionCommand();
	PositionCommand& operator=(const PositionCommand& source);

	virtual void Execute();
};

//SizeCommand
class SizeCommand : public FlowChartCommand {
public:
	SizeCommand(FlowChartEditor *editor = 0);
	SizeCommand(const SizeCommand& source);
	virtual ~SizeCommand();
	SizeCommand& operator=(const SizeCommand& source);

	virtual void Execute();
};

//IntervalCommand
class IntervalCommand : public FlowChartCommand {
public:
	IntervalCommand(FlowChartEditor *editor = 0);
	IntervalCommand(const IntervalCommand& source);
	virtual ~IntervalCommand();
	IntervalCommand& operator=(const IntervalCommand& source);

	virtual void Execute();
};

//SequenceCommand
class SequenceCommand : public FlowChartCommand {
public:
	SequenceCommand(FlowChartEditor *editor = 0);
	SequenceCommand(const SequenceCommand& source);
	virtual ~SequenceCommand();
	SequenceCommand& operator=(const SequenceCommand& source);

	virtual void Execute();
};

//IterationCommand
class IterationCommand : public FlowChartCommand {
public:
	IterationCommand(FlowChartEditor *editor = 0);
	IterationCommand(const IterationCommand& source);
	virtual ~IterationCommand();
	IterationCommand& operator=(const IterationCommand& source);

	virtual void Execute();
};

//SelectionCommand
class SelectionCommand : public FlowChartCommand {
public:
	SelectionCommand(FlowChartEditor *editor = 0);
	SelectionCommand(const SelectionCommand& source);
	virtual ~SelectionCommand();
	SelectionCommand& operator=(const SelectionCommand& source);

	virtual void Execute();
};

//CloseCommand
class CloseCommand : public FlowChartCommand {
public:
	CloseCommand(FlowChartEditor *editor = 0);
	CloseCommand(const CloseCommand& source);
	virtual ~CloseCommand();
	CloseCommand& operator=(const CloseCommand& source);

	virtual void Execute();
};

//RuleKeepCommand
class RuleKeepCommand : public FlowChartCommand {
public:
	RuleKeepCommand(FlowChartEditor *editor = 0);
	RuleKeepCommand(const RuleKeepCommand& source);
	virtual ~RuleKeepCommand();
	RuleKeepCommand& operator=(const RuleKeepCommand& source);

	virtual void Execute();
};

#endif //_FLOWCHARTCOMMANDS_H