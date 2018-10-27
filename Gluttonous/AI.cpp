#include "stdafx.h"
#include "AI.h"


AI::AI()
{
}


AI::~AI()
{
}

BYTE AI::foodPos(QPoint H, QPoint F)
{
	BYTE d = 0x00;

	if (H.x() < F.x() && H.y() == F.y())
	{
		d |= 0x01;
	}
	else if (H.x() < F.x() && H.y() < F.y())
	{
		d |= 0x02;
	}
	else if (H.x() == F.x() && H.y() < F.y())
	{
		d |= 0x04;
	}
	else if (H.x() > F.x() && H.y() < F.y())
	{
		d |= 0x08;
	}
	else if (H.x() > F.x() && H.y() == F.y())
	{
		d |= 0x10;
	}
	else if (H.x() > F.x() && H.y() > F.y())
	{
		d |= 0x20;
	}
	else if (H.x() == F.x() && H.y() > F.y())
	{
		d |= 0x40;
	}
	else if (H.x() < F.x() && H.y() > F.y())
	{
		d |= 0x80;
	}
	else
	{
		d = 0x00;
	}
	return d;
}
