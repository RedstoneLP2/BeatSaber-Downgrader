#include "common.h"

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
            curl_easy_setopt(curl, CURLOPT_URL, "https://raw.githubusercontent.com/RedstoneLP2/BS_Downgrader_meta/master/BSVersions.json");
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
    std::cout << "Creating Backup!"<<std::endl;
    std::filesystem::copy(BSPath,BackupPath,std::filesystem::copy_options::recursive);
    return 0;
}

int copyDepot(std::filesystem::path BSPath){
    std::filesystem::path source = std::filesystem::path(std::filesystem::current_path().append("BeatSaberCache"));
    const auto copyOptions = std::filesystem::copy_options::overwrite_existing
                           | std::filesystem::copy_options::recursive;
    std::cout<<"Copying files!"<<std::endl;
    std::filesystem::copy(source,BSPath,copyOptions);
    std::cout<<"Finished Copying!"<<std::endl;
    return 0;
}

int findDepotDownloader(){
    std::filesystem::path cwd = std::filesystem::current_path().append("DepotDownloader");
    if (!std::filesystem::exists(cwd)){
        std::cout<< "DepotDownloader not found at "<<cwd<<std::endl;
        std::cout<< "Make sure you downloaded DepotDownloader and placed it in the Working Directory"<<std::endl;
        return 1;
    }
    return 0;
}