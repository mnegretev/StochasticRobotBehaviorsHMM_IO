
clear

path= "../data/PruebasImu/";
%name = "prueba2_1m_adelante.txt"
%name = "prueba2_1m_atras.txt"
%name = "prueba2_90_derecha.txt";
name = "prueba2_90_derecha.txt"
slct=3;

% it gets the acceleration file and selects the axis x=2,y=3,z=4
file_data= strcat(path,name);
acceleration=load(file_data);
num=size(acceleration);
t=acceleration(1:num,1);
ddx=acceleration(1:num,slct);
figure
plot(ddx)

% it calculates the integral of the acceleration to get the speed
dx=integral(num,t,ddx);
figure
plot(dx)

% it calculates the integral of the speed to get the position
x=integral(num-2,t,dx);
figure
plot(x)

