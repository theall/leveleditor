#include "soundresourcedialog.h"
#include "ui_soundresourcedialog.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QStandardItemModel>

TSoundResourceSet::TSoundResourceSet()
{

}

TSoundResourceSet::~TSoundResourceSet()
{

}

void TSoundResourceSet::add(const TSoundResourceData &resourceData)
{
    mDataList.append(resourceData);
}

void TSoundResourceSet::add(QMediaContent *sound, const QString text)
{
    TSoundResourceData data;
    data.sound = sound;
    data.text = text;
    mDataList.append(data);
}

TSoundResourceDataList TSoundResourceSet::dataList() const
{
    return mDataList;
}

QString TSoundResourceSet::resourceRoot() const
{
    return mResourceRoot;
}

void TSoundResourceSet::setResourceRoot(const QString &resourceRoot)
{
    mResourceRoot = resourceRoot;
}

void TSoundResourceSet::operator =(const TSoundResourceSet &resourceSet)
{
    mResourceRoot = resourceSet.resourceRoot();
    mDataList = resourceSet.dataList();
}

TSoundResourceDialog::TSoundResourceDialog(QWidget *parent) :
    TAbstractDialog(parent, true),
    ui(new Ui::TSoundResourceDialog)
  , mPlayIcon(new QIcon(":/actionsdock/images/play.png"))
  , mStopIcon(new QIcon(":/actionsdock/images/stop_play.png"))
  , mCurrentPlayingMedia(nullptr)
{
    ui->setupUi(this);
    ui->btnImport->setEnabled(false);
    ui->twSound->horizontalHeader()->setVisible(false);
    ui->twSound->horizontalHeader()->setStretchLastSection(true);
    ui->twSound->verticalHeader()->setVisible(false);
    ui->twSound->horizontalHeader()->setFixedHeight(21);
    ui->twSound->setShowGrid(true);
    ui->twSound->setFocusPolicy(Qt::NoFocus);
    ui->twSound->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->twSound->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->twSound->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->twSound->setMouseTracking(true);
    ui->twSound->setColumnCount(2);
    ui->twSound->setColumnWidth(0, 32);
    mMediaPlayer.setVolume(100);
    connect(&mMediaPlayer,
            SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)),
            this,
            SLOT(slotMediaStatusChanged(QMediaPlayer::MediaStatus)));
    connect(&mMediaPlayer,
            SIGNAL(stateChanged(QMediaPlayer::State)),
            this,
            SLOT(slotMediaStateChanged(QMediaPlayer::State)));
}

TSoundResourceDialog::~TSoundResourceDialog()
{

}

QStringList TSoundResourceDialog::getSelectedSounds()
{
    QStringList sl;
    ui->twSound->setSelectionMode(QAbstractItemView::ExtendedSelection);
    if(exec() == QDialog::Accepted)
    {
        for(QTableWidgetItem *item : ui->twSound->selectedItems())
        {
            sl.append(item->text());
        }
    }
    if(mMediaPlayer.state()==QMediaPlayer::PlayingState)
        mMediaPlayer.stop();
    return sl;
}

QString TSoundResourceDialog::getSelectedSound()
{
    QString s;
    ui->twSound->setSelectionMode(QAbstractItemView::SingleSelection);
    if(exec() == QDialog::Accepted)
    {
        for(QTableWidgetItem *item : ui->twSound->selectedItems())
        {
            s = item->text();
            break;
        }
    }
    if(mMediaPlayer.state()==QMediaPlayer::PlayingState)
        mMediaPlayer.stop();
    return s;
}

void TSoundResourceDialog::setResourceSet(const TSoundResourceSet &resourceSet)
{
    ui->leFilter->clear();
    mResourceDir.setPath(resourceSet.resourceRoot());
    mResourceSetBackup = resourceSet;
    renderResourceSet(resourceSet.dataList());
}

void TSoundResourceDialog::clear()
{
    QStandardItemModel *itemModel = qobject_cast<QStandardItemModel*>(ui->twSound->model());
    if(itemModel)
        itemModel->clear();
    ui->leFilter->clear();
}

void TSoundResourceDialog::setMultiSelectionEnabled(bool enabled)
{
    ui->twSound->setSelectionMode(enabled?QAbstractItemView::ExtendedSelection:QAbstractItemView::SingleSelection);
}

