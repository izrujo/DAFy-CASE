/******************************************************************
* 파일 이름 : FlowChartApp.h
* 기능 : CWinApp 사용
* 작성자 : 송윤창
* 작성일자 : 2015년 4월 06일 
*******************************************************************/

#ifndef _FLOWCHARTAPP_H
#define _FLOWCHARTAPP_H 

#include <afxwin.h>

class FlowChartApp : public CWinApp{
	public:
		virtual BOOL InitInstance(); // Override to perform Windows instance initialization, such as creating your window objects.
};
#endif //_FLOWCHARTAPP_H
