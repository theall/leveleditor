#pragma once

#include <QProxyStyle>

class TProxyStyle : public QProxyStyle
{
    Q_OBJECT

public:
    TProxyStyle(const QPalette &palette, QStyle *style = nullptr);

    void setPalette(const QPalette &palette);
    bool isDark() const;

    void drawPrimitive(PrimitiveElement element,
                       const QStyleOption *option,
                       QPainter *painter,
                       const QWidget *widget) const override;

    void drawControl(ControlElement element,
                     const QStyleOption *option,
                     QPainter *painter,
                     const QWidget *widget) const override;

    void drawComplexControl(ComplexControl control,
                            const QStyleOptionComplex *option,
                            QPainter *painter,
                            const QWidget *widget = nullptr) const override;

    int pixelMetric(PixelMetric metric,
                    const QStyleOption *option = nullptr,
                    const QWidget *widget = nullptr) const override;

    QSize sizeFromContents(ContentsType type,
                           const QStyleOption *option,
                           const QSize &contentsSize,
                           const QWidget *widget) const override;

    QRect subElementRect(SubElement subElement,
                         const QStyleOption *option,
                         const QWidget *widget) const override;

    int styleHint(StyleHint styleHint,
                  const QStyleOption *option,
                  const QWidget *widget,
                  QStyleHintReturn *returnData) const override;

    QIcon standardIcon(StandardPixmap standardIcon,
                       const QStyleOption *opt = nullptr,
                       const QWidget *widget = nullptr) const override;

private:
    QPalette mPalette;
    bool mIsDark;

    QIcon mDockClose;
    QIcon mDockRestore;
};


