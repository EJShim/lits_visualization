#include <QVTKWidget.h>
#include <vtkSmartPointer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>

class E_Manager{
    public:
    enum {VIEW_MAIN, VIEW_AXL, VIEW_COR, VIEW_SAG};
    static const int NUM_VIEW = 4;

    public:
    E_Manager();
    ~E_Manager();

    private:
    static E_Manager* m_instance;
    static void Destroy(){delete m_instance;}

    public:
    static E_Manager* Mgr();

    public:
    void Initialize();
    void ClearMemory();
    void TestFunction();

    //Initialize VTK Widgets
    void SetVTKWidget(QVTKWidget* widget, int idx);

    void Redraw(int idx);
    void RedrawAll();


    protected:
    vtkSmartPointer<vtkRenderer> m_renderer[NUM_VIEW];
    
};