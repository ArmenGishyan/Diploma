#ifndef GUIERRORS_H
#define GUIERRORS_H

#include <string>

// This is Abstruct Base class all gui errors
class GuiMessageWirter
{
public:
    enum class Priority
    {
       INFO,
       WARNING,
       ERROR
    };
    GuiMessageWirter(GuiMessageWirter::Priority, std::string);
    Priority getPriority() const;
    virtual bool  execute() = 0;

protected:
    std::string m_errorMassage;
    Priority m_priority;
};

class TooManySelection : public GuiMessageWirter
{
public:
    TooManySelection(int count, GuiMessageWirter::Priority, std::string);
    bool execute() override;

private:
     // Count of Selected witch can be error
    int m_selectionCount;
};

class WrongSelectionCount : public GuiMessageWirter
{
public:
    WrongSelectionCount(GuiMessageWirter::Priority, std::string);
    bool execute() override;
};

#endif // GUIERRORS_H
