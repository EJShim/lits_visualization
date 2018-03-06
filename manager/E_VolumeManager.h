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
#include <vtkVolume.h>
#include <vtkImageProperty.h>
#include <vtkImageSliceMapper.h>
#include <vtkImageSlice.h>

#include <itkImage.h>
#include <itkImageFileReader.h>
#include <itkImageToVTKImageFilter.h>

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

    public:
    void ImportVolume(std::string path);
    void ImportGroundTruth(std::string path);


    protected:
    //Volume Properties
    vtkSmartPointer<vtkColorTransferFunction> m_colorFunc;
    vtkSmartPointer<vtkPiecewiseFunction> m_opacFunc;
    vtkSmartPointer<vtkVolumeProperty> m_volumeProperty;
    vtkSmartPointer<vtkImageProperty> m_imageProperty;
    
    //Volume 
    vtkSmartPointer<vtkImageData> m_imageData;
    vtkSmartPointer<vtkSmartVolumeMapper> m_volumeMapper;
    vtkSmartPointer<vtkVolume> m_volume;

    //Reslice Volume
    vtkSmartPointer<vtkImageSliceMapper> m_resliceMapper[NUMSLICE];
    vtkSmartPointer<vtkImageSlice> m_resliceActor[NUMSLICE];


    ///Ground-truth volume
    vtkSmartPointer<vtkImageData> m_gimageData;
    vtkSmartPointer<vtkSmartVolumeMapper> m_gvolumeMapper;
    vtkSmartPointer<vtkVolume> m_gvolume;

    ///Ground-truth reslice volume
    vtkSmartPointer<vtkImageSliceMapper> m_gresliceMapper[NUMSLICE];
    vtkSmartPointer<vtkImageSlice> m_gresliceActor[NUMSLICE];

};

#endif //E_VOLUMEMANAGER_H