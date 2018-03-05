#include "E_Manager.h"
#include <iostream>


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
    std::cout << "Initailize Manager"<<std::endl;
}

void E_Manager::ClearMemory(){

}

void E_Manager::TestFunction(){
    std::cout << "Test Function Called" << std::endl;
}