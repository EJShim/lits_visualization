#include "E_Manager.h"
#include <iostream>
#include <vtkCylinderSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkCamera.h>



E_Manager::E_Manager(){
    this->Initialize();
}

E_Manager::~E_Manager(){
    this->ClearMemory();
}

E_Manager* E_Manager::m_instance;

E_Manager* E_Manager::Mgr(){
    if(m_instance == NULL){
        m_instance = new E_Manager();
        atexit(Destroy);
    }
    return m_instance;
}

void E_Manager::Initialize(){
    
}

void E_Manager::ClearMemory(){

}

void E_Manager::TestFunction(){    
    vtkSmartPointer<vtkCylinderSource> cylinder = vtkSmartPointer<vtkCylinderSource>::New();
    cylinder->SetResolution(8);
    
    vtkSmartPointer<vtkPolyDataMapper> cylinderMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    cylinderMapper->SetInputConnection(cylinder->GetOutputPort());

    vtkSmartPointer<vtkActor> cylinderActor = vtkSmartPointer<vtkActor>::New();
    cylinderActor->SetMapper(cylinderMapper);
    cylinderActor->GetProperty()->SetColor(1.0000, 0.3882, 0.2784);
    cylinderActor->RotateX(30.0);
    cylinderActor->RotateY(-45.0);

       
    this->m_renderer->AddActor(cylinderActor);

    this->Redraw();
}

void E_Manager::SetVTKWidget(QVTKWidget* widget){
    this->m_renderer = vtkSmartPointer<vtkRenderer>::New();
    widget->GetRenderWindow()->AddRenderer(this->m_renderer);
}

void E_Manager::Redraw(){
    this->m_renderer->GetRenderWindow()->Render();
}