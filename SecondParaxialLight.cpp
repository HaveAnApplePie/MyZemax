#include"Ray_Point.h"
Ray SencondParaxialLight(struct Ray*Ray0)								//�ڶ�������߼���
{
	#define PI 3.1415927

	struct Ray RaySPL;											//����ڶ��������
	RaySPL = Ray0;

	RaySPL.Ln = 0;												//����ڶ�������ߣ�����������Զ��ʱ�����ͬ��
	RaySPL.Un = sin(PI / (180 / Ray0->Y0_W0));

	return RaySPL;
}