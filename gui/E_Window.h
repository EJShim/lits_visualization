#include <QMainWindow.h>

class E_Window : public QMainWindow{
    
    Q_OBJECT
    
    public:
    E_Window(QWidget *parent = 0);
    ~E_Window();

    public Q_SLOTS:
    void ImportVolume();



    
};