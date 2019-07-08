#include"Ray_Point.h"
#include<math.h>

Ray RealRayOff(double Kw, double Kn, struct Ray*Ray0)			//���������ʵ�ʹ�
{
	struct Ray RayRealOff;
	RayRealOff = *Ray0;

	if (RayRealOff.IsInfinite == true)								//�ж��Ƿ�Ϊ����Զ��
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

Ray RealRayOn(double Kw, double Kn, struct Ray*Ray0)			//�������ϵ�ʵ�ʹ�
{

	struct Ray RayRealOn;
	RayRealOn = *Ray0;

	if (RayRealOn.IsInfinite == true)								//�ж��Ƿ�Ϊ����Զ��
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
//ʵ�ʹ�ĵ��������
	Ray ray_out;
	int k;
	double r, d, H, n1, n2;
	double u1, i1, l1;
	double u2, i2, l2;
//===========��ʼ��============
	l1 = ray_in->Ln;
	u1 = ray_in->Un;

	k = ray_in->now_surface_number + 1; //Ҫ�����������
	n1 = Re_Index[k];					//�﷽������
	n2 = Re_Index[k + 1];				//��������
	r = Radius[k];						//�뾶
	if (k < ray_in->all_surface_number)	//ǰk-1����
		d = Distance[k];
	else								//���һ����d=0
		d = 0;

	ray_out = *ray_in;
//===========��ʽ����===========
	if (ray_in->IsInfinite == true && k == 0 && Kn!=0 && ray_in->Un==0) {//����Զƽ�й�
		H = Kn * ray_in->A0;
		i1 = asin(H / r)*180/PI;
	}
	else
		i1 = asin((l1 - r) / r * sin(PI*u1 / 180)) * 180 / PI;
	i2 = asin(n1 / n2 * sin(PI*i1/180))*180/PI;
	u2 = u1 + i1 - i2;
	l2 = r + r * sin(PI*i2 / 180)/sin(PI*u2 / 180);
//===========���ɹ�ʽ===========
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
//=============��ʼ��==========
	n = ray0->all_surface_number;


//===========test===========
//1�ӳ� 0�׾�
	Kw = 1;
	Kn = 0;
	RayOff = RealRayOff(Kw, Kn, ray0);
	Raycal = &RayOff;
	for (i = 0;i <= ray0->all_surface_number;i++) {
		Raycal = RealRay_single_surface(Raycal, Radius, Distance, Re_Index, Kn);
	}
//===========ʵ����λ��=========
//1.0�ӳ� 1�׾�
	Kw = 0;
	Kn = 1;
	RayOn = RealRayOn(Kw, Kn, ray0);
	Raycal = &RayOn;
	for (i = 0;i <= ray0->all_surface_number;i++) {
		Raycal = RealRay_single_surface(Raycal, Radius, Distance, Re_Index, Kn);
	}
//2.0�ӳ� 0.7�׾�
	Kw = 0;
	Kn = 0.7;
	RayOn = RealRayOn(Kw, Kn, ray0);
	Raycal = &RayOn;
	for (i = 0;i <= ray0->all_surface_number;i++) {
		Raycal = RealRay_single_surface(Raycal, Radius, Distance, Re_Index, Kn);
	}
//============λ��ɫ��==========
//1.  0�ӳ� 0.7�׾�
	Kw = 0;
	Kn = 0;
	RayOn = RealRayOn(Kw, Kn, ray0);
	Raycal = &RayOn;
	for (i = 0;i <= ray0->all_surface_number;i++) {
		Raycal = RealRay_single_surface(Raycal, Radius, Distance, Re_Index, Kn);
	}

//============ʵ�����==========
	//	1�ӳ�	0�׾�
	Kw = 1;
	Kn = 1;
	double Ys;


	RayOff = RealRayOff(Kw, Kn, ray0);
	Raycal = &RayOff;
	for (i = 0; i <= ray0->all_surface_number; i++) {
		Raycal = RealRay_single_surface(Raycal, Radius, Distance, Re_Index, Kn);
	}
	Ys = (Raycal->Ln - 96.833569) * tan(Raycal->Un * PI / 180);

	//	0.7�ӳ�	0�׾�
	Kw = 0.7;
	Kn = 0;
	RayOff = RealRayOff(Kw, Kn, ray0);
	Raycal = &RayOff;
	for (i = 0; i <= ray0->all_surface_number; i++) {
		Raycal = RealRay_single_surface(Raycal, Radius, Distance, Re_Index, Kn);
	}
	Ys = (Raycal->Ln - 121.59595451136) * tan(Raycal->Un * PI / 180);

	//����۲�
	double Yup, Ymd, Ydw, Ymc;
	//	1�ӳ�	1�׾�	�Ϲ���
	Kw = 0.7;
	Kn = 1;
	RayOff = RealRayOff(Kw, Kn, ray0);
	Raycal = &RayOff;
	for (i = 0; i <= ray0->all_surface_number; i++) {
		Raycal = RealRay_single_surface(Raycal, Radius, Distance, Re_Index, Kn);
	}
	Yup = (Raycal->Ln - 121.59595451136) * tan(Raycal->Un * PI / 180);

	//	1�ӳ�	0�׾�	������
	Kw = 0.7;
	Kn = 0;
	RayOff = RealRayOff(Kw, Kn, ray0);
	Raycal = &RayOff;
	for (i = 0; i <= ray0->all_surface_number; i++) {
		Raycal = RealRay_single_surface(Raycal, Radius, Distance, Re_Index, Kn);
	}
	Ymd = (Raycal->Ln - 121.59595451136) * tan(Raycal->Un * PI / 180);

	//	1�ӳ�	-1�׾�	�¹���
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