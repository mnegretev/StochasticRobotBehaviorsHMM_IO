
t=linspace(-100,100,10000);
aux=0;
tru=1;
x=(training_distances(:,2));
z=(training_distances(:,1));
ordlag=13;
xlag=x(1);
zlag=z(1);
for n=2:ordlag

xlag=cat(2,xlag, x(floor((n/ordlag)*size(x,1) )));
zlag=cat(2,zlag, z(floor((n/ordlag)*size(z,1) )));
end

%xlag=[ x(1) x( floor ((2/5)*size(x,1)))  x(floor ((3/5)*size(x,1)))  x(floor ((4/5)*size(x,1)))  x(size(x,1))];
%zlag=[ z(1) z( floor ((2/5)*size(z,1)))  z(floor ((3/5)*size(z,1)))  z(floor ((4/5)*size(z,1)))  z(size(z,1))];
xtest=(testing_distances(:,2));
ztest=(testing_distances(:,1));



for k=1:size(x)
xbuena(tru)=x(k);
 
    for n=1:tru-1
        if xbuena(tru)==xbuena(n)
        tru--;
        k;
        break;
        end

    end
    ++tru;
end

x=xbuena;


aux=1;
for j=1:size(xlag,2)
for tru=1:size(t,2)
for m=1:size(xlag,2)
      if j==m
      aux=aux;
     
      end
      
      if (j!=m)
      aux= aux *   (      (t(tru)-xlag(m))/(xlag(j)-xlag(m))   );
      end
 
end
if aux > 1000
aux=1000;
end

if aux < -1000
aux=-1000;
end


l(j,tru)=aux;
aux=1;

end
end


aux=0;
for tru=1:size(t,2)
for j=1:size(xlag,2)
    aux+=zlag(j)*l(j,tru);
end
L(tru)=aux;
aux=0;
end

for n=1:size(xtest)
if xtest(n) >= 100
xtest(n)=100;
end

if xtest(n) <= -100
xtest(n)=-99.99;
end

e(n)=abs(ztest(n)-L(  round(50*xtest(n)+5000 ) ));

end
figure
subplot(2,1,1)
plot(t,L);

subplot(2,1,2)
plot(e)



