/*  ------------------------------------------------------------------------

Developped by Emmanuel Chriqui (aka wwwingman).
See LICENCE file.

------------------------------------------------------------------------ */

#ifndef __ECIMACROSS2SLACK_CURL_H__
#define __ECIMACROSS2SLACK_CURL_H__

#pragma warning(push)
#pragma warning(disable : 26812 26451 6201 6385 6386)
#include <sierrachart.h>
#pragma warning(pop)

#include <string>

#pragma warning(push)
#pragma warning(disable : 26812 )
#define CURL_STATICLIB
#include "curl/curl.h"
#pragma warning(pop)

extern CURLcode ECIMACross2Slack_Curl_BuildAndSendSignal(SCStudyGraphRef sc,
	const char* slackWebHookURL,
	const char* signalText);

#endif __ECIMACROSS2SLACK_CURL_H__
