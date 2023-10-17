#include "ui_Main.h"
#include "MainUI.h"
#include "common.h"
#include <iostream>
#include <QtConcurrent>

BeatsaberDowngraderWindow::BeatsaberDowngraderWindow(QMainWindow *parent) : QMainWindow(parent), ui(new Ui::BeatsaberDowngraderWindow)
{
    ui->setupUi(this);
    readSettings();
    this->setFixedSize(this->size());
    this->on_ReloadBSVersionsBtn_clicked();
    this->show();
}

BeatsaberDowngraderWindow::~BeatsaberDowngraderWindow()
{
    delete ui;
}

void BeatsaberDowngraderWindow::on_ReloadBSVersionsBtn_clicked(){
    Json::Value versions = downloadAndParseJson();
    ui->BSVersionSelect->clear();
    for (int i = 0; i < versions.size(); i++)
    {
        ui->BSVersionSelect->addItem(QString(versions[i]["BSVersion"].asString().c_str()),QVariant(versions[i]["BSManifest"].asString().c_str()));
    }
}


void BeatsaberDowngraderWindow::on_DowngradeBtn_clicked(){
    
    writeSettings();
    std::string manifestId = ui->BSVersionSelect->currentData().toString().toStdString();
    std::filesystem::path BSPath = std::filesystem::path(ui->BSPath->text().toStdString());
    std::string Username = ui->UsernameEntry->text().toStdString();
    std::string Password = ui->PasswordEntry->text().toStdString();
    bool SkipBackup = ui->SkipBackup->isChecked();
    
    QtConcurrent::run([=]() {
        DDL = new DepotDownloader();
        ui->DowngradeBtn->setEnabled(false);
        DDL->show();
        if(!SkipBackup){
            BackupBSPath(BSPath);
        }
        
        //DDL->show();
        if (!downloadDepot(manifestId,Username,Password,DDL)) {
            copyDepot(BSPath);
        }
        ui->DowngradeBtn->setEnabled(true);
    });
}

void BeatsaberDowngraderWindow::on_BSPathSelectBtn_clicked(){
    QFileDialog FileDialog(this);
    FileDialog.setFileMode(QFileDialog::Directory);

    QStringList fileNames;
    FileDialog.setWindowTitle(QString("Select BeatSaber Main Directory"));
    if (FileDialog.exec()){
        fileNames = FileDialog.selectedFiles();
        std::cout<<fileNames.at(0).toStdString()<<std::endl;
        ui->BSPath->setText(fileNames.at(0));
    }
}

void BeatsaberDowngraderWindow::on_BSPath_textChanged(QString text){
        on_ReloadCurrBSVersionBtn_clicked();
}

void BeatsaberDowngraderWindow::on_ReloadCurrBSVersionBtn_clicked(){
    ui->CurrBSVersion->setText(QString(GetGameVersion(std::filesystem::path(ui->BSPath->text().toStdString())).c_str()));    
}

void BeatsaberDowngraderWindow::readSettings()
{
    QSettings settings("RedstoneLP2", "BS_Downgrader");


    settings.beginGroup("BS_DowngraderSettings");
    ui->UsernameEntry->setText(settings.value("SteamUsername").toString());
    ui->BSPath->setText(settings.value("BSPath").toString());
    settings.endGroup();
}

void BeatsaberDowngraderWindow::writeSettings()
{
    QSettings settings("RedstoneLP2", "BS_Downgrader");


    settings.beginGroup("BS_DowngraderSettings");
    settings.setValue("SteamUsername",ui->UsernameEntry->text());
    settings.setValue("BSPath",ui->BSPath->text());
    settings.endGroup();
}