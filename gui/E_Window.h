#include <QMainWindow>
#include <QVTKWidget.h>


class E_Window : public QMainWindow{
    
    Q_OBJECT
    
    public:
    E_Window(QWidget *parent = 0);
    ~E_Window();

    protected:
    QVTKWidget* m_renderingWidget;

    public Q_SLOTS:
    void ImportVolume();
    
};