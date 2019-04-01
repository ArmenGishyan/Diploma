#include "gaction.h"
#include "editor.h"
#include "gstyledialog.h"

#include <QGraphicsItem>
#include <QColorDialog>


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
    return nullptr;//new GGraphicsPointItem;
}

QRectF GGraphicsPointItem::boundingRect() const
{

}

void GGraphicsPointItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}


void GPenColor::execute(Editor* editor)
{
    qDebug()<<"GLineColor::execute";
    QColorDialog* colorDialog = new QColorDialog;
    colorDialog->exec();
    if(editor) {
        QPen pen(editor->getPen());
        pen.setColor(colorDialog->currentColor());
        editor->setPen(pen);
    }
    colorDialog->deleteLater();
}

void GPenStyle::execute(Editor* editor)
{
    GPenStyleDialog* dialog = new GPenStyleDialog;
    if(QDialog::Accepted == dialog->exec()) {
        if(editor) {
            QPen pen(editor->getPen());
            pen.setWidth(dialog->getWidth());
            qDebug()<<"style = "<<dialog->getStyle();
            pen.setStyle(dialog->getStyle());
            editor->setPen(pen);
        }
    }

}
