#include"Ray_Point.h"
#include<math.h>

Ray RealRayOff(double Kw, double Kn, struct Ray*Ray0)			//计算轴外点实际光
{
	struct Ray RayRealOff;
	RayRealOff = *Ray0;

	if (RayRealOff.IsInfinite == true)								//判断是否为无穷远物
	{		
		RayRealOff.Un = Kw*Ray0->Y0_W0;
		RayRealOff.Ln = Kn * Ray0->A0 / tan(RayRealOff.Un*PI / 180);
	}
	else {
		RayRealOff.Un = atan((Kw*Ray0->Y0_W0 - Kn * Ray0->A0) / (0 - Ray0->L0)) * 180 / PI;
		RayRealOff.Ln = Kn * Ray0->A0 / tan(RayRealOff.Un*PI/180);
	}

	return RayRealOff;
}

Ray RealRayOn(double Kw, double Kn, struct Ray*Ray0)			//计算轴上点实际光
{

	struct Ray RayRealOn;
	RayRealOn = *Ray0;

	if (RayRealOn.IsInfinite == true)								//判断是否为无穷远物
	{
		RayRealOn.Ln = Ray0->L0;
		RayRealOn.Un = 0;
	}
	else {
		RayRealOn.Ln = Ray0->L0;
		//RayRealOn.Un = Kn*sin(Ray0->U0_D0*PI / 180);
		RayRealOn.Un = asin(Kn*sin(Ray0->U0_D0*PI / 180)) * 180 / PI;
	}

	return RayRealOn;
}

Ray* RealRay_single_surface(struct Ray *ray_in, double Radius[], double Distance[], double Re_Index[],double Kn) {
//实际光的单个面计算
	Ray ray_out;
	int k;
	double r, d, H, n1, n2;
	double u1, i1, l1;
	double u2, i2, l2;
//===========初始化============
	l1 = ray_in->Ln;
	u1 = ray_in->Un;

	k = ray_in->now_surface_number + 1; //要计算的面的序号
	n1 = Re_Index[k];					//物方折射率
	n2 = Re_Index[k + 1];				//像方折射率
	r = Radius[k];						//半径
	if (k < ray_in->all_surface_number)	//前k-1个面
		d = Distance[k];
	else								//最后一个面d=0
		d = 0;

	ray_out = *ray_in;
//===========公式计算===========
	if (ray_in->IsInfinite == true && k == 0 && Kn!=0 && ray_in->Un==0) {//无穷远平行光
		H = Kn * ray_in->A0;
		i1 = asin(H / r)*180/PI;
	}
	else
		i1 = asin((l1 - r) / r * sin(PI*u1 / 180)) * 180 / PI;
	i2 = asin(n1 / n2 * sin(PI*i1/180))*180/PI;
	u2 = u1 + i1 - i2;
	l2 = r + r * sin(PI*i2 / 180)/sin(PI*u2 / 180);
//===========过渡公式===========
	ray_out.Ln = l2 - d;
	ray_out.Un = u2;
	ray_out.now_surface_number++;

	*ray_in = ray_out;

	return	ray_in;

}

void RealRay_calculation(struct Ray *ray0, double Radius[], double Distance[], double Re_Index[]) {
	int i, j, k, n;
	double Kw, Kn;
	Ray RayOn, RayOff, *Raycal, RayOffh;;
//=============初始化==========
	n = ray0->all_surface_number;


//===========test===========
//1视场 0孔径
	Kw = 1;
	Kn = 0;
	RayOff = RealRayOff(Kw, Kn, ray0);
	Raycal = &RayOff;
	for (i = 0;i <= ray0->all_surface_number;i++) {
		Raycal = RealRay_single_surface(Raycal, Radius, Distance, Re_Index, Kn);
	}
//===========实际像位置=========
//1.0视场 1孔径
	Kw = 0;
	Kn = 1;
	RayOn = RealRayOn(Kw, Kn, ray0);
	Raycal = &RayOn;
	for (i = 0;i <= ray0->all_surface_number;i++) {
		Raycal = RealRay_single_surface(Raycal, Radius, Distance, Re_Index, Kn);
	}
//2.0视场 0.7孔径
	Kw = 0;
	Kn = 0.7;
	RayOn = RealRayOn(Kw, Kn, ray0);
	Raycal = &RayOn;
	for (i = 0;i <= ray0->all_surface_number;i++) {
		Raycal = RealRay_single_surface(Raycal, Radius, Distance, Re_Index, Kn);
	}
//============位置色差==========
//1.  0视场 0.7孔径
	Kw = 0;
	Kn = 0;
	RayOn = RealRayOn(Kw, Kn, ray0);
	Raycal = &RayOn;
	for (i = 0;i <= ray0->all_surface_number;i++) {
		Raycal = RealRay_single_surface(Raycal, Radius, Distance, Re_Index, Kn);
	}

//============实际像高==========
	//	1视场	0孔径
	Kw = 1;
	Kn = 1;
	double Ys;


	RayOff = RealRayOff(Kw, Kn, ray0);
	Raycal = &RayOff;
	for (i = 0; i <= ray0->all_surface_number; i++) {
		Raycal = RealRay_single_surface(Raycal, Radius, Distance, Re_Index, Kn);
	}
	Ys = (Raycal->Ln - 96.833569) * tan(Raycal->Un * PI / 180);

	//	0.7视场	0孔径
	Kw = 0.7;
	Kn = 0;
	RayOff = RealRayOff(Kw, Kn, ray0);
	Raycal = &RayOff;
	for (i = 0; i <= ray0->all_surface_number; i++) {
		Raycal = RealRay_single_surface(Raycal, Radius, Distance, Re_Index, Kn);
	}
	Ys = (Raycal->Ln - 121.59595451136) * tan(Raycal->Un * PI / 180);

	//子午慧差
	double Yup, Ymd, Ydw, Ymc;
	//	1视场	1孔径	上光线
	Kw = 0.7;
	Kn = 1;
	RayOff = RealRayOff(Kw, Kn, ray0);
	Raycal = &RayOff;
	for (i = 0; i <= ray0->all_surface_number; i++) {
		Raycal = RealRay_single_surface(Raycal, Radius, Distance, Re_Index, Kn);
	}
	Yup = (Raycal->Ln - 121.59595451136) * tan(Raycal->Un * PI / 180);

	//	1视场	0孔径	主光线
	Kw = 0.7;
	Kn = 0;
	RayOff = RealRayOff(Kw, Kn, ray0);
	Raycal = &RayOff;
	for (i = 0; i <= ray0->all_surface_number; i++) {
		Raycal = RealRay_single_surface(Raycal, Radius, Distance, Re_Index, Kn);
	}
	Ymd = (Raycal->Ln - 121.59595451136) * tan(Raycal->Un * PI / 180);

	//	1视场	-1孔径	下光线
	Kw = 0.7;
	Kn = -1;
	RayOff = RealRayOff(Kw, Kn, ray0);
	Raycal = &RayOff;
	for (i = 0; i <= ray0->all_surface_number; i++) {
		Raycal = RealRay_single_surface(Raycal, Radius, Distance, Re_Index, Kn);
	}
	Ydw = (Raycal->Ln - 121.59595451136) * tan(Raycal->Un * PI / 180);
	Ymc = (Yup + Ydw) / 2 - Ymd;
}