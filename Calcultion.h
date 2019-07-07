#ifndef	CALCULTION_H
#define	CALCULTION_H

#include"Ray_Point.h"

//�����
Ray FirstParaxialLight(struct Ray*Ray0);	//��һ�������
Ray SencondParaxialLight(struct Ray*Ray0);	//�ڶ��������
Ray* Paraxial_single_surface(struct Ray *ray_in, double Radius[], double Distance[], double Re_Index[]);	//���������
void Paraxial_calculation(struct Ray *ray0, double Radius[], double Distance[], double Re_Index[]);			//���������

//ʵ�ʹ���
Ray RealRayOff(double Kw, double Kn, struct Ray*Ray0);
Ray RealRayOn(double Kw, double Kn, struct Ray*Ray0);
Ray* RealRay_single_surface(struct Ray *ray_in, double Radius[], double Distance[], double Re_Index[], double Kn);
void RealRay_calculation(struct Ray *ray0, double Radius[], double Distance[], double Re_Index[]);


#endif