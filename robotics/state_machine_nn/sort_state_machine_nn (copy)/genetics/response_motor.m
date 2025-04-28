K0 = 2292.2;
alpha = 75.63;
T1 = 0.03;
Vp = 1;
C1= (Vp*K0)/(alpha.^2);
C2 = alpha*T1;
t = 0:.01:0.1;
t_alpha= alpha*t;
e1 = 2.718281828 .^ C2;
tetha = C1*(e1 -1 + 2.718281828 .^(-t_alpha) * (1 - e1));
plot(t,tetha)
