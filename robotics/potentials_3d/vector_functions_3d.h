

typedef struct _cord{
        float xc,yc,zc,anglec;
} cord;

typedef struct _Behav{
        float xc,yc,zc,status;
        int flg_vector;
} Behav;






float magnitude_3d(cord vector){

        float magnitude;
        magnitude=(float)sqrt((vector.xc*vector.xc)+(vector.yc*vector.yc)+(vector.zc*vector.zc));
        //printf("magnitude: %f\n",magnitude);
        return(magnitude);
}


cord divide_vector_scalar_3d(cord vector1,float cnt){

        cord div;

        div.xc=vector1.xc/cnt;
        div.yc=vector1.yc/cnt;
        div.zc=vector1.zc/cnt;

        return(div);

}





// it gets an unit vector
cord get_unit_vector_3d(Behav Bvector){

 float mag;
 cord unit_vector,vector;

 unit_vector.xc=0;
 unit_vector.yc=0;
 unit_vector.zc=0;

 vector.xc=Bvector.xc;
 vector.yc=Bvector.yc;
 vector.zc=Bvector.zc;

 mag=magnitude_3d(vector);

 if(mag != 0)
        unit_vector=divide_vector_scalar_3d(vector,mag);

 return unit_vector;

}





cord dif_vectors_3d(cord vector1,cord vector2){

        cord dif;

        dif.xc=vector1.xc-vector2.xc;
        dif.yc=vector1.yc-vector2.yc;
        dif.zc=vector1.zc-vector2.zc;

        return(dif);

}



cord multiply_vector_scalar_3d(cord vector1,float cnt){

        cord mult;

        mult.xc=vector1.xc*cnt;
        mult.yc=vector1.yc*cnt;
        mult.zc=vector1.zc*cnt;

        return(mult);
}




cord add_vectors_3d(cord vector1,cord vector2){

        cord sum;

        sum.xc=vector1.xc+vector2.xc;
        sum.yc=vector1.yc+vector2.yc;
        sum.zc=vector1.zc+vector2.zc;

        return(sum);

}


/*
This function is used to calculate the rotation angle for the Mvto command
*/

float get_ang_3d(float ang,float c,float d,float X,float Y){
        float x,y;

        x=c-X;
        y=d-Y;
        if((x == 0) && (y == 0)) return(0);

        if(fabs(x)<0.0001)  return((float) ((y<0.0f)? 3*PI/2  : PI/2) - ang );
        else{
                if(x>=0.0f&&y>=0.0f) return( (float)(atan(y/x)-ang) );
                else if(x< 0.0f&&y>=0.0f) return( (float)(atan(y/x)+PI-ang) );
                else if(x< 0.0f&&y<0.0f) return( (float)(atan(y/x)+PI-ang) );
                else return( (float)(atan(y/x)+2*PI-ang));
        }
}




void get_dist_beta_gamma(float x,float y, float z, float beta_r,float gamma_r,float x1,float y1,float z1,float *distance,float *beta,float *gamma){

 float d;
 float m;
 float n;


 // it calculates the distance
 d=(float)sqrt((x-x1)*(x-x1)+(y-y1)*(y-y1)+(z-z1)*(z-z1));
 //printf("Distance: %f\n",*distance);

 // it calculates the rotation angle beta
 m=(y1-y)/d;
 *beta=acos(m);
 printf("rotation angle beta: %f\n",*beta);
 *beta=*beta+beta_r;
 printf("rotation total angle beta: %f\n",*beta);

 // it calculates the rotation angle gamma
 n=(z1-z)/d;
 *gamma=acos(n);
 printf("rotation angle gamma %f\n",*gamma);
 *gamma=*gamma+gamma_r;

 *distance= d;

}




