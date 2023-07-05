#include "ui_DepotDownloader.h"
#pragma once

namespace Ui {
class DepotDownloader;
}


class DepotDownloader : public QWidget
{
Q_OBJECT

public:
    explicit DepotDownloader(QWidget *parent = 0);
    ~DepotDownloader();
    int AppendTextbox(QString);

private:
    Ui::DepotDownloader *ui;
    DepotDownloader *pWindow;
    QPlainTextEdit logOutput;
        
};