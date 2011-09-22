#include <stdio.h>
#include "../punk_engine/utility/utility.h"

int main()
{
	Utility::RawScene mdl;

	try
	{
		mdl.OpenFile(System::string("d:\\project\\punk_project\\punk_engine\\blender\\simple_anim2.pmd"));
	}
	catch (Utility::UtilityError& err)
	{
		wprintf(L"%s\n", err.w_what().Data());
	}

	return 0;
}