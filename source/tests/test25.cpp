#include "test25.h"

namespace Test25
{
    void Test::Run()
    {
        try
        {
            Math::quat q1(1, 2, 3, 4);
            Math::quat q2(3, -2, 4, -5);
            Math::quat r1 = q1 * q2;    // Quaternion((15.0, -27.0, 15.0, 21.0))
            Math::quat r2 = q2 * q1;    // Quaternion((15.0, 35.0, 11.0, -7.0))
            Math::quat r3 = q1.Conjugated(); // Quaternion((1.0, -2.0, -3.0, -4.0))
            Math::quat r4 = q1.Inversed();  //  Quaternion((0.03333333507180214, -0.06666667014360428, -0.10000000894069672, -0.13333334028720856))
            Math::mat3 m = q1.ToMatrix3x3();    //Matrix(((-49.0, 4.0, 22.0), (20.0, -39.0, 20.0), (10.0, 28.0, -25.0)))


            if (!m.IsEqual({-49.0, 20.0, 10.0, 4.0, -39.0, 28.0, 22.0, 20.0, -25.0}))
                throw std::exception();
            if (r1 != Math::quat(15.0, -27.0, 15.0, 21.0))
                throw std::exception();
            if (r2 != Math::quat(15.0, 35.0, 11.0, -7.0))
                throw std::exception();
            if (r3 != Math::quat(1.0, -2.0, -3.0, -4.0))
                throw std::exception();
            if (!r4.IsEqual({0.03333333507180214, -0.06666667014360428, -0.10000000894069672, -0.13333334028720856}))
                throw std::exception();            

            m_result =  true;
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

