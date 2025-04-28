// robot_functions.h

#include "robot_small.h"

#ifndef PI
#define PI 3.1415926535f
#endif


typedef struct _answer_command{
	int status;
	char answer[300];
	char user[300];
	int id;
} answer_command;


typedef struct _coord{
	float xc,yc,zc,anglec;
} coord;


typedef struct _commands{
	float distance,angle,speed;
} Commands;



typedef struct _Behavior{
	float xc,yc,zc,status;
	int flg_vector;
} Behavior;


typedef struct _AdvanceAngle{
	float advance,angle;
} AdvanceAngle; 

typedef struct _centroid{
	int num;
	int id;
	int inv_id;
	float x,y,z;
	float angle; 
} centroid;


typedef struct _observation{
	int centroid;
	float x,y,theta,sensors[30];
} observation;

observation shared_observations[2];




/*
This function is used to calculate the rotation angle for the Mvto command
*/
float get_angle(float ang,float c,float d,float X,float Y){
	float x,y;
	
	x=c-X;
	y=d-Y;
	if((x == 0) && (y == 0)) return(0);
	if(fabs(x)<0.0001)	return((float) ((y<0.0f)? 3*PI/2  : PI/2) - ang );
	else{               
	 	if(x>=0.0f&&y>=0.0f) return( (float)(atan(y/x)-ang) );
		else if(x< 0.0f&&y>=0.0f) return( (float)(atan(y/x)+PI-ang) );
		else if(x< 0.0f&&y<0.0f) return( (float)(atan(y/x)+PI-ang) );
		else return( (float)(atan(y/x)+2*PI-ang));
	}
}



void get_distance_theta(float x,float y,float angle,float x1,float y1,float *distance,float *theta){
	
 // it calculates the distance
 *distance=(float)sqrt((x-x1)*(x-x1)+(y-y1)*(y-y1));
 //printf("Distance: %f\n",*distance);

 // it calculates the rotation angle
 *theta=get_angle(angle,x,y,x1,y1);
 //printf("rotation angle: %f\n",*theta);
		 
}



float distance(coord vector,coord vector1){
	
 float x,x1,y,y1;
 float distance;

 x=vector.xc;
 x1=vector1.xc;
 y=vector.yc;
 y1=vector1.yc;
 
 // it calculates the distance
 distance=(float)sqrt((x-x1)*(x-x1)+(y-y1)*(y-y1));
 //printf("Distance: %f\n",distance);

 return(distance);		 
}


float magnitude(coord vector){

	float magnitude;

	magnitude=(float)sqrt((vector.xc*vector.xc)+(vector.yc*vector.yc));
	//printf("magnitude: %f\n",magnitude);
	return(magnitude);
}




coord add_vectors(coord vector1,coord vector2){

	coord sum;

	sum.xc=vector1.xc+vector2.xc;
	sum.yc=vector1.yc+vector2.yc;
	return(sum);
}


coord dif_vectors(coord vector1,coord vector2){

	coord dif;

	dif.xc=vector1.xc-vector2.xc;
	dif.yc=vector1.yc-vector2.yc;
	return(dif);
}



coord multiply_vector_scalar(coord vector1,float cnt){

	coord mult;

	mult.xc=vector1.xc*cnt;
	mult.yc=vector1.yc*cnt;
	return(mult);
}

coord divide_vector_scalar(coord vector1,float cnt){

	coord div;

	div.xc=vector1.xc/cnt;
	div.yc=vector1.yc/cnt;
	return(div);
}



void find_corner(float mag_mov){
 int j,flag;
 float sonar,angle,dangle;

 flag=0;
 dangle=(float) (1.5708/3.0);

 ////move_robot("Ryu",(float)-2,0,0);

 for(j=1;j<=4;j++){
		 angle=(j-1)*dangle;
		 //printf("angle %f\n",angle);
////		 sonar=show_sensor("Ryu", "sonar", 1)-ROBOT_RADIO;
		 if(sonar > 10){
			flag=1;
			j=5;
			////move_robot("Ryu",0,dangle/1.5f,0);
		 }
		 ////else move_robot("Ryu",0,dangle,0);
 }
 if(flag==0){
	//// move_robot("Ryu",0,(float)-2.6170,0);
	 for(j=1;j<=3;j++){
		 angle=-(j-1)*dangle;
		 //printf("angle %f\n",angle);		 
		 ////sonar=show_sensor("Ryu", "sonar", 1);
		 if(sonar > 10){
			flag=1;
			j=5;
		////	move_robot("Ryu",0,-dangle/1.5f,0);
		 }
		 ////else move_robot("Ryu",0,-dangle,0);
	}
 }
//// move_robot("Ryu",mag_mov,0,0);

}
 

