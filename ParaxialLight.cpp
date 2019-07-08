#include"Ray_Point.h"
#include<math.h>
Ray ParaxialLight(struct Ray*Ray0)								//��һ������߼���
{
	struct Ray RayFPL;											//�����һ�������
	struct Ray RaySPL;											//����ڶ��������

	RayFPL = RaySPL = Ray0;

	if (RayFPL->IsInfinite = true)								//�����һ�����������Զ��ʱ���
	{
		RayFPL->Ln = Ray0->L0;
		RayFPL->Un = 0;
	}
	else {														//�����һ������߷�����Զ��ʱ���
		RayFPL->Ln = Ray0->L0;
		RayFPL->Un = Math.Sin(Math.PI / (180 / Ray0->U0_D0));
	}
		
	RaySPL->Ln = 0;												//����ڶ�������ߣ�����������Զ��ʱ�����ͬ��
	RaySPL->Un = Math.Sin(Math.PI / (180 / Ray0->Y0_W0));
}