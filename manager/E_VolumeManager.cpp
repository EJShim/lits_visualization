#include "E_Manager.h"
#include "E_VolumeManager.h"

#include <itkImage.h>
#include <itkImageFileReader.h>
#include <itkNiftiImageIO.h>
#include <itkImageToVTKImageFilter.h>



E_VolumeManager::E_VolumeManager(){
    this->m_imageData = NULL;
    this->m_volumeMapper = NULL;
    this->m_volume = NULL;

    this->m_colorFunc = NULL;
    this->m_opacFunc = NULL;
    this->m_volumeProperty = NULL;
    this->m_imageProperty = NULL;

    for(int i=0 ; i<NUMSLICE ; i++){
        this->m_resliceMapper[i] = NULL;
        this->m_resliceActor[i] = NULL;
    }
    
}

E_VolumeManager::~E_VolumeManager(){

}


void E_VolumeManager::ImportVolume(std::string path){    

    itk::ImageIOBase::Pointer imageIO = itk::ImageIOFactory::CreateImageIO(path.c_str(), itk::ImageIOFactory::ReadMode);

    imageIO->SetFileName(path);
    // imageIO->ReadImageInformation();
    // std::cout << "numDimensions : " << imageIO->GetNumberOfDimensions() << std::endl;
    // std::cout << "component type : " << imageIO->GetComponentTypeAsString(imageIO->GetComponentType()) << std::endl;
    // std::cout << "pixel type : " << imageIO->GetPixelTypeAsString(imageIO->GetPixelType()) << std::endl;


    // Make ITK Image Data
    typedef itk::Image<short, 3> ImageType;
    typedef itk::ImageFileReader<ImageType> VolumeReader;
    VolumeReader::Pointer reader = VolumeReader::New();
    reader->SetFileName(imageIO->GetFileName());
    reader->Update();
    ImageType::Pointer itkImageData = reader->GetOutput();
    

    // Convert to vtkimagedata
    typedef itk::ImageToVTKImageFilter<ImageType> itkVtkConverter;
    itkVtkConverter::Pointer conv = itkVtkConverter::New();
    conv->SetInput(itkImageData);
    conv->Update();

    //orientation
    // ImageType::DirectionType d = itkImageData->GetDirection();
    // vtkSmartPointer<vtkMatrix4x4> mat = vtkSmartPointer<vtkMatrix4x4>::New();
    // for(int i=0 ; i<3 ; i++){
    //     for(int k=0 ; k<3 ; k++){
    //         mat->SetElement(i, k, d(i,k));
    //     }
    // }
    // mat->Print(std::cout);

    if(m_imageData == NULL)
        m_imageData = vtkSmartPointer<vtkImageData>::New();
    
    m_imageData->DeepCopy( conv->GetOutput());    
    double scalarRange[2];
    m_imageData->GetScalarRange(scalarRange);
    std::cout << scalarRange[0] << ',' << scalarRange[1] << std::endl;

    
    // Initialize || Update Volume Property
    if(m_colorFunc == NULL)
        m_colorFunc = vtkSmartPointer<vtkColorTransferFunction>::New();
    m_colorFunc->AddRGBPoint(scalarRange[0], 0.0, 0.0, 0.0);
    m_colorFunc->AddRGBPoint(scalarRange[1], 1.0, 1.0, 1.0);

    if(m_opacFunc == NULL)
        m_opacFunc = vtkSmartPointer<vtkPiecewiseFunction>::New();
    m_opacFunc->AddPoint(scalarRange[0], 0.0);
    m_opacFunc->AddPoint(scalarRange[1], 1.0);

    if(m_volumeProperty == NULL){
        m_volumeProperty = vtkSmartPointer<vtkVolumeProperty>::New();
        m_volumeProperty->SetColor(m_colorFunc);
        m_volumeProperty->SetScalarOpacity(m_opacFunc);
        m_volumeProperty->ShadeOff();
        m_volumeProperty->SetInterpolationTypeToLinear();
    }

    if(m_imageProperty == NULL){
        m_imageProperty = vtkSmartPointer<vtkImageProperty>::New();
        m_imageProperty->SetInterpolationTypeToLinear();        
    }
    m_imageProperty->SetColorLevel( (scalarRange[1]+scalarRange[0])/2.0 );
    m_imageProperty->SetColorWindow(scalarRange[1] - scalarRange[0] - 1.0);
    
    if(m_volumeMapper == NULL){
        m_volumeMapper = vtkSmartPointer<vtkSmartVolumeMapper>::New();
        m_volumeMapper->SetInputData(m_imageData);
        m_volumeMapper->SetBlendModeToMaximumIntensity();
    }
    
    if(m_volume == NULL){
        m_volume = vtkSmartPointer<vtkVolume>::New();
        m_volume->SetMapper(m_volumeMapper);
        m_volume->SetProperty(m_volumeProperty);

        //Add To Renderer
        E_Manager::Mgr()->GetRenderer(E_Manager::VIEW_MAIN)->AddViewProp(m_volume);
    }


    //Initialize Reslice
    if(m_resliceMapper[0] == NULL){
        for(int i=0 ; i<NUMSLICE ; i++){
            m_resliceMapper[i] = vtkSmartPointer<vtkImageSliceMapper>::New();
            m_resliceMapper[i]->SetOrientation(i);
            m_resliceMapper[i]->SetInputData(m_imageData);

            m_resliceActor[i] = vtkSmartPointer<vtkImageSlice>::New();
            m_resliceActor[i]->SetMapper(m_resliceMapper[i]);
            m_resliceActor[i]->SetProperty(m_imageProperty);

            E_Manager::Mgr()->GetRenderer(i+1)->AddViewProp(m_resliceActor[i]);
        }
    }
    
    E_Manager::Mgr()->RedrawAll();
}