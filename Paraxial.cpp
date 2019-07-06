#include"Ray_Point.h"
#include<math.h>

#define PI 3.1415927

Ray FirstParaxialLight(struct Ray*Ray0)							//第一近轴光线计算
{


	struct Ray RayFPL;											//定义第一近轴光线
	RayFPL = *Ray0;

	if (RayFPL.IsInfinite == true)								//计算第一近轴光线无穷远物时情况
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

Ray SencondParaxialLight(struct Ray*Ray0)								//第二近轴光线计算
{

	struct Ray RaySPL;											//定义第二近轴光线
	RaySPL = *Ray0;

	RaySPL.Ln = 0;												//计算第二近轴光线（无穷或非无穷远物时情况相同）
	RaySPL.Un = sin(PI / (180 / Ray0->Y0_W0));

	return RaySPL;
}

Ray* Paraxial_single_surface(struct Ray *ray_in,double Radius[],double Distance[],double Re_Index[]) {
//近轴光的单个面计算
	Ray ray_out;
	int k;
	double r,d,n1,n2;
	double u1, i1, l1;
	double u2, i2, l2;
//===========初始化============
	l1 = ray_in->Ln;
	u1 = ray_in->Un;
	
	k = ray_in->now_surface_number + 1; //要计算的面的序号
	n1 = Re_Index[k];					//物方折射率
	n2 = Re_Index[k + 1];				//像方折射率
	r  = Radius[k];						//半径
	if (k < ray_in->all_surface_number)	//前k-1个面
		d = Distance[k];		
	else								//最后一个面d=0
		d = 0;

	ray_out = *ray_in;
//===========公式计算===========
	i1 = (l1 - r) / r * u1;
	i2 = n1 / n2 * i1;
	u2 = i1 + u1 - i2;
	l2 = r + r * i2 / u2;
//===========过渡公式===========
	ray_out.Ln = l2 - d;
	ray_out.Un = u2;

	*ray_in = ray_out;

	return	ray_in;
}



void Paraxial_calculation(struct Ray *ray0, double Radius[], double Distance[], double Re_Index[]) {
	int i,j,k,n;
	Ray RayFPL,RaySPL,*Raycal;

//=============初始化==========
	n = ray0->all_surface_number;
	RayFPL = FirstParaxialLight(ray0);
	RaySPL = SencondParaxialLight(ray0);

//=============第一近轴光========
	Raycal = &RayFPL;
	for (i = 0;i <= ray0->all_surface_number;i++) {
		Raycal = Paraxial_single_surface(Raycal, Radius, Distance, Re_Index);
	}

//============第二近轴光=========
	Raycal = &RaySPL;
	for (i = 0;i <= ray0->all_surface_number;i++) {
		Raycal = Paraxial_single_surface(Raycal, Radius, Distance, Re_Index);
	}
}

