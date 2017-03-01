#include "qnsbnarrative.h"

QnsbNarrative::QnsbNarrative()
{

}

QnsbNarrative::~QnsbNarrative()
{

}


QVector<QnsbChain*> QnsbNarrative::getChains() const
{
    return chains;
}

void QnsbNarrative::addChain(QnsbChain* chain)
{
    if (chain != NULL){
        chains.append(chain);
    }
}

void QnsbNarrative::removeChain(QnsbChain* chain)
{
    if (chain != NULL){
        int index = chains.indexOf(chain);

        if (index >= 0){
            chains.remove(index);
        }
    }
}
