#include"Ray_Point.h"
#include"Calcultion.h"
#include<math.h>

Ray InitialNarrowBeam(struct Ray*ray0, double Radius[],double Kw,double Kn) {	//��ʼ��
	double PA, x, T0, S0;
	double i1,H;
	struct Ray NarrowBeam;

//������ʵ�ʹ����������������ĳ�ʼ��

	NarrowBeam = RealRayOff(Kw, Kn, ray0);

	i1 = asin((NarrowBeam.Ln - Radius[0]) / Radius[0] * sin(PI*NarrowBeam.Un / 180)) * 180 / PI;


//���S0��T0
	PA = NarrowBeam.Ln * sin(NarrowBeam.Un * PI / 180) / cos(0.5*(i1 - NarrowBeam.Un)*PI / 180);
	x = PA * PA / (2*Radius[0]);
	S0 = (NarrowBeam.L0 - x) / cos(NarrowBeam.Un*PI/180);
	T0 = (NarrowBeam.L0 - x) / cos(NarrowBeam.Un*PI/180);

	NarrowBeam.S = S0;
	NarrowBeam.T = T0;

	return NarrowBeam;
}

Ray* NarrowBeam_single_surface(struct Ray *ray_in,double Radius[], double Distance[], double Re_Index[],double Kn) {
//ϸ��������

	//ʵ�ʹ������㲿��

	Ray ray_out;
	int k;
	double r, d, D, H, PA, n1, n2, x1, x2;
	double u1, i1, l1, t1, s1;
	double u2, i2, l2, t2, s2;
	double i2_1;
//===========��ʼ��============
	l1 = ray_in->Ln;
	u1 = ray_in->Un;
	t1 = ray_in->T;
	s1 = ray_in->S;


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

	i1 = asin((l1 - r) / r * sin(PI*u1 / 180)) * 180 / PI;
	i2 = asin(n1 / n2 * sin(PI*i1 / 180)) * 180 / PI;
	u2 = u1 + i1 - i2;
	l2 = r + r * sin(PI*i2 / 180) / sin(PI*u2 / 180);

	t2 = n2 * cos(i2 * PI / 180)*cos(i2 * PI / 180) / (((n2 * cos(PI*i2 / 180) - n1 * cos(PI * i1 / 180)) / r) + n1 * cos(i1 * PI / 180)*cos(i1 * PI / 180) / t1);
	s2 = n2 / (((n2 * cos(PI * i2 / 180) - n1 * cos(PI * i1 / 180)) / r) + n1 / s1);

//===========���ɹ�ʽ===========
	ray_out.Ln = l2 - d;
	ray_out.Un = u2;
	if (k < ray_in->all_surface_number) {
		PA = (l1 * sin(PI*u1/180)) / cos(0.5*(i1 - u1)*PI / 180);
		x1 = (PA * PA) / (2 * r);
		i2_1 = asin((ray_out.Ln - Radius[k + 1]) / Radius[k + 1] * sin(PI*u2 / 180)) * 180 / PI;
		PA = (ray_out.Ln* sin(PI*u2/180)) / cos(0.5*(i2_1 - u2)*PI / 180);
		x2 =(PA * PA) / (2 * Radius[k + 1]);
		D = (d - x1 + x2) / cos(PI*u2 / 180);
	}
	else
		D = 0;

	ray_out.T = t2 - D;
	ray_out.S = s2 - D;

	ray_out.now_surface_number++;

	*ray_in = ray_out;

	return	ray_in;
}

void NarrowBeam_calculation(struct Ray*ray0, double Radius[], double Distance[], double Re_Index[])
{
	int i, j, k, n;
	double Kw, Kn, delta_x;
	double l_t_image, l_s_image, x, PA_n,i_n;
	Ray Rayinit, *Raycal;

//=============��ʼ��==========
	n = ray0->all_surface_number;
//1.1�ӳ� 0�׾�  ��ɢ����
	Kw = 1;
	Kn = 0;
	Rayinit = InitialNarrowBeam(ray0,Radius,Kw,Kn);
	Raycal = &Rayinit;
	for (i = 0;i <= ray0->all_surface_number;i++) {
		if (i == n) {
			i_n = asin((Raycal->Ln - Radius[n]) / Radius[n] * sin(PI*Raycal->Un / 180)) * 180 / PI;
			PA_n = (Raycal->Ln * sin(PI*Raycal->Un / 180)) / cos(0.5*(i_n - Raycal->Un)*PI / 180);
		}		
		Raycal = NarrowBeam_single_surface(Raycal, Radius, Distance, Re_Index, Kn);
	}
	delta_x = (Raycal->T - Raycal->S)*cos(Raycal->Un*PI / 180);
	

	x = (PA_n*PA_n) / (2 * Radius[n]);
//���糡��
	l_t_image = Raycal->T*cos(Raycal->Un*PI / 180) + x;

//��ʸ����
	l_s_image = Raycal->S*cos(Raycal->Un*PI / 180) + x;
}