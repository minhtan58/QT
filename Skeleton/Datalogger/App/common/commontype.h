#ifndef COMMONTYPE_H
#define COMMONTYPE_H

#include <QString>

typedef struct {
    QString time;
    QString valO2;
    QString valCO;
    QString valNO;
    QString valNOX;
    QString valSO2;
    QString valTEMP;
    QString valOPP;
    QString valDUSTPM;
    QString valVEL;
    QString valFLOW;
} CemsDataRow;

#endif // COMMONTYPE_H

