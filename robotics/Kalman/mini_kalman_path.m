close all
clear all

N_steps= 200;
u_theta = [0, pi/4, 0, 0, 0, 0, -pi/4, 0, 0, 0, 0,pi/4, 0, 0, 0, 0, -pi/4, 0, 0, 0, 0,pi/4, 0, 0, 0, 0, -pi/4, 0, 0, 0, 0,pi/4, 0, 0, 0, 0, -pi/4, 0, 0, 0, 0,pi/4, 0, 0, 0, 0, -pi/4, 0, 0, 0, 0,pi/4, 0, 0, 0, 0, -pi/4, 0, 0, 0, 0,pi/4, 0, 0, 0, 0, -pi/4, 0, 0, 0, 0,pi/4, 0, 0, 0, 0, -pi/4, 0, 0, 0, 0,pi/4, 0, 0, 0, 0, -pi/4, 0, 0, 0, 0,pi/4, 0, 0, 0, 0, -pi/4, 0, 0, 0, 0, pi/4, 0, 0, 0, 0, -pi/4, 0, 0, 0, 0,pi/4, 0, 0, 0, 0, -pi/4, 0, 0, 0, 0,pi/4, 0, 0, 0, 0, -pi/4, 0, 0, 0, 0,pi/4, 0, 0, 0, 0, -pi/4, 0, 0, 0, 0,pi/4, 0, 0, 0, 0, -pi/4, 0, 0, 0, 0,pi/4, 0, 0, 0, 0, -pi/4, 0, 0, 0, 0,pi/4, 0, 0, 0, 0, -pi/4, 0, 0, 0, 0,pi/4, 0, 0, 0, 0, -pi/4, 0, 0, 0, 0,pi/4, 0, 0, 0, 0, -pi/4, 0, 0, 0, 0,pi/4, 0, 0, 0, 0, -pi/4, 0, 0, 0, 0,  ];

u_avance = .2; %%Avance fijo en cada 

des = .03;    %% Desviacion estandar  Del error de  movimiento
des_l = .01;  %% desviacion estandar del error lanmarks
media = 0;


%%%%%%%  Para calcular Q  %%%%%%%%%%
angle_real = [1:N_steps];
x = [1:N_steps];
y = [1:N_steps];

angle = [1:N_steps];
x_real = [1:N_steps];
y_real = [1:N_steps];

%% Valores iniciales

angle_real(1) = 0;
x_real(1) = 0;
y_real(1) = 0;

angle(1) = 0;
x(1)=0;
y(1)=0;

  
%%%%%%%%%%%     Para optener Q
for i = 2:N_steps

  angle_real(i) = angle_real(i-1) + u_theta(i) ;
  x_real(i) = x_real(i-1) + u_avance * cos( angle_real(i) );
  y_real(i) = y_real(i-1) + u_avance * sin( angle_real(i) );
  
  
  angle(i) = angle(i-1) + u_theta(i) ;
  x(i) =  x(i-1) + u_avance * cos( angle(i-1) + u_theta(i)  ) +(des.*randn() + media);
  y(i) =  y(i-1) + u_avance * sin( angle(i-1) + u_theta(i)  ) +(des.*randn() + media);
  
  x_error(i) = x(i) - x(i-1);
  y_error(i) = y(i) - y(i-1);
  angle_error(i) =  atan( (y(i)-y(i-1) ) / (x(i)-x(i-1)+.001)  ) ;
    
end


figure(1);
plot(x,y,'b');
title ("Pruebas para obtener Q (Rojo ideal/ Azul con ruido)");
xlabel ("x");
ylabel ("y");
hold on; 
plot(x_real,y_real,'r')
hold off; 
 
Q = [ var(x_error(2:end)), 0, 0 ;0, var(y_error(2:end)), 0; 0,0,var(angle_error(2:end))]

%%%%% Para obtener R

landmarks = [ .003*N_steps, .002*N_steps, .026*N_steps ;
              .0005*N_steps, .032*N_steps, .017*N_steps]

l_n = landmarks;

[ nada,n_radios] = size(landmarks)
radio = [1:n_radios]

x_z(1) = 0;
y_z(1) = 0;

for j = 2:N_steps
   for i = 1:n_radios
    l_n(1,i)=landmarks(1,i);
    l_n(2,i)=landmarks(2,i); 
   end
   
   for i = 1:n_radios
    rd(i) =   sqrt( ( l_n(1,i)+(des.*randn() + media) - x_real(j) )^2 + ( l_n(2,i) + (des.*randn() + media)- y_real(j) )^2 ) ;
   end
   
   a1 = l_n(2,2)-l_n(2,1);
   a2 = rd(2)^2 - rd(3)^2 - l_n(1,2)^2 + l_n(1,3)^2 - l_n(2,2)^2  + l_n(2,3)^2 ;
   a3 = l_n(2,3)-l_n(2,2);
   a4 = rd(1)^2 - rd(2)^2 - l_n(1,1)^2 + l_n(1,2)^2 - l_n(2,1)^2 + l_n(2,2)^2 ;
   a5 = l_n(1,3) - l_n(1,2);
   a6 = l_n(1,2) - l_n(1,1);  
   
   x_z(j) =  ( (a1 * a2) - (a3 * a4) ) / ( (2 * a5 * a1) - (2 * a6 * a3) );  
   y_z(j) =  ( (a6 * a2) - (a5 * a4) ) / ( (2 * a6 * a3) - (2 * a5 * a1) );  
   
   x_z_error(j) = x_z(j) - x_real(j);
   y_z_error(j) = y_z(j) - y_real(j);
   
   angle_z(j) = atan( (y_z(j)-y_real(j-1) ) / (x_z(j)-x_real(j-1)+.001)  ) ;
   
