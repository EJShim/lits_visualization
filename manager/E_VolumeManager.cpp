#include "E_Manager.h"
#include "E_VolumeManager.h"

#include <vtkLookupTable.h>

#include <itkNiftiImageIO.h>



E_VolumeManager::E_VolumeManager(){        
    this->m_volume = NULL;

    this->m_gimageData = NULL;
    this->m_gvolumeMapper = NULL;
    this->m_gvolume = NULL;


    for(int i=0 ; i<NUMSLICE ; i++){        

        this->m_gresliceMapper[i] = NULL;
        this->m_gresliceActor[i] = NULL;
    }
    
}

E_VolumeManager::~E_VolumeManager(){

}


void E_VolumeManager::ImportVolume(std::string path){    


    // Make ITK Image Data    
    VolumeReader::Pointer reader = VolumeReader::New();
    reader->SetFileName(path);
    reader->Update();
    ImageType::Pointer itkImageData = reader->GetOutput();
    

    // Convert to vtkimagedata
    typedef itk::ImageToVTKImageFilter<ImageType> itkVtkConverter;
    itkVtkConverter::Pointer conv = itkVtkConverter::New();
    conv->SetInput(itkImageData);
    conv->Update();

    //Make Volume
    if(m_volume == NULL){
        m_volume = vtkSmartPointer<E_Volume>::New();
    }
    m_volume->SetImageData(conv->GetOutput());


    E_Manager::Mgr()->GetRenderer(E_Manager::VIEW_MAIN)->AddViewProp(m_volume);

    
    for(int i=0 ; i<NUMSLICE ; i++){
        vtkSmartPointer<vtkImageSlice> slice = m_volume->GetImageSlice(i);
        E_Manager::Mgr()->GetRenderer(i+1)->AddViewProp(slice);
    }

    E_Manager::Mgr()->RedrawAll(true);    
}

void E_VolumeManager::ImportGroundTruth(std::string path){
    if(m_volume == NULL) return;

    // Make ITK Image Data    
    VolumeReader::Pointer reader = VolumeReader::New();
    reader->SetFileName(path);
    reader->Update();
    ImageType::Pointer itkImageData = reader->GetOutput();
    

    // Convert to vtkimagedata    
    itkVtkConverter::Pointer conv = itkVtkConverter::New();
    conv->SetInput(itkImageData);
    conv->Update();
    

    m_volume->SetGroundTruth(conv->GetOutput());
    E_Manager::Mgr()->GetRenderer(0)->AddViewProp(m_volume->GetGroundTruthVolume());

    for(int i=0 ; i<3 ; i++){
        vtkSmartPointer<vtkImageSlice> slice = m_volume->GetGroundTruthImageSlice(i);

        E_Manager::Mgr()->GetRenderer(0)->AddViewProp(slice);
        E_Manager::Mgr()->GetRenderer(i+1)->AddViewProp(slice);
    }

    E_Manager::Mgr()->RedrawAll(true);    
}

void E_VolumeManager::ForwardSlice(int idx){
    if(m_volume == NULL) return;

    m_volume->ForwardSlice(idx);

    E_Manager::Mgr()->Redraw(0);
    E_Manager::Mgr()->Redraw(idx+1);
}

void E_VolumeManager::BackwardSlice(int idx){
    if(m_volume == NULL) return;

    m_volume->BackwardSlice(idx);
    
    E_Manager::Mgr()->Redraw(0);
    E_Manager::Mgr()->Redraw(idx+1);
}