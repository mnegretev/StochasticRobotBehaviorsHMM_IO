%%clear;
%%load Datos;
t=linspace(-100,100,10000);
x=(training_distances(:,2));
z=(training_distances(:,1));
N=size(x,1);
xp=testing_distances(:,2);
y=testing_distances(:,1); 

 m= (     N*sum(x.*z) - sum(x)*sum(z)  )               / ( N*sum(x.*x)-(sum(x)*sum(x))   );
 b= (  (sum(z)*sum(x.*x))  -  ( sum(x.*x)*sum(x) ) )   / (N*sum(x.*x)- sum(x)*sum(x)   );
zp= m.*xp + b;
 e=abs(y.-zp);
 mincu=m.*t+b;
 
 figure
 subplot(2,1,1)
 plot(t,mincu);
 
 subplot(2,1,2)
 
 
 
 
 plot(e);
 
 