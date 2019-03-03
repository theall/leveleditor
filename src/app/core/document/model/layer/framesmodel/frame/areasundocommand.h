#ifndef AREASUNDOCOMMAND_H
#define AREASUNDOCOMMAND_H

#include <QUndoCommand>

enum AreasUndoCommand
{
    AUC_ADD = 0,
    AUC_REMOVE,
    AUC_MOVE,
    AUC_COUNT
};

class TArea;
class TAreaManager;

class TAreasUndoCommand : public QUndoCommand
{
public:
    TAreasUndoCommand(AreasUndoCommand command,
                       TAreaManager *areaManager,
                       TArea *area,
                       QUndoCommand *parent = nullptr);
    TAreasUndoCommand(AreasUndoCommand command,
                       TAreaManager *areaManager,
                       const QList<TArea*> &areaList,
                       QUndoCommand *parent = nullptr);
    TAreasUndoCommand(AreasUndoCommand command,
                       TAreaManager *areaManager,
                       const QList<TArea*> &areaList,
                       const QPointF &distance,
                       QUndoCommand *parent = nullptr);
    ~TAreasUndoCommand();

    QList<TArea *> areaList() const;
    QPointF moveDistance() const;

private:
    TAreaManager *mAreaManager;
    AreasUndoCommand mCommand;
    QList<TArea *> mAreaList;
    QPointF mMoveDistance;

    // QUndoCommand interface
public:
    int id() const Q_DECL_OVERRIDE;
    bool mergeWith(const QUndoCommand *other) Q_DECL_OVERRIDE;
    void undo() Q_DECL_OVERRIDE;
    void redo() Q_DECL_OVERRIDE;
};


#endif // AREASUNDOCOMMAND_H
