#ifndef _FLOWCHARTCOMMANDFACTORY_H
#define _FLOWCHARTCOMMANDFACTORY_H

class FlowChartEditor;
class FlowChartCommand;

class FlowChartCommandFactory {
public:
	FlowChartCommandFactory(FlowChartEditor *editor = 0);
	FlowChartCommandFactory(const FlowChartCommandFactory& source);
	~FlowChartCommandFactory();
	FlowChartCommandFactory& operator=(const FlowChartCommandFactory& source);

	FlowChartCommand* Make(char *text);
private:
	FlowChartEditor *editor;
};

#endif //_FLOWCHARTCOMMANDFACTORY_H