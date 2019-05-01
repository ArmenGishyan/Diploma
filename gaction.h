#ifndef GACTION_H
#define GACTION_H

#include <QAction>
#include <ggraphicsitems.h>

class QGraphicsItem;
class QGraphicsRectItem;
class Editor;

class GAction : public QAction
{
    Q_OBJECT
public:
    GAction(QObject* parent = nullptr);
    GAction(const QString &text, QObject *parent = nullptr);
    GAction(const QIcon &icon, const QString &text, QObject *parent = nullptr);

    virtual GGraphicsItem* getObject() = 0;
};

class GRectAction : public GAction
{
    Q_OBJECT
public:
    GRectAction(QObject* parent = nullptr);
    GRectAction(const QString &text, QObject *parent = nullptr);
    GRectAction(const QIcon &icon, const QString &text, QObject *parent = nullptr);

    GGraphicsItem* getObject() override;

private:
    QGraphicsRectItem* m_rectItem;
};

// Line Action for drawing point
class GLineAction : public GAction
{
    Q_OBJECT
public:
    GLineAction(QObject* parent = nullptr);
    GLineAction(const QString &text, QObject *parent = nullptr);
    GLineAction(const QIcon &icon, const QString &text, QObject *parent = nullptr);

    GGraphicsItem* getObject() override;
};

class GNoneShapeAction : public GAction
{
public:
    GNoneShapeAction(QObject* parent = nullptr):GAction(parent){}
    GGraphicsItem* getObject() override {return nullptr;}
};

//------------------------------------------------Style Action-----------------------------------------------
class GStyleAction : public QAction
{
public:
    virtual void execute(Editor* editor) = 0;
};

class GBrushStyle : public GStyleAction
{
public:
    void execute(Editor* editor) override;

private:
    Qt::BrushStyle m_brushStyle;
};

class GBrushColor : public GStyleAction
{
public:
    GBrushColor();
    void execute(Editor* editor) override;
};

class GPenColor : public GStyleAction
{
public:
    GPenColor();
    void execute(Editor* editor) override;

};

class GPenStyle : public GStyleAction
{
public:
    void execute(Editor* editor) override;
};


#endif // GACTION_H
