#ifndef TOPBARADAPTER_H
#define TOPBARADAPTER_H

#include <QObject>
#include <QQuickItem>

#include "Common.h"
#include "DataManager.h"

class TopBarAdapter : public QObject
{
    Q_OBJECT
public:
    explicit TopBarAdapter(QQuickItem *container, QObject *parent = nullptr);
    void initAppData();

public slots:
    void updateAppData(int dpid);

private:
    QQuickItem *m_topbarContainer = nullptr;
    QObject *m_topBarView = nullptr;
};

#endif // TOPBARADAPTER_H