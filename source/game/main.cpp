#include <QApplication>
#include <QMessageBox>
#include <QThread>

#include <windows.h>
#include <iostream>
#include "data_domain/humans/module.h"
#include "simulator/module.h"
#include "forms/simulatorwindow.h"

//class A
//{
//public:
//    int f()
//    {
//        std::cout << "A::f" << std::endl;
//    }
//};

//int b()
//{}

//decltype(b()) k()
//{
//    return 0;
//}

//struct SS
//{
//    int a;
//    float b;

//    void Print()
//    {
//        std::cout << "a = " << a << " b = " << b << std::endl;
//    }
//};

//class AA
//{
//public:

//    AA()
//        : P(*this, &AA::GetP, &AA::SetP)
//        , Name(*this, &AA::GetName, &AA::SetName)
//        , S(*this, &AA::GetSS, &AA::SetSS)
//        , m_value(0)
//    {}

//    Property<int, AA> P;
//    Property<std::string, AA> Name;
//    Property<SS, AA> S;

//private:

//    void SetP(const int& value)
//    {
//        m_value = value;
//    }

//    const int& GetP() const
//    {
//        if (m_value == 0)
//        {
//            std::cout << "P is not initialized" << std::endl;
//        }
//        return m_value;
//    }

//    void SetName(const std::string& name)
//    {
//        m_name = name;
//    }

//    const std::string& GetName() const
//    {
//        return m_name;
//    }

//    void SetSS(const SS& s)
//    {
//        m_s = s;
//    }

//    const SS& GetSS() const
//    {
//        return m_s;
//    }

//    int m_value;
//    std::string m_name;
//    SS m_s;

//    template<typename A, typename U>
//    friend class Property;
//};


int main(int argc, char *argv[])
{    
    QApplication a(argc, argv);

    SimulatorWindow wnd;
    wnd.show();
    a.exec();

    return 0;
}
