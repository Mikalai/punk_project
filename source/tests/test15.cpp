#include "test15.h"
#include <type_traits>

namespace Test15
{
	class TestApp : public Punk::Application
	{
	public:


	};

	void Test::Run()
	{
        TestApp app;
		try
		{
            Punk::Config cfg;
            cfg.gpu_config.disable_3d_graphics = true;
            app.Init(cfg);
            app.Run();
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
