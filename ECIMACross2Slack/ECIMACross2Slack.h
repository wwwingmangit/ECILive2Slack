/*  ------------------------------------------------------------------------

Developped by Emmanuel Chriqui (aka wwwingman).
See LICENCE file.

------------------------------------------------------------------------ */


#ifndef __ECI_MACROSS_TO_SLACK_H__
#define __ECI_MACROSS_TO_SLACK_H__

#pragma warning(push)
#pragma warning(disable : 26812 26451 6201 6385 6386)
#include <sierrachart.h>
#pragma warning(pop)

// version of project
#define ECI_PROJECT_NAME "ECIMACross2Slack"
#define ECI_PROJECT_VERSION "V2"

// channels hardcoded url for test/dev/...
enum class ECIMaCross2Slack_ChannelType
{
	Dev = 0,
	Test = 1,
	Prod = 2,
};
#define ECIMACROSS2SLACK_CHANNELTYPE_STRINGS "Dev;Test;Prod"

const SCString g_ECIMaCross2Slack_ChannelURLTable[] =
{
	"https://hooks.slack.com/services/TODO",
	"https://hooks.slack.com/services/TODO",
	"https://hooks.slack.com/services/TODO",
};

#endif __ECI_MACROSS_TO_SLACK_H__
