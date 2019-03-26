#ifndef MAINPROPERTYCONTROLLER_H
#define MAINPROPERTYCONTROLLER_H

#include "propertycontroller.h"

class TMainPropertyController : public TPropertyController
{
    Q_OBJECT

public:
    TMainPropertyController(QObject *parent = nullptr);
    ~TMainPropertyController();

    // TAbstractController interface
    bool joint(TMainWindow *mainWindow, TCore *core) Q_DECL_OVERRIDE;

    void setCurrentDocument(TDocument *document) Q_DECL_OVERRIDE;

private slots:
    void slotOnSelectedObjectChanged(TObject *prev, TObject *current);

public slots:
    void setPropertySheet(TPropertySheet *propertySheet);

private:

};

#endif // MAINPROPERTYCONTROLLER_H
