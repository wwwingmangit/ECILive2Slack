/*  ------------------------------------------------------------------------

Developped by Emmanuel Chriqui (aka wwwingman).
See LICENCE file.

------------------------------------------------------------------------ */
#include "ECIMACross2Slack.h"

//
// DLL
const SCString g_ScDllName = (SCString)ECI_PROJECT_NAME + (SCString)ECI_PROJECT_VERSION;
SCDLLName(g_ScDllName)

//
// Send modes
//
enum class ECIMACross2Slack_SendMode
{
	DontSendEvents = 0,
	SendRealtimeEvents,
};
#define ECIMACROSS2SLACK_SENDMODE_STRINGS "Don't send;Send Realtime Events"


// ------------------------------------------------------------------------
//
// scsf_ECIMACross2Slack Study
//
// ------------------------------------------------------------------------
SCSFExport scsf_ECIMACross2Slack(SCStudyGraphRef sc)
{
	SCString _logMsg;

	//
	// study descriptions
	//
	const SCString _studyName = "ECIMACross2Slack";
	const SCString _studyVersion = "V1";
	const SCString _studyDescription =
		"<p>ECIMACross2Slack: Illustrate MACross detection and send signal to Slack</p>"
		"<p>This is an open source tool under MIT Licence.</p>"
		"<p>Developped by Emmanuel Chriqui aka wwwingman.</p>";

	//
	// subgraphs
	//
	unsigned _sgCnt = 0;

	SCSubgraphRef _upSignalSG = sc.Subgraph[_sgCnt++];
	SCSubgraphRef _dnSignalSG = sc.Subgraph[_sgCnt++];

	//
	// input
	//
	unsigned _inCnt = 0;

	SCInputRef _fastMAIN = sc.Input[_inCnt++];
	SCInputRef _slowMAIN = sc.Input[_inCnt++];

	SCInputRef  _timeFilterStartTimeIN	= sc.Input[_inCnt++];
	SCInputRef  _timeFilterEndTimeIN	= sc.Input[_inCnt++];

	SCInputRef _drawOffsetInTicksIN = sc.Input[_inCnt++];

	//
	// Initialize configuration variables
	//
	if (sc.SetDefaults)
	{
		// General
		sc.GraphName = _studyName + _studyVersion;
		sc.StudyDescription = _studyDescription;
		sc.GraphRegion = 0;

		// subgraphs
		_upSignalSG.Name = "Up Signal";
		_upSignalSG.DrawStyle = DRAWSTYLE_ARROWUP;
		_upSignalSG.PrimaryColor = COLOR_GREEN;
		_upSignalSG.LineWidth = 3;

		_dnSignalSG.Name = "Dn Signal";
		_dnSignalSG.DrawStyle = DRAWSTYLE_ARROWDOWN;
		_dnSignalSG.PrimaryColor = COLOR_RED;
		_dnSignalSG.LineWidth = 3;

		// input
		_fastMAIN.Name = "Fast MA Study";
		_fastMAIN.SetStudySubgraphValues(0, 0);

		_slowMAIN.Name = "Slow MA Study";
		_slowMAIN.SetStudySubgraphValues(0, 0);

		_timeFilterStartTimeIN.Name = "Time Filter Start time?";
		_timeFilterStartTimeIN.SetTime(HMS_TIME(03, 00, 0));
		_timeFilterEndTimeIN.Name = "Time Filter End time?";
		_timeFilterEndTimeIN.SetTime(HMS_TIME(14, 59, 59));

		_drawOffsetInTicksIN.Name = "Draw offset in Ticks?";
		_drawOffsetInTicksIN.SetInt(10);
		_drawOffsetInTicksIN.SetIntLimits(0, INT_MAX);

		// misc
		sc.AutoLoop = true;
		sc.CalculationPrecedence = LOW_PREC_LEVEL; // needed for external input data

		return;
	}

	//
	// Initialize
	//
	int _currentBarIndex = sc.Index;

	// compute once per bar, on bar close
	if (sc.GetBarHasClosedStatus(_currentBarIndex) != BHCS_BAR_HAS_CLOSED)
		return;

	// reset subgraphs to zero before computation
	for (unsigned _sgIdx = 0; _sgIdx < _sgCnt; _sgIdx++)
		sc.Subgraph[_sgIdx][_currentBarIndex] = 0.;

	//
	// Get MA Data
	// 
	SCFloatArray _fastMAFA, _slowMAFA;

	if (((sc.GetStudyArrayUsingID(_fastMAIN.GetStudyID(), _fastMAIN.GetSubgraphIndex(), _fastMAFA) == 0) || (_fastMAFA.GetArraySize() == 0)) ||
		((sc.GetStudyArrayUsingID(_slowMAIN.GetStudyID(), _slowMAIN.GetSubgraphIndex(), _slowMAFA) == 0) || (_slowMAFA.GetArraySize() == 0)))
	{
		if (_currentBarIndex == 0)
			sc.AddMessageToLog("Error. Cannot Get MA Data", 1);
		return;
	}

	//
	// PreCompute tests
	//

	// check if bar is allowed for computation
	const int _timeFilterStartTime = _timeFilterStartTimeIN.GetTime();
	const int _timeFilterEndTime = _timeFilterEndTimeIN.GetTime();

	const int _currentBarTime = sc.BaseDateTimeIn[_currentBarIndex].GetTime();
	const int _currentBarAllowedInTime = (_timeFilterStartTime <= _timeFilterEndTime) ?
		(_timeFilterStartTime <= _currentBarTime && _currentBarTime <= _timeFilterEndTime) :
		(_timeFilterStartTime <= _currentBarTime || _currentBarTime <= _timeFilterEndTime);

	if (!_currentBarAllowedInTime)
		return;

	//
	// Compute
	//

	const float _curBarFastMA = _fastMAFA[_currentBarIndex];
	const float _curBarSlowMA = _slowMAFA[_currentBarIndex];
	const float _prevBarFastMA = _fastMAFA[_currentBarIndex-1];
	const float _prevBarSlowMA = _slowMAFA[_currentBarIndex-1];

	const int _upSignal = (_prevBarSlowMA > _prevBarFastMA) && (_curBarSlowMA < _curBarFastMA);
	const int _dnSignal = (_prevBarSlowMA < _prevBarFastMA) && (_curBarSlowMA > _curBarFastMA);

	//
	// Draw
	//
	const unsigned _drawOffsetInTicks = _drawOffsetInTicksIN.GetInt();
	const float _drawOffset = (float)_drawOffsetInTicks * sc.TickSize;

	_upSignalSG[_currentBarIndex] = _upSignal ? sc.Low[_currentBarIndex] - _drawOffset : 0.f;
	_dnSignalSG[_currentBarIndex] = _dnSignal ? sc.High[_currentBarIndex] + _drawOffset : 0.f;
}
