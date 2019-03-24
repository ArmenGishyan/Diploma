#include "gaction.h"

#include <QGraphicsItem>

GAction::GAction(QObject* parent):QAction (parent){}
GAction::GAction(const QString &text, QObject *parent):QAction (text, parent) {}
GAction::GAction(const QIcon &icon, const QString &text, QObject *parent) : QAction (icon,text,parent){}

GRectAction::GRectAction(QObject* parent):GAction(parent) {}
GRectAction::GRectAction(const QString &text, QObject *parent): GAction (text, parent) {}
GRectAction::GRectAction(const QIcon &icon, const QString &text, QObject *parent):GAction(icon,text,parent) {}

QGraphicsItem* GRectAction::getObject()
{
    return new QGraphicsRectItem;
}

GPointAction::GPointAction(QObject* parent):GAction(parent) {}
GPointAction::GPointAction(const QString &text, QObject *parent): GAction (text, parent) {}
GPointAction::GPointAction(const QIcon &icon, const QString &text, QObject *parent):GAction(icon,text,parent) {}

QGraphicsItem* GPointAction::getObject()
{
    return new GGraphicsPointItem;
}

QRectF GGraphicsPointItem::boundingRect() const
{

}

void GGraphicsPointItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}
