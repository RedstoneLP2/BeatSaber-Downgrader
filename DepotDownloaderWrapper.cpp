#include "common.h"


std::string appId   = "620980";
std::string depotId = "620981";


int downloadDepot(std::string manifestId, std::string Username, std::string Password, DepotDownloader *DDL){
    if (findDepotDownloader()){
        return 1;
    }
    
    std::cout<<"Starting Download"<<std::endl;
    std::string cmd = std::format("./DepotDownloader -app {} -depot {} -manifest {} -username {} -password {} -dir {} -validate", appId, depotId, manifestId, Username, Password, std::filesystem::current_path().append("BeatSaberCache").string());
#ifdef _WIN32
    std::unique_ptr<FILE, decltype(&_pclose)> pipe(_popen(cmd.c_str(), "r"), _pclose);
#elif __linux__
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"), pclose);
#endif
    std::array<char, 128> buffer;
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        DDL->AppendTextbox(QString("test"));
        std::cout << buffer.data();

    }
    return 0;
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
    logOutput.appendPlainText(text);
    logOutput.repaint();
    return 0;
}