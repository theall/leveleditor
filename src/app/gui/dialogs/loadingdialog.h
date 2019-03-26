#ifndef LOADINGDIALOG_H
#define LOADINGDIALOG_H

#include <QDialog>

namespace Ui {
class TLoadingDialog;
}

class TLoadingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TLoadingDialog(QWidget *parent = 0);
    ~TLoadingDialog();

    void setProgress(int progress, int total);
    bool isEnd() const;

private:
    bool mIsEnd;
    Ui::TLoadingDialog *ui;

    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event);
};

#endif // LOADINGDIALOG_H
