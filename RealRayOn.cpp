#include"Ray_Point.h"
#include<math.h>
Ray RealRayOn(double Kw, double Kn, struct Ray*Ray0)			//计算轴上点实际光
{
	#define PI 3.1415927

	struct Ray RayRealOn;											
	RayRealOn = *Ray0;

	if (RayRealOn.IsInfinite == true)								//判断是否为无穷远物
	{
		RayRealOn.Ln = Ray0->L0;
		RayRealOn.Un = 0;
	}
	else {
		RayRealOn.Ln = Ray0->L0;
		RayRealOn.Un = asin(Kn*sin(Ray0->U0_D0*PI/ 180));
	}

	return RayRealOn;
}