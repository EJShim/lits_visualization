#ifndef E_SEGMENTATIONTHREAD_H
#define E_SEGMENTATIONTHREAD_H

#include <QThread>

class E_SegmentationThread : public QThread{    
    Q_OBJECT    

    public:
    void run();


    signals:
    void onCalculated(int i);
};



#endif