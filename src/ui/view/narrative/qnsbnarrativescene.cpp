#include "qnsbnarrativescene.h"

QnsbNarrativeScene::QnsbNarrativeScene(QObject* parent)
    : QnsbGraphicsScene(parent)
{
    reqwidth = 0;

    reqheight = 0;

    home = NULL;
}

QnsbNarrativeScene::~QnsbNarrativeScene()
{

}

void QnsbNarrativeScene::setHome(QnsbNarrativeChain* home)
{
    this->home = home;
}

void QnsbNarrativeScene::adjust()
{
    if (home != NULL){
        int gh = calcgh(home);

        reqwidth = 32 + gh*(128+48) + 100;

        int gw = calcgw(home);

        reqheight = gw*(80+32) + 100;

        if (getHeight() < reqheight){
            setHeight(reqheight);
        }

        if (getWidth() < reqwidth){
            setWidth(reqwidth);
        }

        home->setLeft(32);
        home->setTop(getHeight()/2 - (80+32)/2);
        home->setVisible(true);

        adjustg(home, 1, getHeight()/2);

        waux.clear();
    }
}

int QnsbNarrativeScene::calcgh(QnsbNarrativeChain* start)
{
    int H = 1;

    int cmp = H;

    foreach(QnsbNarrativeLink* link, start->getLinks()){
        if (link->getType() != "referencial"){
            int result = calcgh(link->getTarget());

            if (result+cmp > H){
                H = result+cmp;
            }
        }
    }

    return H;
}

int QnsbNarrativeScene::calcgw(QnsbNarrativeChain* start)
{
    int W = 1;

    int MAX = 0;
    int SUM = 0;

    foreach(QnsbNarrativeLink* link, start->getLinks()){
        if (link->getType() != "referencial"){
            int result = calcgw(link->getTarget());

            if (result > MAX){
                MAX = result;
            }
        }
    }

    SUM = MAX*start->getLinks().size();

    if (SUM > W){
        W = SUM;
    }

    waux[start->getUid()] = W;

    return W;
}

void QnsbNarrativeScene::adjustg(QnsbNarrativeChain* start, int n, int mid)
{
    int WMAX = 0;

    foreach(QnsbNarrativeLink* link, start->getLinks()){
        if (WMAX < waux[link->getTarget()->getUid()]){
            WMAX = waux[link->getTarget()->getUid()];
        }
    }

    int nl = start->getLinks().size();
    int mosttop = mid - WMAX*(nl)*(80+32)/2;

    int i = 0;

    foreach(QnsbNarrativeLink* link, start->getLinks()){
        QnsbNarrativeChain* next = link->getTarget();

        next->setLeft(32+n*(128+48));
        next->setTop(mosttop + WMAX*i*(80 + 32) + (WMAX-1)*(80 + 32)/2 );
        next->setVisible(true);

        if (link->getType() != "referencial"){
            adjustg(next, n+1, next->getTop() + 80/2 + 16);
        }

        link->adjust();

        i++;
    }
}
