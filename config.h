#ifndef _CONFIG_H
#define _CONFIG_H

enum ScrobblingService {
	LastFm,
	LibreFm
};

extern struct ScrobblingServiceDesc {
	const char *name;
	const char *url;
} const services[];

class CConfig
{
public:
	CConfig(const char* cfg);

	ScrobblingService getService() const;

	std::string Get(const std::string &name) const;
	bool GetBool(const std::string &name) const;
	int GetInt(const std::string &name) const;
	void Set(std::string name, std::string value) { _configuration[name] = value; };

	bool gotNecessaryData() const {
		if(!Get("username").size() || !Get("password").size())
			return false;
		return true;
	}

	void LoadConfig(const std::string &path);
private:
	void ParseLine(const std::string &line);
	std::map<std::string, std::string> _configuration;
};

#endif
