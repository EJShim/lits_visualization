#include <QMainWindow>
#include <QToolBar>
#include <QVTKWidget.h>
#include "E_Manager.h"


class E_Window : public QMainWindow{
    
    Q_OBJECT
    
    public:
    E_Window(QWidget *parent = 0);
    ~E_Window();

    protected:
    QToolBar* InitToolbar();
    QWidget* InitCentralWidget();

    protected:
    QVTKWidget* m_renderingWidget[E_Manager::NUM_VIEW];

    public Q_SLOTS:
    void ImportVolume();
    void RunSegmentation();
    ///temporary
    void ImportGT();
    
};