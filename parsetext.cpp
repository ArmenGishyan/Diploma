#include "parsetext.h"
#include <string>
#include "ggraphicsitems.h"

ParseText::ParseText(std::vector<std::string> str)
{
    for(int i = 0; i < str.size(); ++i) {
        QString strItem = QString::fromStdString(str[i]);
        QStringList itemList = strItem.split("{", QString::SkipEmptyParts);
        itemList.removeAt(0);
        m_text.push_back(itemList);
    }
}

QList<GGraphicsItem*> ParseText::parseShapes() const
{
    QList<GGraphicsItem*> listOfItem;

    for(int i = 0; i < m_text.size(); ++i)
    {
        if(m_text[i].first() == "Rect") {
            GGraphicsRectItem* item = new GGraphicsRectItem;
            item->parseShape(m_text[i]);
            listOfItem.push_back(item);
        }
    }

    return listOfItem;
}
