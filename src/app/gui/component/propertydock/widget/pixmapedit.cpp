#include "pixmapedit.h"

#include <QHBoxLayout>
#include <QToolButton>

TPixmapEdit::TPixmapEdit(QWidget *parent) :
    QWidget(parent)
  , mPixmap(new QLabel(this))
  , mText(new QLabel(this))
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setMargin(0);
    layout->setSpacing(0);

    mPixmap->setScaledContents(true);
    mPixmap->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    mText->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred));

    QToolButton *button = new QToolButton(this);
    button->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred));
    button->setFixedWidth(20);
    button->setText(QLatin1String("..."));
    layout->addWidget(mPixmap);
    layout->addWidget(mText);
    layout->addWidget(button);

    connect(button, SIGNAL(clicked()), this, SLOT(slotButtonClicked()));
}

TPixmapEdit::~TPixmapEdit()
{

}

QPixmap TPixmapEdit::pixmap() const
{
    return *mPixmap->pixmap();
}

void TPixmapEdit::setPixmap(const QPixmap &pixmap)
{
    mPixmap->setPixmap(pixmap);
}

void TPixmapEdit::slotButtonClicked()
{
    QPixmap pixmap;
    QString text;
    emit getSelectedPixmap(text, pixmap);
    if(text.isEmpty())
        return;

    mPixmap->setPixmap(pixmap);
    mText->setText(text);
    emit pixmapChanged(text, pixmap);
}

QString TPixmapEdit::text() const
{
    return mText->text();
}

void TPixmapEdit::setText(const QString &text)
{
    mText->setText(text);
}
