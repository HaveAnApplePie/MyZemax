#include<stdio.h>
#include<stdlib.h>

#include"Ray_Point.h"
#include"Initial.h"
#include"Calcultion.h"


int main(void) {

	struct Ray ray0;
	double Radius[100], Distance[100], Re_Index[100];

	InitialFromFile(&ray0,Radius,Distance,Re_Index);
	Paraxial_calculation(&ray0, Radius, Distance, Re_Index);

	return 0;
}