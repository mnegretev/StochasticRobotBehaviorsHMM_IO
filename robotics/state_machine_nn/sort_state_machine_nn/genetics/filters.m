t = 0:511;
ft = 7000;
f1 = 1500;
f2 = 3000;
fs = 16000;

x0 = zeros(1,100);
tono=cos(2*3.1416*ft/fs*t);
t = 0:31;
x1=cos(2*3.1416*f1/fs*t);
x2=cos(2*3.1416*f2/fs*t);

x= [x0 tono x2 x1 x2 x2 x1 x2 x1 x2 x1 x1 x2 x1 x1];
subplot(3,1,1);
plot(x);
%[B,A]=fir1(64,(ft+2000)/fs,'high');
B=fir1(64,(ft+2000)/fs,'high');
subplot(3,1,2);
A=1;
y=filter(B,A,x);
plot(y)
