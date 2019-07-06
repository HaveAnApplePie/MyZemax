#include"Ray_Point.h"
Ray FirstParaxialLight(struct Ray*Ray0)							//第一近轴光线计算
{
	#define PI 3.1415927

	struct Ray RayFPL;											//定义第一近轴光线
	RayFPL = Ray0;

	if (RayFPL.IsInfinite = true)								//计算第一近轴光线无穷远物时情况
	{
		RayFPL.Ln = Ray0->L0;
		RayFPL.Un = 0;
	}
	else {														//计算第一近轴光线非无穷远物时情况
		RayFPL.Ln = Ray0->L0;
		RayFPL.Un = sin(PI / (180 / Ray0->U0_D0));
	}

	return RayFPL;
}