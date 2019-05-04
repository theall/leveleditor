#include "stylehelper.h"
#include "proxystyle.h"

#include <QStyle>
#include <QApplication>
#include <QPixmapCache>
#include <QStyleFactory>
#include <utils/preferences.h>

static QPalette createPalette(const QColor &windowColor,
                              const QColor &highlightColor)
{
    int hue, sat, windowValue;
    windowColor.getHsv(&hue, &sat, &windowValue);

    auto fromValue = [=](int value) {
        return QColor::fromHsv(hue, sat, qBound(0, value, 255));
    };

    const bool isLight = windowValue > 128;
    const int baseValue = isLight ? windowValue + 48 : windowValue - 24;

    const int lightTextValue = qMin(255, windowValue + 160);
    const int darkTextValue = qMax(0, windowValue - 160);

    const QColor lightText = QColor(lightTextValue, lightTextValue, lightTextValue);
    const QColor darkText = QColor(darkTextValue, darkTextValue, darkTextValue);
    const QColor lightDisabledText = QColor(lightTextValue, lightTextValue, lightTextValue, 128);
    const QColor darkDisabledText = QColor(darkTextValue, darkTextValue, darkTextValue, 128);

    QPalette palette(fromValue(windowValue));
    palette.setColor(QPalette::Base, fromValue(baseValue));
    palette.setColor(QPalette::AlternateBase, fromValue(baseValue - 10));
    palette.setColor(QPalette::WindowText, isLight ? darkText : lightText);
    palette.setColor(QPalette::ButtonText, isLight ? darkText : lightText);
    palette.setColor(QPalette::Text, isLight ? darkText : lightText);
    palette.setColor(QPalette::Light, fromValue(windowValue + 55));
    palette.setColor(QPalette::Dark, fromValue(windowValue - 55));
    palette.setColor(QPalette::Mid, fromValue(windowValue - 27));
    palette.setColor(QPalette::Midlight, fromValue(windowValue + 27));

    palette.setColor(QPalette::Disabled, QPalette::WindowText, isLight ? darkDisabledText : lightDisabledText);
    palette.setColor(QPalette::Disabled, QPalette::ButtonText, isLight ? darkDisabledText : lightDisabledText);
    palette.setColor(QPalette::Disabled, QPalette::Text, isLight ? darkDisabledText : lightDisabledText);

    bool highlightIsDark = qGray(highlightColor.rgb()) < 120;
    palette.setColor(QPalette::Highlight, highlightColor);
    palette.setColor(QPalette::HighlightedText, highlightIsDark ? Qt::white : Qt::black);

    return palette;
}

IMPL_SINGLE_INSTANCE(TStyleHelper)
TStyleHelper::TStyleHelper() :
    mDefaultStyle(QApplication::style()->objectName())
  , mDefaultPalette(QApplication::palette())
{
    apply();

    TPreferences *preferences = TPreferences::instance();
    QObject::connect(preferences, &TPreferences::applicationStyleChanged, this, &TStyleHelper::apply);
    QObject::connect(preferences, &TPreferences::baseColorChanged, this, &TStyleHelper::apply);
    QObject::connect(preferences, &TPreferences::selectionColorChanged, this, &TStyleHelper::apply);
}

const QString &TStyleHelper::defaultStyle()
{
    return mDefaultStyle;
}

const QPalette &TStyleHelper::defaultPalette()
{
    return mDefaultPalette;
}

void TStyleHelper::apply()
{
    TPreferences *preferences = TPreferences::instance();

    QString desiredStyle;
    QPalette desiredPalette;

    switch (preferences->applicationStyle()) {
    default:
    case TPreferences::SystemDefaultStyle:
        desiredStyle = defaultStyle();
        desiredPalette = defaultPalette();
        break;
    case TPreferences::FusionStyle:
        desiredStyle = QLatin1String("fusion");
        desiredPalette = createPalette(preferences->baseColor(),
                                       preferences->selectionColor());
        break;
    case TPreferences::TiledStyle:
        desiredStyle = QLatin1String("tiled");
        desiredPalette = createPalette(preferences->baseColor(),
                                       preferences->selectionColor());
        break;
    }

    QStyle *style = QApplication::style();
    if (style->objectName() != desiredStyle) {

        if (desiredStyle == QLatin1String("tiled")) {
            style = QStyleFactory::create(QLatin1String("fusion"));
            style = new TProxyStyle(desiredPalette, style);
        } else {
            style = QStyleFactory::create(desiredStyle);
        }

        QApplication::setStyle(style);
    }

    if (QApplication::palette() != desiredPalette) {
        QPixmapCache::clear();
        QApplication::setPalette(desiredPalette);

        if (TProxyStyle *proxyStyle = qobject_cast<TProxyStyle*>(style))
            proxyStyle->setPalette(desiredPalette);
    }

    emit styleApplied();
}
