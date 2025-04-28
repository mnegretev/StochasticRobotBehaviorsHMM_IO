%%Ejemplo Campos Potenciales
clear all
%%Datos
q0 = [1 ;1]; %%Posición inicial del robot
qobs = [2; 2]; %%Posición del centroide de un obstáculo
qdest = [5; 4]; %%Posición final deseada
%%Constantes
d0 = 5; 
e1 = 1;
eta = 2;
delta0 = 0.1; 
d1 = 10;

figure
title('Trayectoria de un robot usando "Campos Potenciales"')
xlabel('Posición en x')
ylabel('Posición en y')
xlim([0 6])
ylim([0 5])

hold on
plot(q0(1,1),q0(2,1),'o','LineWidth',2)%%Posición inicial
text(q0(1,1),q0(2,1),'Inicio','VerticalAlignment','bottom','HorizontalAlignment','right')
hold on
plot(qdest(1,1),qdest(2,1),'o','LineWidth',2)%%Posición final
text(qdest(1,1),qdest(2,1),'Final','VerticalAlignment','bottom','HorizontalAlignment','right')
hold on
plot(qobs(1,1),qobs(2,1),'o','LineWidth',2)%%Posición del centroide del obstáculo
text(qobs(1,1),qobs(2,1),'Obstáculo','VerticalAlignment','bottom','HorizontalAlignment','right')
  
while norm(q0-qdest) > 0.1 %%Tolerancia entre la distancia del robot y el destino
    
    %%Fuerza de atracción del robot al destino
    Fatr = e1*(q0-qdest);
    %%Fuerza de repulsión del robot al obstáculo
    magvobs = norm(q0-qobs);
    Frep = -eta * ( 1/magvobs - 1/d0)*(1/magvobs^2)*((q0-qobs)/magvobs);
    %%Fuerza total
    FT = Fatr + Frep;
    ft = FT/norm(FT);
    %%Cálculo de la siguiente posición del robot
    q1 = q0 - delta0*ft;
    hold on
    line([q0(1,1) q1(1,1)],[q0(2,1) q1(2,1)],'LineWidth',2,'Color','r')
    q0 = q1;
    
end