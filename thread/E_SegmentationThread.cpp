#include "E_SegmentationThread.h"



void E_SegmentationThread::run(){

    for(int i=0 ; i<10 ; i++){
        sleep(1);
        emit onCalculated(i);
    }

}