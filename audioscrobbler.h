#ifndef _AUDIOSCROBBLER_H
#define _AUDIOSCROBBLER_H


class CAudioScrobbler
{
public:
	CAudioScrobbler(const CConfig *cfg);
	~CAudioScrobbler();

	std::string CreateScrobbleMessage(int index, const CacheEntry& entry);
	bool Scrobble(const CacheEntry& entry);
	void ReportResponse(const char* buf, size_t size);
	bool LoveTrack(const Song& song, bool unlove = false);
	bool SendNowPlaying(const Song& song);
	void Failure();
private:
	/* returns the session ID */
	std::string Handshake();
	std::string GetServiceURL();
	void OpenURL(const std::string &url, const char* postfields, char* errbuf);
	bool CheckFailure();

	const CConfig *_cfg;
	CURL* _handle;

	std::string _response;

	std::string _sessionid;

	bool _authed;
	int _failcount;
};

class CLastFMMessage
{
public:
	CLastFMMessage(CURL *curl_handle) { this->curl_handle = curl_handle; }
	void AddField(std::string name, std::string value) { valueMap[name] = value; }
	void AddField(std::string name, int value) {
		std::ostringstream str;
		str << value;
		AddField(name, str.str());
	}
	std::string GetMessage();
private:
	std::map<std::string, std::string> valueMap;
	std::string GetSignatureHash();
	CURL *curl_handle;
};

#endif
