#include"Ray_Point.h"
#include<math.h>
Ray RealRayOff(double Kw, double Kn, struct Ray*Ray0)			//���������ʵ�ʹ�
{
	#define PI 3.1415927

	struct Ray RayRealOff;
	RayRealOff = *Ray0;

	if (RayRealOff.IsInfinite == true)								//�ж��Ƿ�Ϊ����Զ��
	{
		RayRealOff.Ln = Kn * Ray0->U0_D0 / 2 * tan(Ray0->Y0_W0*PI / 180);
		RayRealOff.Un = Ray0->Y0_W0;
	}
	else {
		RayRealOff.Ln = Kn* Ray0->A0/tan(Ray0->U0_D0);
		RayRealOff.Un = atan((Kw*Ray0->Y0_W0-Kn* Ray0->A0)/ (0 - Ray0->L0));
	}

	return RayRealOff;
}