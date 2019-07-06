#include"Ray_Point.h"
Ray SencondParaxialLight(struct Ray*Ray0)								//第二近轴光线计算
{
	#define PI 3.1415927

	struct Ray RaySPL;											//定义第二近轴光线
	RaySPL = Ray0;

	RaySPL.Ln = 0;												//计算第二近轴光线（无穷或非无穷远物时情况相同）
	RaySPL.Un = sin(PI / (180 / Ray0->Y0_W0));

	return RaySPL;
}