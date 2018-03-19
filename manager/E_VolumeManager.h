#ifndef E_VOLUMEMANAGER_H
#define E_VOLUMEMANAGER_H

#include <iostream>

#include <vtkSmartPointer.h>
#include <vtkMatrix4x4.h>

#include <vtkImageData.h>
#include <vtkColorTransferFunction.h>
#include <vtkPiecewiseFunction.h>
#include <vtkVolumeProperty.h>
#include <vtkSmartVolumeMapper.h>
#include <vtkImageProperty.h>
#include <vtkImageSliceMapper.h>
#include <vtkImageSlice.h>

#include <itkImage.h>
#include <itkImageFileReader.h>
#include <itkImageToVTKImageFilter.h>

#include "E_Volume.h"

class E_VolumeManager{
    public:
    enum{AXL, COR, SAG};
    static const int NUMSLICE = 3;

    ///ITK Image Type
    typedef itk::Image<short, 3> ImageType;
    typedef itk::ImageFileReader<ImageType> VolumeReader;
    typedef itk::ImageToVTKImageFilter<ImageType> itkVtkConverter;

    public:
    E_VolumeManager();
    ~E_VolumeManager();



    protected:   
    vtkSmartPointer<E_Volume> m_volume;

    ///Ground-truth volume
    vtkSmartPointer<vtkImageData> m_gimageData;
    vtkSmartPointer<vtkSmartVolumeMapper> m_gvolumeMapper;
    vtkSmartPointer<E_Volume> m_gvolume;

    ///Ground-truth reslice volume
    vtkSmartPointer<vtkImageSliceMapper> m_gresliceMapper[NUMSLICE];
    vtkSmartPointer<vtkImageSlice> m_gresliceActor[NUMSLICE];

    public:
    void ImportVolume(std::string path);
    void ImportGroundTruth(std::string path);

    void ForwardSlice(int idx);
    void BackwardSlice(int idx);

};

#endif //E_VOLUMEMANAGER_H