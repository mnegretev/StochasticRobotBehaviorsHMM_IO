
%load ../data/accelerator.dat
tf=3;
num=100;
delta_t=tf/num;
xp=1;
yp=1;

ax0=0;
ax1=0;
ax2=(3*xp)/(tf*tf);
ax3= (-2*xp)/(tf*tf*tf);

ay0=0;
ay1=0;
ay2=(3*yp)/(tf*tf);
ay3= (-2*yp)/(tf*tf*tf);

i=0;
for j=1:num

	x(j) = ax0 + ax1*i + ax2*(i*i) + ax3*(i*i*i);
	y(j) = ay0 + ay1*i + ay2*(i*i) + ay3*(i*i*i);
	dx(j) = ax1 + 2*ax2*i + 3*ax3*(i*i);
	dy(j) = ay1 + 2*ay2*i + 3*ay3*(i*i);
	ddx(j) =  2*ax2 + 6*ax3*i;
	ddy(j) =  2*ay2 + 6*ay3*i;
	vect_time(j) = i;
	i= i+delta_t;

end

%vect_time(j) = i;


figure
plot(x)

figure
plot(dx)

figure
plot(ddx)

file_name = '../data/sim_accelerator.txt'
fileID = fopen('../data/sim_accelerator.txt','w');
%A = [vect_time ; ddx];
A = [vect_time ; ddx];
fprintf(fileID,'%f %f\n',A);
fclose(fileID);



