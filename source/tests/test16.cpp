#include "test16.h"
#include <type_traits>

namespace Test16
{
    class TestApp : public Punk::Application
    {
    public:


    };

    void Test::Run()
    {
        m_result = true;
        try
        {
            System::string string("Hello this world");
            std::wcout << string << std::endl;

            System::string s2(L"   bad Hello bad world bad       ");
            std::wcout << s2 << std::endl;

            s2 = s2.Replace("bad", "AmazIng");
            std::wcout << s2 << std::endl;
            s2 = s2.Trim(" ");
            std::wcout << s2 << std::endl;
            if (s2 != s2)
                throw;

            std::wcout << s2.ToLower() << std::endl;

            System::string s3(L"Vitaju Šanoŭnaje spadarstva!");
            std::wcout << s3 << std::endl;
            std::wcout << s3.ToLower() << std::endl;

            std::wcout << System::string::Convert(24) << std::endl;
            std::wcout << System::string::Convert(true) << std::endl;
            std::wcout << System::string::Convert(L'Q') << std::endl;
            long double ld = 1.45;
            std::wcout << System::string::Convert(ld) << std::endl;
            std::wcout << System::string::Convert((double)ld) << std::endl;
            std::wcout << System::string::Convert((float)ld) << std::endl;
            std::wcout << System::string::Convert((uint16_t)0xeaff) << std::endl;

            std::wcout << s2 + s3 << std::endl;

            std::wcout << "Split: " << s2 << std::endl;
            auto v = s2.Split(" ");
            for (auto e : v)
            {
                std::wcout << e << std::endl;
            }

            std::wcout << "s2 size: " << s2.Size() << std::endl;
            std::wcout << "s2 length: " << s2.Length() << std::endl;

            {
                System::string s("The value is {0} and {1}");

                int8_t p = 13;
                std::wcout << s.arg(p).arg(p/2) << std::endl;
            }

            {
                System::string s = L"Hełło world šæźžćđš¶ŧŋ";
                std::ofstream stream("test.string");
                s.Save(stream);
            }

            {
                std::ifstream stream("test.string");
                System::string s;
                s.Load(stream);
                std::wcout << s << std::endl;
            }
        }
        catch(System::PunkException& e)
        {
            out_error() << e.ToString() << std::endl;
            m_result = false;
        }
        catch(...)
        {
            m_result = false;
        }
    }

    bool Test::Succeed()
    {
        return m_result;
    }

}