void TSoundResourceDialog::on_btnImport_clicked()
{
    hide();

    QStringList fileNames = QFileDialog::getOpenFileNames(
                this,
                tr("Import audio"),
                "",
                tr("Audios formats (*.wav *.mp3 *.ogg)"));
    if(fileNames.size()>0)
    {
        QString resourcePath = mResourceDir.absolutePath();
        bool overWriteAll = false;
        for(QString fileName : fileNames)
        {
            QFileInfo fi(fileName);
            if(fi.absolutePath()==resourcePath)
                continue;
            QString imageFileName = fi.fileName();
            QString destFileName = mResourceDir.absoluteFilePath(imageFileName);
            bool fileExists = QFile::exists(destFileName);
            if(!overWriteAll && fileExists)
            {
                int code = QMessageBox::question(
                            this, tr("Question."),
                            tr("Destination file \"%1\" already exists, do you want to overwrite?").arg(imageFileName),
                            QMessageBox::YesToAll|QMessageBox::Yes|QMessageBox::No|QMessageBox::NoToAll);
                if(code == QMessageBox::NoToAll) {
                    break;
                } else if(code == QMessageBox::No) {
                    continue;
                } else if(code == QMessageBox::YesToAll) {
                    overWriteAll = true;
                }
            }
            if(fileExists)
                QFile::remove(destFileName);
            QFile::copy(fileName, destFileName);
        }
    }

    show();
}

void TSoundResourceDialog::on_leFilter_textChanged(const QString &filter)
{
    bool matchAll = filter.isEmpty();
    TSoundResourceDataList dataList;
    for(TSoundResourceData &data : mResourceSetBackup.dataList())
    {
        if(!matchAll && !data.text.contains(filter, Qt::CaseInsensitive))
            continue;

        dataList.append(data);
    }
    renderResourceSet(dataList);
}

void TSoundResourceDialog::on_btnOk_clicked()
{
    QStringList selectedSounds = getSelectedSounds();
    if(selectedSounds.size() > 0)
        emit soundsChoosed(selectedSounds);
    accept();
}

void TSoundResourceDialog::on_btnCancel_clicked()
{
    reject();
}

void TSoundResourceDialog::on_twSound_doubleClicked(const QModelIndex &index)
{
    Q_UNUSED(index);

    on_btnOk_clicked();
}

void TSoundResourceDialog::retranslateUi()
{
    ui->retranslateUi(this);
}

void TSoundResourceDialog::slotSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    Q_UNUSED(selected);
    Q_UNUSED(deselected);

    QItemSelectionModel *sm = ui->twSound->selectionModel();
    ui->btnOk->setEnabled(sm && !sm->selectedIndexes().empty());
}

void TSoundResourceDialog::slotPlayButtonClicked(bool checked)
{
    Q_UNUSED(checked);

    QToolButton *btn = static_cast<QToolButton*>(sender());
    QMediaContent *m = mButtonMediaMap.value(btn);
    if(mCurrentPlayingMedia == m)
    {
        mMediaPlayer.stop();
    } else {
        if(mCurrentPlayingMedia && mMediaPlayer.state()==QMediaPlayer::PlayingState)
        {
            // There is something playing, stop it
            mMediaPlayer.stop();
        }
        mCurrentPlayingMedia = m;
        mMediaPlayer.setMedia(*m);
        mMediaPlayer.play();
    }
}

void TSoundResourceDialog::slotMediaStatusChanged(QMediaPlayer::MediaStatus mediaStatus)
{
    Q_UNUSED(mediaStatus);
}

void TSoundResourceDialog::slotMediaStateChanged(QMediaPlayer::State mediaState)
{
    if(!mCurrentPlayingMedia)
        return;

    if(mediaState==QMediaPlayer::PlayingState)
    {
        mMediaButtonMap[mCurrentPlayingMedia]->setIcon(*mStopIcon);
    } else if(mediaState==QMediaPlayer::StoppedState) {
        mMediaButtonMap[mCurrentPlayingMedia]->setIcon(*mPlayIcon);
        mCurrentPlayingMedia = nullptr;
    }
}

void TSoundResourceDialog::renderResourceSet(const TSoundResourceDataList &dataList)
{
    if(ui->twSound->selectionModel())
        ui->twSound->selectionModel()->disconnect(this);

    for(QToolButton *btn : mButtonMediaMap.keys())
        btn->disconnect(this);
    mMediaButtonMap.clear();
    mButtonMediaMap.clear();

    ui->twSound->setRowCount(dataList.size());
    int row = 0;
    for(TSoundResourceData data : dataList)
    {
        QTableWidgetItem *item = new QTableWidgetItem;
        item->setText(data.text);
        ui->twSound->setItem(row, 1, item);
        QToolButton *btn = new QToolButton(ui->twSound);
        if(data.sound==mCurrentPlayingMedia)
            btn->setIcon(*mStopIcon);
        else
            btn->setIcon(*mPlayIcon);
        connect(btn, SIGNAL(clicked(bool)), this, SLOT(slotPlayButtonClicked(bool)));
        ui->twSound->setCellWidget(row, 0, btn);
        mMediaButtonMap.insert(data.sound, btn);
        mButtonMediaMap.insert(btn, data.sound);
        if(data.sound->isNull())
            btn->setEnabled(false);
        row++;
    }

    connect(ui->twSound->selectionModel(),
            SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
            this,
            SLOT(slotSelectionChanged(QItemSelection,QItemSelection)));
}