end

figure(2);
plot(x_z,y_z,'+r')
title ("Pruebas para obtener R");
xlabel ("x");
ylabel ("y");
hold on; 
plot(landmarks(1,:),landmarks(2,:),'*b')
hold off; 

R = [ var(x_z_error(2:end)), 0, 0 ;0, var(y_z_error(2:end)), 0; 0,0,var(angle_z(2:end)) ]

%%% FIltro de kalman


% Jacobiano de la funcion F
VF = [ 1, 0, -u_avance*sin(u_theta(i)); 
       0, 1,  u_avance*cos(u_theta(i));
       0, 0,  1]

% Matriz de predicciones
for i = 1:N_steps
  x_hat(:,:,i) = [0;0;u_theta(i)];
end

%% Matriz de covarianza
P = [0,0,0;0,0,0;0,0,0];

%% Jacobiano de la funcion H
VH = [1,0,0;0,1,0;0,0,1];

%%% Vector de comparacion
V = [0;0;0];

%% Kalman filter    
 
xx_real = [1:N_steps];
yy_real = [1:N_steps];

xx_real(1) = 0;
yy_real(1) = 0;

theta = [1:N_steps];
theta_k = [1:N_steps];

theta(1)= 0;
theta_k(1)= 0;

for i = 2:N_steps

theta(i) = theta(i-1) + u_theta(i);  
xx_real(i) = xx_real(i-1) + u_avance*cos( theta(i) ) + (des.*randn() + media);
yy_real(i) = yy_real(i-1) + u_avance*sin( theta(i) ) + (des.*randn() + media);

% Prediccion
theta_k(i) = theta_k(i-1) + u_theta(i);

x_hat(:,:,i) = [ x_hat(1,i-1) + u_avance*cos( theta_k(i) ) , x_hat(2,i-1)+ u_avance*sin( theta_k(i) ) ,0]'  ;
P = VF*P*VF'+Q;

%actualizacion o correccion

                 for j = 1:n_radios
                  rd(j) = sqrt( ( landmarks(1,j) - x_hat(1,:,i) )^2 + ( landmarks(2,j)- x_hat(2,:,i) )^2 ) ;
                 end
                 
                 a1 = l_n(2,2)-l_n(2,1);
                 a2 = rd(2)^2 - rd(3)^2 - l_n(1,2)^2 + l_n(1,3)^2 - l_n(2,2)^2  + l_n(2,3)^2 ;
                 a3 = l_n(2,3)-l_n(2,2);
                 a4 = rd(1)^2 - rd(2)^2 - l_n(1,1)^2 + l_n(1,2)^2 - l_n(2,1)^2 + l_n(2,2)^2 ;
                 a5 = l_n(1,3) - l_n(1,2);
                 a6 = l_n(1,2) - l_n(1,1); 
                                 
                 x_VHX =  ( (a1 * a2) - (a3 * a4) ) / ( (2 * a5 * a1) - (2 * a6 * a3) );  
                 y_VHX =  ( (a6 * a2) - (a5 * a4) ) / ( (2 * a6 * a3) - (2 * a5 * a1) );  
                 
                 
                 
                 for j = 1:n_radios
                  rd(j) = sqrt( ( landmarks(1,j)+(des_l.*randn() + media)- xx_real(i) )^2 + ( landmarks(2,j) +(des_l.*randn() + media)- yy_real(i) )^2 ) ;
                 end
                 
                 a1 = l_n(2,2)-l_n(2,1);
                 a2 = rd(2)^2 - rd(3)^2 - l_n(1,2)^2 + l_n(1,3)^2 - l_n(2,2)^2  + l_n(2,3)^2 ;
                 a3 = l_n(2,3)-l_n(2,2);
                 a4 = rd(1)^2 - rd(2)^2 - l_n(1,1)^2 + l_n(1,2)^2 - l_n(2,1)^2 + l_n(2,2)^2 ;
                 a5 = l_n(1,3) - l_n(1,2);
                 a6 = l_n(1,2) - l_n(1,1); 
                                 
                 x_z =  ( (a1 * a2) - (a3 * a4) ) / ( (2 * a5 * a1) - (2 * a6 * a3) );  
                 y_z =  ( (a6 * a2) - (a5 * a4) ) / ( (2 * a6 * a3) - (2 * a5 * a1) );  
                 
                 V(1,1)= x_z - x_VHX;
                 V(2,1)= y_z - y_VHX;
                 V(3,1)= 0 ;


S =  ( VH*P*VH')+R;
K = P*VH'*inv(S);
x_hat(:,:,i) = x_hat(:,:,i)+ K*(V );


P = P + K*S*K';

end

figure(3);
plot(xx_real,yy_real,'r')

title ("Azul prediccion / 'Rojo REAL'");
xlabel ("x");
ylabel ("y");
hold on; 
plot(x_hat(1,1,:),x_hat(2,1,:),'b')
plot(landmarks(1,:),landmarks(2,:),'*b')
hold off; 

       
