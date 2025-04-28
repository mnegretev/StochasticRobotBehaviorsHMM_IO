K0 = 2292.2;
alpha = 75.63;
T = 0.001;
Vp = 1;
C1= 1/(2*T*alpha + 4);
C2 = K0*T*T;
C3 = 4 - 2*T*alpha;
t1 = 0.01;
Nt1 = t1/T;
tt = 0.3;
Ntt = tt/T;

for j=1:Ntt
   v(j)=0;
   tetha(j)=0;
end

for j=1:Nt1
   v(j)=1;
end

for j=3:Ntt
   tetha(j) = C1*( C2*(v(j)+2*v(j-1)+v(j)) + 8*tetha(j-1) - C3*tetha(j-2));
end

Nt=1:Ntt;
t = T * Nt;

figure
plot(t,tetha)
