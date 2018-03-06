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
E_VolumeManager* E_Manager::m_volumeManager;

E_Manager* E_Manager::Mgr(){
    if(m_instance == NULL){
        m_instance = new E_Manager();
        atexit(Destroy);
    }
    return m_instance;
}

E_VolumeManager* E_Manager::VolumeMgr(){
    if(m_volumeManager == NULL){
        m_volumeManager = new E_VolumeManager();
        atexit(DestroyVolumeManager);
    }

    return m_volumeManager;
}

void E_Manager::Initialize(){
    
}

void E_Manager::ClearMemory(){

}


void E_Manager::SetVTKWidget(QVTKWidget* widget, int idx){
    this->m_renderer[idx] = vtkSmartPointer<vtkRenderer>::New();
    widget->GetRenderWindow()->AddRenderer(this->m_renderer[idx]);
}

void E_Manager::Redraw(int idx){
    this->m_renderer[idx]->GetRenderWindow()->Render();
    this->m_renderer[idx]->ResetCamera();
}

void E_Manager::RedrawAll(){
    for(int i=0 ; i<NUM_VIEW ; i++){
        this->Redraw(i);
    }
}