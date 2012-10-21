#include <algorithm>
#include "program_impl.h"
#include "context_impl.h"
#include "device_impl.h"
#include "command_queue_impl.h"

namespace OpenCL
{
	Program::Program() : m_impl(new Program::ProgramImpl) {}
	Program::Program(const Program& value) : m_impl(new Program::ProgramImpl(*value.m_impl)) {}
	
	Program& Program::operator = (const Program& value)
	{
		Program temp(value);
		std::swap(temp.m_impl, m_impl);
		return *this;
	}

	bool Program::Init(Context& context, Device& device, CommandQueue& queue)
	{
		return m_impl->Init(context.m_impl->m_context, device.m_impl->m_device, queue.m_impl->m_queue);
	}

	bool Program::CreateFromFile(const System::string& path)
	{
		return m_impl->CreateFromFile(path);		
	}

	bool Program::GetKernel(const System::string& name, Kernel& value)
	{
		return m_impl->GetKernel(name, value);
	}

	Program::~Program()
	{
		m_impl.reset(0);
	}
}