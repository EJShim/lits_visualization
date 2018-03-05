#include "E_Window.h"
#include "E_Manager.h"
#include <iostream>

#include <QToolBar>

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
    QAction* import_action = new QAction(QString("Import Volume"));
    toolbar->addAction(import_action);
    connect(import_action, SIGNAL(triggered()), this, SLOT(ImportVolume()));

}

E_Window::~E_Window(){
    std::cout << "Window Destroyed" << std::endl;
}

void E_Window::ImportVolume(){
    std::cout << "Volume Import Triggered" << std::endl;

    E_Manager::Mgr()->TestFunction();
}