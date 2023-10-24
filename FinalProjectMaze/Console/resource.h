#ifndef __RESOURCE__
#define __RESOURCE__
#include <string>
namespace app
{
	namespace console
	{
		enum class key
		{
			BACKSPACE = 8,
			TAB = 9,
			ENTER = 13,
			ESCAPE = 27,
			SPACE = 32,
			_0 = 48, _1, _2, _3, _4, _5, _6, _7, _8, _9,
			A = 65, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
			a = 97, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z,
		};
		enum class color : unsigned int
		{
			NAVY = 1,
			GREEN,
			BLUE,
			FIREBRICK,
			VIOLET,
			GOLD,
			WHITE,
			GRAY,
			BLUE_V2,
			GREEN_V2,
			CYAN,
			RED,
			VIOLET_V2,
			YELLOW,
			WHITE_V2
		};
		enum class diag_direction
		{
			NW,
			NE,
			SE,
			SW
		};
	}
}
#endif