#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include "tabwidget/tabwidget.h"

class TCentralWidget : public QWidget
{
public:
    TCentralWidget(QWidget *parent = nullptr);
    ~TCentralWidget();

    TTabWidget *tabWidget() const;

private:
    TTabWidget *mTabWidget;
};

#endif // CENTRALWIDGET_H
