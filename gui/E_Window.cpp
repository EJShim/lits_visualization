#include "E_Window.h"
#include "E_Manager.h"
#include <iostream>
#include <QVBoxLayout>
#include <QToolBar>
#include <QAction>

E_Window::E_Window(QWidget* parent):QMainWindow(parent){
    //Show in maximum size
    this->showMaximized();

    //Initialize Toolbar
    QToolBar* toolbar = new QToolBar();
    toolbar->setIconSize(QSize(50, 50));
    toolbar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    toolbar->setMovable(false);
    this->addToolBar(Qt::TopToolBarArea, toolbar);

    //Import Volume
    QIcon icon = QIcon(":/images/pantone-2.png");
    QAction* import_action = new QAction(QIcon(":/images/pantone-2.png") ,QString("Import Volume"), this);
    toolbar->addAction(import_action);
    connect(import_action, SIGNAL(triggered()), this, SLOT(ImportVolume()));


    //Initialize VTK Widget
    this->m_renderingWidget = new QVTKWidget;
    E_Manager::Mgr()->SetVTKWidget(this->m_renderingWidget);

    QWidget* centralWidget = new QWidget();
    QVBoxLayout* centralLayout = new QVBoxLayout();
    centralWidget->setLayout(centralLayout);
    centralLayout->addWidget(this->m_renderingWidget);
    this->setCentralWidget(centralWidget);
    

    //Initialize Test Function
    E_Manager::Mgr()->TestFunction();

}

E_Window::~E_Window(){
    std::cout << "Window Destroyed" << std::endl;
}

void E_Window::ImportVolume(){
    std::cout << "Volume Import Triggered" << std::endl;    
}