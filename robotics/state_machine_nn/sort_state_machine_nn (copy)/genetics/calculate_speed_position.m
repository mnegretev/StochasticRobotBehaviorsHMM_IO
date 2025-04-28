
% it calculates the speed and position from the acceleration 
%function speed_position=calculate_speed_position(file_data,slct)
function calculate_speed_position(file_data,slct,axis)

	% it gets the acceleration file and selects the axis x=2,y=3,z=4
	acceleration=load(file_data);
	num=size(acceleration);
	t=acceleration(200:num,1);
	ddx=acceleration(200:num,slct);
	figure
	subplot(4,1,1);
	plot(ddx)
	string=strcat('AXIS ',axis)
	title(string)
	xlabel('acceleration')
	m=mean(ddx(1:20));
	%ddx=ddx;
	ddx=ddx-m;
	N=10;
	ddx_f = filter(ones(1,N)/N, 1, ddx);

	f1 = 40;
	fs = 120;
	B=fir1(32,f1/fs,'high');
	A=1;
	%ddx_f=filter(B,A,ddx);


	%figure
	subplot(4,1,2);
	plot(ddx_f)
	xlabel('filtered acceleration')


	% it calculates the integral of the acceleration to get the speed
	dx=integral(num,t,ddx_f);
	%figure
	subplot(4,1,3);
	plot(dx)
	xlabel('velocity')

	% it calculates the integral of the speed to get the position
	num=num-2
	x=integral(num,t,dx);
	subplot(4,1,4);
	plot(x)
	xlabel('position')

	figure
	plot(t)
	%speed_position=[dx;x];

