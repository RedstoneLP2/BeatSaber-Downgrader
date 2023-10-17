#include "common.h"


std::string appId   = "620980";
std::string depotId = "620981";


int downloadDepot(std::string manifestId, std::string Username, std::string Password, DepotDownloader *DDL){
    if (findDepotDownloader()){
        return 1;
    }
    
    std::cout<<"Starting Download"<<std::endl;
    std::string cmd = std::format("./DepotDownloader -app {} -depot {} -manifest {} -username {} -password {} -dir {} -validate 2>&1", appId, depotId, manifestId, Username, Password, std::filesystem::current_path().append("BeatSaberCache").string());
    int ret = 0;
#ifdef _WIN32
    const auto deleter = [&ret](FILE* file) { ret = file ? _pclose(file) : 0; };
    std::unique_ptr<FILE, decltype(deleter)> pipe(_popen(cmd.c_str(), "r"), deleter);
#elif __linux__
    const auto deleter = [&ret](FILE* file) { ret = file ? pclose(file) : 0; };
    std::unique_ptr<FILE, decltype(deleter)> pipe(popen(cmd.c_str(), "r"), deleter);
#endif
    std::array<char, 128> buffer;
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        DDL->AppendTextbox(QString(buffer.data()));
        //std::cout << buffer.data();

    }
    std::cout << "RETURN CODE: " << ((std::string(buffer.data()).find("Error") == -1) ? 0 : 1) <<std::endl;
    return ((std::string(buffer.data()).find("Error") == -1) ? 0 : 1);
}

DepotDownloader::DepotDownloader(QWidget *parent) : QWidget(parent), ui(new Ui::DepotDownloader)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
}

DepotDownloader::~DepotDownloader()
{
    delete ui;
}

int DepotDownloader::AppendTextbox(QString text){
    ui->logOutput->appendPlainText(text);
    ui->logOutput->repaint();
    return 0;
}