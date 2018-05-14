#ifndef _AUDIOSCROBBLER_H
#define _AUDIOSCROBBLER_H

class LibCURL {
public:
	LibCURL(long flags = CURL_GLOBAL_ALL);
	~LibCURL();
};

class LibCURLEasy : LibCURL {
public:
	LibCURLEasy();
	~LibCURLEasy();
	operator CURL *() const { return _handle; }
private:
	CURL *const _handle;
};

class CAudioScrobbler
{
public:
	CAudioScrobbler(const CConfig &cfg);

	std::string CreateScrobbleMessage(int index, const CacheEntry& entry);
	bool Scrobble(const CacheEntry& entry);
	bool LoveTrack(const Song& song, bool unlove = false);
	bool SendNowPlaying(const Song& song);
	void Failure();
private:
	/* returns the session ID */
	std::string Handshake();
	const char * GetServiceURL();
	std::string OpenURL(const char *url, const char* postfields, char* errbuf);
	bool CheckFailure(const std::string &_response);

	const CConfig &_cfg;
	const LibCURLEasy _handle;

	bool _authed;
	int _failcount;

	std::string _sessionid;
};

class CLastFMMessage
{
public:
	void AddField(std::string name, std::string value) { valueMap[name] = value; }
	void AddField(std::string name, int value) {
		std::ostringstream str;
		str << value;
		AddField(name, str.str());
	}
	std::string GetMessage(CURL *curl_handle) const;
private:
	std::map<std::string, std::string> valueMap;
	std::string GetSignatureHash() const;
};

#endif
