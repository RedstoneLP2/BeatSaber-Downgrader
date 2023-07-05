#pragma once
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
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>
#include "DepotDownloaderWrapper.h"


std::string GetGameVersion(std::filesystem::path);
Json::Value downloadAndParseJson();
static std::string *DownloadedResponse;
static int writer(char*, size_t, size_t, std::string*);
int downloadDepot(std::string, std::string, std::string,DepotDownloader*);
int BackupBSPath(std::filesystem::path);
int copyDepot(std::filesystem::path);
int findDepotDownloader();