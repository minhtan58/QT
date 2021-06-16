#ifndef FONTMANAGER_H
#define FONTMANAGER_H

#include <QObject>

class FontManager : public QObject
{
    Q_OBJECT

public:
    FontManager(QObject *parent = nullptr) : QObject(parent){}
    Q_INVOKABLE QString segoeUI() {return "Segoe UI";}
    Q_INVOKABLE QString segoeUILight() {return "Segoe UI Light";}
    Q_INVOKABLE QString segoeUISemiLight() {return "Segoe UI Semilight";}
    Q_INVOKABLE QString segoeUIBold() {return "Segoe UI Bold";}
};
#endif // FONTMANAGER_H
