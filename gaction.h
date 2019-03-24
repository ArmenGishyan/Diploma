#ifndef GACTION_H
#define GACTION_H

#include <QAction>
#include <ggraphicspointitem.h>

class QGraphicsItem;
class QGraphicsRectItem;


class GAction : public QAction
{
    Q_OBJECT
public:
    GAction(QObject* parent = nullptr);
    GAction(const QString &text, QObject *parent = nullptr);
    GAction(const QIcon &icon, const QString &text, QObject *parent = nullptr);

    virtual QGraphicsItem* getObject() = 0;
};

class GRectAction : public GAction
{
    Q_OBJECT
public:
    GRectAction(QObject* parent = nullptr);
    GRectAction(const QString &text, QObject *parent = nullptr);
    GRectAction(const QIcon &icon, const QString &text, QObject *parent = nullptr);

    QGraphicsItem* getObject() override;

private:
    QGraphicsRectItem* m_rectItem;
};

class GPointAction : public GAction
{
    Q_OBJECT
public:
    GPointAction(QObject* parent = nullptr);
    GPointAction(const QString &text, QObject *parent = nullptr);
    GPointAction(const QIcon &icon, const QString &text, QObject *parent = nullptr);

    QGraphicsItem* getObject() override;

private:
    GGraphicsPointItem* m_pointItem;
};

#endif // GACTION_H
