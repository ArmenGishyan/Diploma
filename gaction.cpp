#include "gaction.h"
#include "editor.h"
#include "gstyledialog.h"
#include "ggraphicsstyle.h"

#include <QGraphicsItem>
#include <QColorDialog>
#include "selectshapescolor.h"


GAction::GAction(QObject* parent):QAction (parent){}
GAction::GAction(const QString &text, QObject *parent):QAction (text, parent) {}
GAction::GAction(const QIcon &icon, const QString &text, QObject *parent) : QAction (icon,text,parent){}

GRectAction::GRectAction(QObject* parent):GAction(parent) {}
GRectAction::GRectAction(const QString &text, QObject *parent): GAction (text, parent) {}
GRectAction::GRectAction(const QIcon &icon, const QString &text, QObject *parent):GAction(icon,text,parent) {}

GGraphicsItem* GRectAction::getObject()
{
    return new GGraphicsRectItem;
}

GLineAction::GLineAction(QObject* parent):GAction(parent) {}
GLineAction::GLineAction(const QString &text, QObject *parent): GAction (text, parent) {}
GLineAction::GLineAction(const QIcon &icon, const QString &text, QObject *parent):GAction(icon,text,parent) {}

GGraphicsItem* GLineAction::getObject()
{
    return new GGraphicsLineItem;
}


void GPenColor::execute(Editor* editor)
{
    SelectShapesColor* colorDialog = new SelectShapesColor;
    if(colorDialog->exec() == QDialog::Accepted) {
        if(editor) {
          std::shared_ptr<GGraphicsStyle> style = editor->getStyle();
          style->setPen(QPen(colorDialog->currentColor()));
          editor->setStyle(style);
        }
    }
    colorDialog->deleteLater();
}

GPenColor::GPenColor()
{
    setText("Pen Color");
    setIcon(QIcon(":/Icons/pencolor.png"));
}
void GPenStyle::execute(Editor* editor)
{
    GPenStyleDialog* dialog = new GPenStyleDialog;
    if(QDialog::Accepted == dialog->exec()) {
        if(editor) {
           // QPen pen(editor->getPen());
           // pen.setWidth(dialog->getWidth());
           // pen.setStyle(dialog->getStyle());
           // editor->setPen(pen);
        }
    }

}

GBrushColor::GBrushColor()
{
    setText("Brush Color");
    setIcon(QIcon(":/Icons/fillcolor.png"));
}

void GBrushColor::execute(Editor* editor)
{
    SelectShapesColor* colorDialog = new SelectShapesColor;
    if(colorDialog->exec() == QDialog::Accepted) {
        if(editor) {
          std::shared_ptr<GGraphicsStyle> style = editor->getStyle();
          style->setBrush(QBrush(colorDialog->currentColor()));
        }
    }
    colorDialog->deleteLater();
}
