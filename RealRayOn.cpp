#include"Ray_Point.h"
#include<math.h>
Ray RealRayOn(double Kw, double Kn, struct Ray*Ray0)			//�������ϵ�ʵ�ʹ�
{
	#define PI 3.1415927

	struct Ray RayRealOn;											
	RayRealOn = *Ray0;

	if (RayRealOn.IsInfinite == true)								//�ж��Ƿ�Ϊ����Զ��
	{
		RayRealOn.Ln = Ray0->L0;
		RayRealOn.Un = 0;
	}
	else {
		RayRealOn.Ln = Ray0->L0;
		RayRealOn.Un = asin(Kn*sin(Ray0->U0_D0*PI/ 180));
	}

	return RayRealOn;
}