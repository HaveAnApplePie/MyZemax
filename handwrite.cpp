void handwrite(struct Ray*Ray0  , double Radius[], double Distance[],double Re_Index[])
{
	int k,i;
	
	Ray0->surface_number = -1;
	
	Ray0->Wavelen = D_RAY;
	
	scanf("%lf",&Ray0->L0);			//初始物距
	
	if(Ray0->L0<INFINITE)
	 
	 	Ray0->IsInfinite = false;
	
	else Ray0->IsInfinite = true;
	
	scanf("%lf",&Ray0->U0_D0);		//初始物方半径角U0 入瞳直径D0 
	
	scanf("%lf",&Ray0->Y0_W0);		//初始物高Y0 半径角W 
	
	scanf("%d",&k);
	
	for(i=0;i<k;i++){
	
	scanf("%lf",&Radius[i]);
}
	for(i=0;i<k-1;i++){
	
	scanf("%lf",&Distance[i]);
}
	for(i=0;i<k+1;i++){
	
	scanf("%lf",&Re_Index[i]);
}
}
