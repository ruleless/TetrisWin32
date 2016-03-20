#ifndef __COLOUR_H__
#define __COLOUR_H__

namespace tetris
{
	struct SRgb 
	{
		int r, g, b;

		SRgb() : r(0), g(0), b(0)
		{
		}

		SRgb(int rr, int gg, int bb) : r(rr), g(gg), b(bb)
		{
		}

		SRgb(const SRgb &c) : r(c.r), g(c.g), b(c.b)
		{
		}

		static const SRgb RED;
		static const SRgb GREEN;
		static const SRgb BLUE;
	};
}

#endif // __COLOUR_H__