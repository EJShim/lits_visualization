#include "E_Window.h"
#include "E_SegmentationThread.h"

#include <iostream>
#include <QGridLayout>
#include <QAction>
#include <QFileDialog>
#include <QCheckBox>

E_Window::E_Window(QWidget* parent):QMainWindow(parent){
    //Show in maximum size
    this->showMaximized();

    // Initialize toolbar
    this->addToolBar(Qt::TopToolBarArea, this->InitToolbar());
    
    //Initialize Central WIdget    
    this->setCentralWidget(this->InitCentralWidget());    

}

E_Window::~E_Window(){
        
}

QToolBar* E_Window::InitToolbar(){
    //Initialize Toolbar
    QToolBar* toolbar = new QToolBar();
    toolbar->setIconSize(QSize(50, 50));
    toolbar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    toolbar->setMovable(false);    

    //Import Volume    
    QAction* import_action = new QAction(QIcon(":/images/pantone-2.png") ,QString("Import Volume"), this);
    toolbar->addAction(import_action);
    connect(import_action, SIGNAL(triggered()), this, SLOT(ImportVolume()));    
    //Import Ground Truth
    QAction* gt_import_action = new QAction(QIcon(":/images/document.png"), QString("Import Ground Truth(temp)"), this);
    toolbar->addAction(gt_import_action);
    connect(gt_import_action, SIGNAL(triggered()), this, SLOT(ImportGT()));


    //Run Segmentation
    QAction* segmentation_action = new QAction(QIcon(":/images/edit-tools.png") ,QString("Run Segmentation"), this);
    toolbar->addAction(segmentation_action);
    connect(segmentation_action, SIGNAL(triggered()), this, SLOT(RunSegmentation()));


    
    toolbar->addWidget(Init3DSliceGroup());

    

    return toolbar;
}

QGroupBox* E_Window::Init3DSliceGroup(){
    QGroupBox* groupbox = new QGroupBox(tr("3d slice"));
    groupbox->setFlat(true);

    QCheckBox* checkbox_axl = new QCheckBox(tr("Axial"));
    QCheckBox* checkbox_cor = new QCheckBox(tr("Coronal"));
    QCheckBox* checkbox_sag = new QCheckBox(tr("Sagittal"));

    checkbox_axl->setChecked(true);
    checkbox_cor->setChecked(true);
    checkbox_sag->setChecked(true);

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(checkbox_axl);
    vbox->addWidget(checkbox_cor);
    vbox->addWidget(checkbox_sag);
    vbox->addStretch(1);
    groupbox->setLayout(vbox);


    return groupbox;
}

QWidget* E_Window::InitCentralWidget(){
    //Initialize VTK Widget
    for(int i=0 ; i<E_Manager::NUM_VIEW ; i++){
        this->m_renderingWidget[i] = new QVTKWidget;
        E_Manager::Mgr()->SetVTKWidget(this->m_renderingWidget[i],i);
    }
    
    
    // Initialize Central Widgets
    QWidget* centralWidget = new QWidget();
    QGridLayout* layout = new QGridLayout();
    centralWidget->setLayout(layout);


    //Add To Central Widget(Grid Layout)
    layout->addWidget(this->m_renderingWidget[E_Manager::VIEW_MAIN], 0, 1);
    layout->addWidget(this->m_renderingWidget[E_Manager::VIEW_AXL], 0, 2);
    layout->addWidget(this->m_renderingWidget[E_Manager::VIEW_COR], 1, 1);
    layout->addWidget(this->m_renderingWidget[E_Manager::VIEW_SAG], 1, 2);


    return centralWidget;
}



////////////////////////////////////////////////////////////////////Action SLOTS////////////////////////////////////////////////////////
void E_Window::ImportVolume(){    
    QString fileName = QFileDialog::getOpenFileName(this, ("Open File"),"~/..",
                                                ("volumes (*.dcm *.nii"));

    // If file is not selected
    if(fileName == ""){
        return;
    }

    // Import Volume                                        
    E_Manager::VolumeMgr()->ImportVolume(fileName.toStdString());
}

void E_Window::RunSegmentation(){
    E_SegmentationThread *segThread = new E_SegmentationThread();
    connect(segThread, &E_SegmentationThread::onCalculated, this, &E_Window::OnSegmentationCalculated);

    segThread->start();
}

void E_Window::OnSegmentationCalculated(int i){
    std::cout << i << std::endl;
    
}



void E_Window::ImportGT(){
    QString fileName = QFileDialog::getOpenFileName(this, ("Open File"),"~/..",
                                                ("volumes (*.dcm *.nii"));

    if(fileName == "") return;

    E_Manager::VolumeMgr()->ImportGroundTruth(fileName.toStdString());


}