#ifndef SOUNDRESOURCEDIALOG_H
#define SOUNDRESOURCEDIALOG_H

#include "abstractdialog.h"
#include <QDir>
#include <QMediaPlayer>
#include <QMediaContent>
#include <QToolButton>

class QItemSelection;
class QStandardItemModel;

namespace Ui {
class TSoundResourceDialog;
}

struct TSoundResourceData
{
    QMediaContent *sound;
    QString text;
    void operator =(const TSoundResourceData &data)
    {
        sound = data.sound;
        text = data.text;
    }
};

typedef QList<TSoundResourceData> TSoundResourceDataList;

class TSoundResourceSet
{
public:
    TSoundResourceSet();
    ~TSoundResourceSet();

    void add(const TSoundResourceData &data);
    void add(QMediaContent *sound, const QString text);

    TSoundResourceDataList dataList() const;

    QString resourceRoot() const;
    void setResourceRoot(const QString &resourceRoot);
    void operator =(const TSoundResourceSet &resourceSet);

private:
    QString mResourceRoot;
    TSoundResourceDataList mDataList;
};

class TSoundResourceDialog : public TAbstractDialog
{
    Q_OBJECT

public:
    explicit TSoundResourceDialog(QWidget *parent = 0);
    ~TSoundResourceDialog();

    QStringList getSelectedSounds();
    QString getSelectedSound();
    void setResourceSet(const TSoundResourceSet &resourceSet);
    void clear();
    void setMultiSelectionEnabled(bool enabled);

signals:
    void soundsChoosed(const QStringList &list);

private slots:
    void on_btnImport_clicked();
    void on_leFilter_textChanged(const QString &arg1);
    void on_btnOk_clicked();
    void on_btnCancel_clicked();
    void on_twSound_doubleClicked(const QModelIndex &index);
    void slotSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
    void slotPlayButtonClicked(bool checked);
    void slotMediaStatusChanged(QMediaPlayer::MediaStatus mediaStatus);
    void slotMediaStateChanged(QMediaPlayer::State mediaState);

private:
    Ui::TSoundResourceDialog *ui;
    QDir mResourceDir;
    QIcon *mPlayIcon;
    QIcon *mStopIcon;
    TSoundResourceSet mResourceSetBackup;
    QMediaPlayer mMediaPlayer;
    QMediaContent *mCurrentPlayingMedia;
    QMap<QToolButton*, QMediaContent*> mButtonMediaMap;
    QMap<QMediaContent*, QToolButton*> mMediaButtonMap;

    void renderResourceSet(const TSoundResourceDataList &dataList);

    // TAbstractDialog interface
private:
    void retranslateUi() Q_DECL_OVERRIDE;
};

#endif // SOUNDRESOURCEDIALOG_H
