/*  ------------------------------------------------------------------------

Developped by Emmanuel Chriqui (aka wwwingman).
See LICENCE file.

------------------------------------------------------------------------ */
#include "ECIMACross2Slack_Curl.h"
#include <string>

static std::size_t WriteMemoryCallback(const char* in, std::size_t size, std::size_t num, std::string* out)
{
	const std::size_t totalBytes(size * num);
	out->append(in, totalBytes);
	return totalBytes;
}

CURLcode ECIMACross2Slack_Curl_BuildAndSendSignal(SCStudyGraphRef sc,
	const char* slackWebHookURL,
	const char* signalText)
{
	SCString logMsg;

	//
	// send the signal to Slack using libCurl
	//
	curl_global_init(CURL_GLOBAL_ALL);

	CURLcode res = CURLE_OK;
	CURL* curl = curl_easy_init();
	if (!curl)
		return res;

	// set content type to json
	struct curl_slist* headers = NULL;
	headers = curl_slist_append(headers, "Content-Type: application/json");
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

	// set url, Follow HTTP redirects if necessary
	curl_easy_setopt(curl, CURLOPT_URL, slackWebHookURL);
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
	// set POST parameters
	std::string _params = "{\"text\":\"" + (std::string)signalText + "\"}";
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, _params.c_str());
	curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(_params.c_str()));

	// send all data to this function
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);

	// we pass our 'chunk' struct to the callback function
	std::string postAnswer;
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&postAnswer);

	// some servers don't like requests that are made without a user-agent field, so we provide one
	curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");

	// make the Post request
	res = curl_easy_perform(curl);

	// check results
	if (res != CURLE_OK)
	{
		logMsg.Format("ERROR, Curl curl_easy_perform() failed: <%s>", curl_easy_strerror(res));
		sc.AddMessageToLog(logMsg, 1);
	}

	// always cleanup
	curl_easy_cleanup(curl);

	// global cleanup
	curl_global_cleanup();

	return res;
}