float find_coodinates_obstacle(float mag_mov){
 int j,flag;
 float sonar,angle,dangle;

 flag=0;
 dangle=(float) (1.5708/3.0);

 ////move_robot("Ryu",(float)-2,0,0);

 for(j=1;j<=4;j++){
		 angle=(j-1)*dangle;
		 //printf("angle %f\n",angle);
		//// sonar=show_sensor("Ryu", "sonar", 1)-ROBOT_RADIO;
		 if(sonar > 10){
			flag=1;
			j=5;
			////move_robot("Ryu",0,dangle/1.5f,0);
		 }
		 ////else move_robot("Ryu",0,dangle,0);
 }
 if(flag==0){
	//// move_robot("Ryu",0,(float)-2.6170,0);
	 for(j=1;j<=3;j++){
		 angle=-(j-1)*dangle;
		 //printf("angle %f\n",angle);		 
		 ////sonar=show_sensor("Ryu", "sonar", 1);
		 if(sonar > 10){
			flag=1;
			j=5;
		////	move_robot("Ryu",0,-dangle/1.5f,0);
		 }
		 ////else move_robot("Ryu",0,-dangle,0);
	}
 }
 ////move_robot("Ryu",mag_mov,0,0);

 return(0.0);
}






// it checks if a point is in the left or right side
int check_lines(float x,float y, float xk, float yk, float xl, float yl){

 float result,xt,yt;
 int flag=0;

 result=((yk-yl)*x)+((xl-xk)*y)+((xk*yl) - (xl*yk));
 if(result>0){
         flag=0; // left side
 }
 else{  // right side, inside
        // it checks if its on range
	//
	//printf("original x %f y %f xk %f yk %f xl %f yl %f\n",x,y,xk,yk,xl,yl);
	if(xk>xl){
	      xt=xl;
	      xl=xk;
	      xk=xt;
	}
	if(yk>yl){
	      yt=yl;
	      yl=yk;
	      yk=yt;
	}
	if( (xl == xk) && ((y >= yk) & (y <= yl)) ){
	      //printf("range x %f y %f xk %f yk %f xl %f yl %f\n",x,y,xk,yk,xl,yl);
	      flag=1;
	}
	else if( (yl == yk) && ((x >= xk) & (x <= xl)) ){
	     //printf("range x %f y %f xk %f yk %f xl %f yl %f\n",x,y,xk,yk,xl,yl);
	     flag=1;
	}
	else if(((x >= xk) & (x <= xl)) && ((y >= yk) & (y <= yl))){
		//printf("range x %f y %f xk %f yk %f xl %f yl %f\n",x,y,xk,yk,xl,yl);
		flag=1;
	}
 	else{
   		//printf("x %f y %f xk %f yk %f xl %f yl %f\n",x,y,xk,yk,xl,yl);
   		flag=0;
 	}	
 }

 return flag;

}



// It checks if a point is inside of an object
int check_inside(float x, float y, PolygonSonar polygons){

 int flag=1,j;
 float x0,y0,x1,y1,xf,yf;

 for(j=1; j< polygons.num_vertex;j++){
        x0=polygons.vertex[j].x;
        y0=polygons.vertex[j].y;
        x1=polygons.vertex[j+1].x;
        y1=polygons.vertex[j+1].y;

        flag=check_lines(x,y,x0,y0,x1,y1);
        if(flag == 0){
             return flag;
        }
 }

 //Last line
 xf=polygons.vertex[1].x;
 yf=polygons.vertex[1].y;

 flag=check_lines(x,y,x1,y1,xf,yf);

 return flag;

}


// it finds the if the robot gets inside of a polygon
int check_inside_polygons(int num_polygons,PolygonSonar *polygons, float x, float y){

 int i;
 int flag=0;

 for(i=1;i<num_polygons;i++){

    //printf("\n Object %s\n",polygons[i].name);
    // It finds in which objects is the point
    flag=check_inside(x, y, polygons[i]);
    if(flag==1){
    	return 1;
    }

 }

 return 0;

}

#ifndef SIMULATOR_SENSORS

// it finds if the intersection points, xinter and yinter, are between a line
int interval(float xinter,float yinter,PolygonSonar polygon,int j){

        float x1,x2,y1,y2;

        if(polygon.vertex[j].x < polygon.vertex[j+1].x){
                x1=polygon.vertex[j].x;
                x2=polygon.vertex[j+1].x;
        }
        else{
                x2=polygon.vertex[j].x;
                x1=polygon.vertex[j+1].x;
        }
        if(polygon.vertex[j].y < polygon.vertex[j+1].y){
                y1=polygon.vertex[j].y;
                y2=polygon.vertex[j+1].y;
        }
        else{
                y2=polygon.vertex[j].y;
                y1=polygon.vertex[j+1].y;
        }

        //printf("line interval %d x1 %f y1 %f\n",j,x1,y1);
        //printf("line interval %d x2 %f y2 %f\n",j,x2,y2);


        if(x1 != x2)
        if( (xinter < x1) || (xinter > x2))
                return(0);
        if(y1 != y2)
        if( (yinter < y1) || (yinter > y2))
                return(0);


        return(1);

}

