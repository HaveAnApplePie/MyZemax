#include"Ray_Point.h"
Ray FirstParaxialLight(struct Ray*Ray0)							//��һ������߼���
{
	#define PI 3.1415927

	struct Ray RayFPL;											//�����һ�������
	RayFPL = Ray0;

	if (RayFPL.IsInfinite = true)								//�����һ�����������Զ��ʱ���
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