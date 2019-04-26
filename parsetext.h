#ifndef PARSETEXT_H
#define PARSETEXT_H

#include <QString>
#include <QStringList>
#include <vector>
#include <QList>
#include <QGraphicsItem>

class GGraphicsItem;

class ParseText
{
public:
    ParseText(std::vector<std::string> str);
    QList<GGraphicsItem*> parseShapes() const;

private:
    QList<QStringList> m_text;
};

#endif // PARSETEXT_H
