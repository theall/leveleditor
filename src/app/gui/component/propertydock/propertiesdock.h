#ifndef PROPERTIESDOCK_H
#define PROPERTIESDOCK_H

#include "../basedock.h"
#include "propertybrowser.h"

#include <QLabel>
#include <QLineEdit>

class TPropertiesDock : public TBaseDock
{
    Q_OBJECT

public:
    explicit TPropertiesDock(QWidget *parent = nullptr);
    ~TPropertiesDock();

    TPropertyBrowser *propertyBrowser() const;
    void setText(const QString &text);
    void setIcon(const QPixmap &icon);

public slots:
    void bringToFront();

signals:

private slots:
    void slotSearchActionTriggered(bool checked);
    void slotFindWhatChanged(const QString &text);

private:
    QLabel *mIcon;
    QLabel *mText;
    QLabel *mSearchLabel;
    QLineEdit *mFindWhat;
    QWidget *mFindWidgetsWrap;
    TPropertyBrowser *mPropertyBrowser;

    QAction *mActionSearch;
    QAction *mActionConfig;

    void retranslateUi();
};

#endif // PROPERTIESDOCK_H
