#ifndef QNSBNARRATIVESCENE_H
#define QNSBNARRATIVESCENE_H

#include "ui/view/qnsbgraphicsscene.h"

#include "qnsbnarrativechain.h"

class QnsbNarrativeScene : public QnsbGraphicsScene
{
public:
    QnsbNarrativeScene(QObject* parent = 0);

    virtual ~QnsbNarrativeScene();

    void setHome(QnsbNarrativeChain* home);

    void adjust();

    int calcgh(QnsbNarrativeChain* start);

    int calcgw(QnsbNarrativeChain* start);

    void adjustg(QnsbNarrativeChain* start, int n, int mid);

private:
    int reqwidth;

    int reqheight;

    QMap<QString, int> waux;

    QnsbNarrativeChain* home;
};

#endif // QNSBNARRATIVESCENE_H
