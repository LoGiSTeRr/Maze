#include "console_manip.h"

namespace app
{
	namespace console
	{
		console& endl(console& con)
		{
			return con << '\n';
		}
	}
}