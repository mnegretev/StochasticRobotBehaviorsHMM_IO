
coord multiply_vector_scalar(coord vector1,float cnt){

        coord mult;

        mult.xc=vector1.xc*cnt;
        mult.yc=vector1.yc*cnt;
        return(mult);
}

coord add_vectors(coord vector1,coord vector2){

        coord sum;

        sum.xc=vector1.xc+vector2.xc;
        sum.yc=vector1.yc+vector2.yc;
        return(sum);
}


/*
This function is used to calculate the rotation angle for the Mvto command
*/

float get_ang(float ang,float c,float d,float X,float Y){
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




void get_dist_theta(float x,float y,float angle,float x1,float y1,float *distance,float *theta){

 // it calculates the distance
 *distance=(float)sqrt((x-x1)*(x-x1)+(y-y1)*(y-y1));
 //printf("Distance: %f\n",*distance);

 // it calculates the rotation angle
 *theta=get_ang(angle,x1,y1,x,y);
 //printf("rotation angle: %f\n",*theta);

}




