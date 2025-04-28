function f_r=genera_crepulsion(c_c,c_o,c_m,eta,d0)
c=length(c_c);
o=length(c_o);
m=length(c_m);
f_r=[];

for i=1:1:c
    sumax=0;
    sumay=0;
    for j=1:1:o
        mag=sqrt((c_c(i,1)-c_o(j,1))^2 + (c_c(i,2)-c_o(j,2))^2);
        if mag>d0
            fx=0;
            fy=0;
        else
            fx=-eta*(1/mag-1/d0)*(1/mag^3)*(c_c(i,1)-c_o(j,1));
            fy=-eta*(1/mag-1/d0)*(1/mag^3)*(c_c(i,2)-c_o(j,2));
        end
        sumax=sumax+fx;
        sumay=sumay+fy;
    end
    for j=1:1:m
        mag=sqrt((c_c(i,1)-c_m(j,1))^2 + (c_c(i,2)-c_m(j,2))^2);
        if mag>d0
            fx=0;
            fy=0;
        else
            fx=-eta*(1/mag-1/d0)*(1/mag^3)*(c_c(i,1)-c_m(j,1));
            fy=-eta*(1/mag-1/d0)*(1/mag^3)*(c_c(i,2)-c_m(j,2));
        end
        sumax=sumax+fx;
        sumay=sumay+fy;
    end
    F=[sumax,sumay];
    f_r=[f_r;F];
end