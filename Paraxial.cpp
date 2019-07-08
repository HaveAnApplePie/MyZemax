#include"Ray_Point.h"
#include<math.h>



Ray FirstParaxialLight(struct Ray*Ray0)							//��һ������߼���
{


	struct Ray RayFPL;											//�����һ�������
	RayFPL = *Ray0;

	if (RayFPL.IsInfinite == true)								//�����һ�����������Զ��ʱ���
	{
		RayFPL.Ln = Ray0->L0;
		RayFPL.Un = 0;
	}
	else {														//�����һ������߷�����Զ��ʱ���
		RayFPL.Ln = Ray0->L0;
		RayFPL.Un = sin(PI / (180 / Ray0->U0_D0));
	}

	return RayFPL;
}

Ray SencondParaxialLight(struct Ray*Ray0)								//�ڶ�������߼���
{

	struct Ray RaySPL;											//����ڶ��������
	RaySPL = *Ray0;

	RaySPL.Ln = 0;												//����ڶ�������ߣ�����������Զ��ʱ�����ͬ��
	
	if (Ray0->IsInfinite == true) {
		RaySPL.Un = Ray0->Y0_W0;
	}
	else {
		RaySPL.Un = atan(Ray0->Y0_W0 / (-Ray0->L0))*180/PI;
	}

	return RaySPL;
}

Ray* Paraxial_single_surface(struct Ray *ray_in,double Radius[],double Distance[],double Re_Index[]) {
//�����ĵ��������
	Ray ray_out;
	int k;
	double r,d,n1,n2;
	double u1, i1, l1;
	double u2, i2, l2;
//===========��ʼ��============
	l1 = ray_in->Ln;
	u1 = ray_in->Un;
	
	k = ray_in->now_surface_number + 1; //Ҫ�����������
	n1 = Re_Index[k];					//�﷽������
	n2 = Re_Index[k + 1];				//��������
	r  = Radius[k];						//�뾶
	if (k < ray_in->all_surface_number)	//ǰk-1����
		d = Distance[k];		
	else								//���һ����d=0
		d = 0;

	ray_out = *ray_in;

//===========��ʽ����===========
	if (ray_in->IsInfinite == true && k == 0)
		i1 = ray_in->U0_D0 / 2 / r;
	else
		i1 = (l1 - r) / r * u1;
	i2 = n1 / n2 * i1;
	u2 = i1 + u1 - i2;
	l2 = r + r * i2 / u2;
//===========���ɹ�ʽ===========
	ray_out.Ln = l2 - d;
	ray_out.Un = u2;
	ray_out.now_surface_number++;

	*ray_in = ray_out;

	return	ray_in;
}

void Paraxial_calculation(struct Ray *ray0, double Radius[], double Distance[], double Re_Index[]) {
	int i,j,k,n;
	double f_image, l_F_image, l_H_image, y_image;
	Ray RayFPL,RaySPL,*Raycal;	//Raycal�����ڼ���Ĺ���

//=============��ʼ��==========
	n = ray0->all_surface_number;
	RayFPL = FirstParaxialLight(ray0);
	RaySPL = SencondParaxialLight(ray0);

//=============��һ�����========
	Raycal = &RayFPL;
	for (i = 0;i <= ray0->all_surface_number;i++) {
		Raycal = Paraxial_single_surface(Raycal, Radius, Distance, Re_Index);
	}
	l_F_image = Raycal->Ln;				//�������
//============�ڶ������=========
	Raycal = &RaySPL;
	for (i = 0;i <= ray0->all_surface_number;i++) {
		Raycal = Paraxial_single_surface(Raycal, Radius, Distance, Re_Index);
	}

//============���ݴ���==========
//1.�������
	Raycal->now_surface_number = -1;
	Raycal->IsInfinite = true;
	Raycal->U0_D0 = 10;
	Raycal->Y0_W0 = 0;
	Raycal->Ln = 1E15;
	Raycal->Un = 0;

	f_image = 1;

	for (i = 0;i <= ray0->all_surface_number;i++) {
		Raycal = Paraxial_single_surface(Raycal, Radius, Distance, Re_Index);
		if (i < ray0->all_surface_number)
			f_image = f_image * (Raycal->Ln + Distance[Raycal->now_surface_number]) / (Raycal->Ln);
		else
			f_image = f_image * Raycal->Ln;
	}
//2.�������λ��
	l_H_image = l_F_image - f_image;

//3.�������
	double l1, l2, n1, n2, d, r, y_object;
	RaySPL = *ray0;
	Raycal = &RaySPL;
	


	if (Raycal->IsInfinite == true) {
		y_image = f_image*tan(Raycal->Y0_W0*PI / 180);
	}
	else {
		Raycal->Ln = Raycal->L0;
		y_object = Raycal->Y0_W0;


		y_image = y_object * Re_Index[0] / Re_Index[n + 1];

		for (i = 0;i <= ray0->all_surface_number;i++) {
			l1 = Raycal->Ln;
			n1 = Re_Index[i];					//�﷽������
			n2 = Re_Index[i + 1];				//��������
			r = Radius[i];						//�뾶
			if (i < ray0->all_surface_number)	//ǰk-1����
				d = Distance[i];
			else								//���һ����d=0
				d = 0;

			l2 = n2 / (n1 / l1 + (n2 - n1) / r);

			y_image = y_image * l2 / l1;

			Raycal->Ln = l2 - d;
		}


	}


}