// it finds if the intersection points are between the robot's line
int interval_robot(float xinter,float yinter,PolygonSonar robot){

        float x1,x2,y1,y2;

        if(robot.vertex[1].x < robot.vertex[2].x){
                x1=robot.vertex[1].x;
                x2=robot.vertex[2].x;
        }
        else{
                x2=robot.vertex[1].x;
                x1=robot.vertex[2].x;
        }
        if(robot.vertex[1].y < robot.vertex[2].y){
                y1=robot.vertex[1].y;
                y2=robot.vertex[2].y;
        }
        else{
                y2=robot.vertex[1].y;
                y1=robot.vertex[2].y;
        }
        //printf("line robot x1 %f y1 %f\n",x1,y1);
        //printf("line robot x2 %f y2 %f\n",x2,y2);


        if(x1 != x2)
        if( (xinter < x1) || (xinter > x2))
                return(0);
        if(y1 != y2)
        if( (yinter < y1) || (yinter > y2))
                return(0);


        return(1);

}

// it finds the distance between the robot and the intersection line
float magnitud(PolygonSonar robot,float xinter,float yinter){

        float distance;
        float x,y;

        x = robot.vertex[1].x-xinter;
        y = robot.vertex[1].y-yinter;
        distance=sqrtf(x*x+y*y);

        return distance;
}






// it finds the distance to the closest polygon
float distance_polygon(int num_polygons,PolygonSonar *polygons,PolygonSonar robot,
                                                        int *index_smallest){

        int i,j;
        float m,b,mr,br;
        float smallest_distance=(float)(0x7fffffff);
        float xinter,yinter,distance;

        mr=robot.line[1].m;
        br=robot.line[1].b;
        //printf("\n robot m %f b %f", mr,br);

        for(i=1;i<num_polygons;i++){

          //printf("\n polygon %s \n", polygons[i].name);

          for(j=1; j<= polygons[i].num_vertex;j++){
                        m=polygons[i].line[j].m;
                        b=polygons[i].line[j].b;
                                        //printf("line m %f b %f\n", m,b);
                                        //xinter= (float)(br-b)/(float)(m-mr);
                                        xinter= (float)(b-br)/(float)(mr-m);
                                        //yinter=m*xinter+b;
                                        yinter=mr*xinter+br;

                                        //printf("intersection %d xinter %f yinter %f\n",
                                        //              j,xinter,yinter);

                                        if(interval(xinter,yinter,polygons[i],j)==1)
                                                if(interval_robot(xinter,yinter,robot)==1){


                                                        distance=magnitud(robot,xinter,yinter);
                                                        //printf("correct interval %d dist %f smallest %f\n",
                                                                                                //j,distance,smallest_distance);
                                                        if(distance<smallest_distance){
                                                                smallest_distance=distance;
                                                                *index_smallest=i;
                                                        }
                                        }
        }
    }

    return smallest_distance;
}





// it returns the distance to closest poligon from the robot
int shs_distance_obstacle(float x1, float y1, float x2, float y2,float dist_advance){

 int index;
 float distance;


  index=0;
  robot_sensor.vertex[1].x=x1;
  robot_sensor.vertex[1].y=y1;


  robot_sensor.vertex[2].x=x2+0.0001;
  robot_sensor.vertex[2].y=y2+0.0001;

  //printf("check x1 %f y1 %f\n",robot_sensor.vertex[1].x,robot_sensor.vertex[1].y);
  ////printf("check x2 %f y2 %f\n",robot_sensor.vertex[2].x,robot_sensor.vertex[2].y);

  //m=(y2-y1)/(x2-x1);
  //b=(x2*y1-y2*x1)/(x2-x1);
  robot_sensor.line[1].m= (robot_sensor.vertex[2].y-robot_sensor.vertex[1].y)/
                        (robot_sensor.vertex[2].x-robot_sensor.vertex[1].x);
  robot_sensor.line[1].b= (robot_sensor.vertex[2].x*robot_sensor.vertex[1].y-
                         robot_sensor.vertex[2].y*robot_sensor.vertex[1].x)/
                        (robot_sensor.vertex[2].x-robot_sensor.vertex[1].x);




  // it finds the distance to the closest polygon
  distance=distance_polygon(num_polygons_wrl,polygons_wrl,robot_sensor,&index);

  //printf("shs sonar %d angle %f polygon %s distance %f\n",num,angle,
  //                            polygons_wrl[index].name,distance);

 //printf("** check distance closests %f distance advance %f **\n",distance,dist_advance);

 if(distance>abs(dist_advance)){
        return 0;
 }else{
        return 1;
 }

}

#endif

