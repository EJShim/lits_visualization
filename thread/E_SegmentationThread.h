#ifndef E_SEGMENTATIONTHREAD_H
#define E_SEGMENTATIONTHREAD_H

#include <QThread>

#include <vtkSmartPointer.h>
#include <vtkImageData.h>

class E_SegmentationThread : public QThread{    
    Q_OBJECT


    protected:
    vtkSmartPointer<vtkImageData> m_imageData;

    public:
    void run();
    void SetImageData(vtkSmartPointer<vtkImageData> data){m_imageData = data;}


    signals:
    void onCalculated(int i);
};



#endif