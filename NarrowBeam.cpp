#include"Ray_Point.h"
#include<math.h>

Ray NarrowBeam(struct Ray*Ray0,double Radius[],double Re_Index[])
{
	double PA, Io, Ie, x, To, Te;
	struct Ray NarrowBeam;
	NarrowBeam = *Ray0;
	#define PI 3.1415927;

	PA = Ray0->L0 * sin(Ray0->U0_D0 * PI / 180) / cos(0.5*(Ray->U0_D0 - Io)*PI / 180);
	x = PA * PA / Radius[0];
	So = (Ray0->L0 - x) / cos(Ray0->U0_D0);
	To = (Ray0->L0 - x) / cos(Ray0->U0_D0);
	NarrowBeam.T = Re_Index[1] * cos(Ie * PI / 180)*cos(Ie * PI / 180) / (((Re_Index[1] * cos(PI*Ie / 180) - Re_Index[0] * cos(PI * Io / 180)) / Radius[0]) + Re_Index[0] * cos(Io * PI / 180)*cos(Io * PI / 180) / To);
	NarrowBeam.S = Re_Index[1] / (((Re_Index[1] * cos(PI * Ie / 180) - Re_Index[0] * cos(PI * Io / 180)) / Radius[0]) + Re_Index[0] / So);

	return NarrowBeam;
}