#include <QtWidgets/QMainWindow>
#include <QFileDialog>

namespace Ui {
class BeatsaberDowngraderWindow;
}

class BeatsaberDowngraderWindow : public QMainWindow
{
Q_OBJECT

public:
    explicit BeatsaberDowngraderWindow(QMainWindow *parent = 0);
    ~BeatsaberDowngraderWindow();

private slots:
    void on_ReloadBSVersionsBtn_clicked();
    void on_DowngradeBtn_clicked();
    void on_BSPathSelectBtn_clicked();
    void on_ReloadCurrBSVersionBtn_clicked();
    void on_BSPath_textChanged(QString);

private:
    Ui::BeatsaberDowngraderWindow *ui;
    BeatsaberDowngraderWindow *pWindow;
        
};