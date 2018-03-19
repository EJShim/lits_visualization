#include "E_SegmentationThread.h"



void E_SegmentationThread::run(){

    int* dims = m_imageData->GetDimensions();

    for(int i=0 ; i<dims[2] ; i++){     
        msleep(500);
        emit onCalculated(i);
    }

}