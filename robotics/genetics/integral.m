
% it calculates the integral using the trapezoidal function every two samples
function dx=integral(num,t,ddx)

        partial=0;
        for j=1:num-200

                %integration using the trapezoidal rule
                t1=t(j);
                t2=t(j+1);
                h=(t2-t1)/2;

                ddx(j);
                ddx(j+1);
                suma = ddx(j) + ddx(j+1);
                partial=(h * suma) + partial;
                dx(j)=partial;
        end


