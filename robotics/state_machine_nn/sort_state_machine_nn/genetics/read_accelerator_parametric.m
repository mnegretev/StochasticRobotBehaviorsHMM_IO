
load ../data/sim_accelerator.txt
num=size(sim_accelerator)


ntr=1;

%num=10;
%for j=1:num
	%sim_accelerator(j,2)=1;
	%sim_accelerator(j,1)=j*2;
%end

t=sim_accelerator(1:num,1);
ddx=sim_accelerator(1:num,2);

figure
plot(ddx)

partial=0;

for j=1:num-ntr

	t1=t(j);
	t2=t(j+ntr);
	h=(t2-t1)/(ntr+1);

	ddx(j);
	ddx(j+ntr);
	suma = ddx(j) + ddx(j+ntr);
	for i=1:ntr-1
		ddx(j+i);
		suma=ddx(j+i)*2 + suma;
	end
	partial=(h * suma) + partial;
	dx(j)=partial;
end

figure
plot(dx)

partial=0;

for j=1:num-ntr-1

        t1=t(j);
        t2=t(j+ntr);
        h=(t2-t1)/(ntr+1);

        dx(j);
        dx(j+ntr);
        suma = dx(j) + dx(j+ntr);
        for i=1:ntr-1
                ddx(j+i);
                suma=ddx(j+i)*2 + suma;
        end

	partial=(h * suma) + partial;
	x(j)=partial;
end 
	
figure
plot(x)

	%ddx2=ddx(j+1)
	%ddx3=ddx(j+2)

	%t11=t1*t1
	%t12=t11*t1
	%t13=t12*t1

	%t3=t(j+2)

	%dx1=(t2-t1)*(ddx2+ddx1)/2
	%dx2=(t3-t2)*(ddx3+ddx2)/2
	%x1=(t2-t1)*(dx2+dx1)/2

	%a3 = (ddx2 - ddx1) / 6*(t2-t1)
	%a2 = (ddx1 - t1 * (ddx2 - ddx1))/2
	%a1 = dx1 - 2*a2*t1 - 3*a3*t11
	%a0 =  x1 - a1*t1 - a2*t12 - a3*t13

	%x(j) = a0 + a1*t1 + a2*t12 + a3*t13
	%xx(j) = x1;

%end

%figure
%plot(dx)

%figure
%plot(xx)

