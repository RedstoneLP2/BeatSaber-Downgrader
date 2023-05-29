#include "common.h"

std::string appId   = "620980";
std::string depotId = "620981";

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

Json::Value downloadAndParseJson(){
    CURL *curl;
    CURLcode res;
    std::string readBuffer;
    curl = curl_easy_init();
        if(curl) {
            curl_easy_setopt(curl, CURLOPT_URL, "https://raw.githubusercontent.com/RiskiVR/BSLegacyLauncher/master/Resources/BSVersions.json");
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);
        }
    Json::Reader reader;
    Json::Value obj;
    reader.parse(readBuffer, obj); 
    return obj;
}


// This will probably break some time!
std::string GetGameVersion(std::filesystem::path GamePath){
    std::filesystem::path gamemanagersPath = GamePath.append("Beat Saber_Data").append("globalgamemanagers");
    if (!std::filesystem::exists(gamemanagersPath)) return "Not Found! Check Path!";
    std::fstream fin(gamemanagersPath, std::ios::in|std::ios::binary);
    std::string key = "public.app-category.games";
    std::regex ver("[\\d]+.[\\d]+.[\\d]+");
    if (fin.is_open())
    {
        fin.seekg (0, fin.end);
        int length = fin.tellg();
        fin.seekg (0, fin.beg);
        char * buffer = new char [sizeof(int64_t)];

        int pos = 0;
        while (fin.tellg() < length && pos < key.size())
        {
            if (fin.get() == key[pos]) pos++;
            else pos = 0;
        }
        
        std::cout<<fin.tellg()<<std::endl;
        std::string version ;
        
        while (fin.tellg() < length)
        {
            char c = fin.get();
            if (std::isdigit(c)|| c == '.'){ 
                version += c;
            }else if(c == '_'){
                break;
            }
        }
        
        std::cout<<version<<std::endl;
    return version;
    }
}

int BackupBSPath(std::filesystem::path BSPath){
    std::filesystem::path BackupPath;
    BackupPath = BSPath;
    BackupPath+=std::filesystem::path(".bak");
    std::filesystem::remove_all(BackupPath);
    std::filesystem::copy(BSPath,BackupPath);
    return 0;
}

int copyDepot(std::filesystem::path BSPath){
    std::filesystem::path source = std::filesystem::path(getenv("HOME")).append(".steam").append("steamcmd").append("linux32").append("steamapps").append("content").append("app_620980").append("depot_620981");
    const auto copyOptions = std::filesystem::copy_options::overwrite_existing
                           | std::filesystem::copy_options::recursive;

    std::filesystem::copy(source,BSPath,copyOptions);
    return 0;
}

int downloadDepot(std::string manifestId, std::string Username, std::string Password, std::string SteamGuard=""){
    // Linux only for now
    std::string command = std::format("steamcmd +login {} {} {} +download_depot {} {} {} +quit",Username,Password,SteamGuard,appId,depotId,manifestId);
    return system(command.c_str());
}