#include"Ray_Point.h"
#include<math.h>
Ray ParaxialLight(struct Ray*Ray0)								//第一近轴光线计算
{
	struct Ray RayFPL;											//定义第一近轴光线
	struct Ray RaySPL;											//定义第二近轴光线

	RayFPL = RaySPL = Ray0;

	if (RayFPL->IsInfinite = true)								//计算第一近轴光线无穷远物时情况
	{
		RayFPL->Ln = Ray0->L0;
		RayFPL->Un = 0;
	}
	else {														//计算第一近轴光线非无穷远物时情况
		RayFPL->Ln = Ray0->L0;
		RayFPL->Un = Math.Sin(Math.PI / (180 / Ray0->U0_D0));
	}
		
	RaySPL->Ln = 0;												//计算第二近轴光线（无穷或非无穷远物时情况相同）
	RaySPL->Un = Math.Sin(Math.PI / (180 / Ray0->Y0_W0));
}