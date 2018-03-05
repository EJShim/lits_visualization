#include "E_Window.h"
#include "E_Manager.h"
#include <iostream>
#include <QVBoxLayout>
#include <QAction>

E_Window::E_Window(QWidget* parent):QMainWindow(parent){
    //Show in maximum size
    this->showMaximized();

    // Initialize toolbar
    this->addToolBar(Qt::TopToolBarArea, this->InitToolbar());
    
    //Initialize Central WIdget    
    this->setCentralWidget(this->InitCentralWidget());
    

    //Initialize Test Function
    E_Manager::Mgr()->TestFunction();

}

E_Window::~E_Window(){
    std::cout << "Window Destroyed" << std::endl;
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

    //Run Segmentation
    QAction* segmentation_action = new QAction(QIcon(":/images/edit-tools.png") ,QString("Run Segmentation"), this);
    toolbar->addAction(segmentation_action);
    connect(segmentation_action, SIGNAL(triggered()), this, SLOT(RunSegmentation()));

    return toolbar;
}

QWidget* E_Window::InitCentralWidget(){
    //Initialize VTK Widget
    this->m_renderingWidget = new QVTKWidget;
    E_Manager::Mgr()->SetVTKWidget(this->m_renderingWidget);
    
    QWidget* centralWidget = new QWidget();
    QVBoxLayout* centralLayout = new QVBoxLayout();
    centralWidget->setLayout(centralLayout);
    centralLayout->addWidget(this->m_renderingWidget);



    return centralWidget;
}

void E_Window::ImportVolume(){
    std::cout << "Volume Import Triggered" << std::endl;    
}

void E_Window::RunSegmentation(){
    std::cout << "Run Segmentation" << std::endl;
}