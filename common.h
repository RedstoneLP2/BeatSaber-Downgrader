#include <vector>
#include <curl/curl.h>
#include <iostream>
#include <json/json.h>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <string>
#include <regex>
#include <format>
#include <stdlib.h>
#include <QSettings>

std::string GetGameVersion(std::filesystem::path);
Json::Value downloadAndParseJson();
static std::string *DownloadedResponse;
static int writer(char*, size_t, size_t, std::string*);
int downloadDepot(std::string, std::string, std::string , std::string);
int BackupBSPath(std::filesystem::path);
int copyDepot(std::filesystem::path);
