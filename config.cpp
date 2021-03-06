#include "mpdas.h"

const ScrobblingServiceDesc services[] = {
	/*[LastFm]  =*/ { "Last.fm" , "https://ws.audioscrobbler.com/2.0/" },
	/*[LibreFm] =*/ { "Libre.fm", "https://libre.fm/2.0/" },
};

int IniHandler(void* param, const char* section, const char* name, const char* value)
{
    CConfig* config = (CConfig*)param;
    std::string val = std::string(value);

    // strip quotes if they exist to allow passwords to begin with a whitespace
    if(val.length() >= 2 && val[0] == '\"' && val[val.length()-1] == '\"') {
		val.erase(0, 1);
		val.erase(val.length() - 1);
    }

    config->Set(name, val);

    return 1;
}

void CConfig::LoadConfig(const std::string &path)
{
    if(ini_parse(path.c_str(), &IniHandler, this) < 0) {
		iprintf("Cannot parse config file (%s).", path.c_str());
		return;
    }
}
std::string CConfig::Get(const std::string &name) const
{
    if(_configuration.find(name) == _configuration.end()) {
		return "";
    }

    return _configuration.find(name)->second;
}

bool CConfig::GetBool(const std::string &name) const
{
    std::string value = Get(name);
    return value == "1" || value == "true";
}

int CConfig::GetInt(const std::string &name) const
{
    return atoi(Get(name).c_str());
}

ScrobblingService CConfig::getService() const
{
    return Get("service") == "librefm" ? LibreFm : LastFm;
}

CConfig::CConfig(const char* cfg)
{
    /* Set optional settings to default */
    Set("host", "localhost");
    Set("port", "6600");
    Set("debug", "false");
    Set("service", "lastfm");

    std::string path = "";

    if(!cfg) {
		path = CONFDIR;
		path.append("/mpdasrc");
    }
    else {
		path = cfg;
    }

    LoadConfig(path);
}
