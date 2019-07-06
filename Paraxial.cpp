#include"Ray_Point.h"
#include<math.h>

#define PI 3.1415927

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
	RaySPL.Un = sin(PI / (180 / Ray0->Y0_W0));

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
	i1 = (l1 - r) / r * u1;
	i2 = n1 / n2 * i1;
	u2 = i1 + u1 - i2;
	l2 = r + r * i2 / u2;
//===========���ɹ�ʽ===========
	ray_out.Ln = l2 - d;
	ray_out.Un = u2;

	*ray_in = ray_out;

	return	ray_in;
}



void Paraxial_calculation(struct Ray *ray0, double Radius[], double Distance[], double Re_Index[]) {
	int i,j,k,n;
	Ray RayFPL,RaySPL,*Raycal;

//=============��ʼ��==========
	n = ray0->all_surface_number;
	RayFPL = FirstParaxialLight(ray0);
	RaySPL = SencondParaxialLight(ray0);

//=============��һ�����========
	Raycal = &RayFPL;
	for (i = 0;i <= ray0->all_surface_number;i++) {
		Raycal = Paraxial_single_surface(Raycal, Radius, Distance, Re_Index);
	}

//============�ڶ������=========
	Raycal = &RaySPL;
	for (i = 0;i <= ray0->all_surface_number;i++) {
		Raycal = Paraxial_single_surface(Raycal, Radius, Distance, Re_Index);
	}
}

