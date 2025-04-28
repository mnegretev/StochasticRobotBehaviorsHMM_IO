


%b     blue
%g     green
%r     red
%c     cyan
%m     magenta
%y     yellow
%k     black
%w     white

clear

disp("")
disp("")
disp("**************************************************")
disp ("RESULTS POTENTIAL BEHAVIOR")

load /home/biorobotica/data/data_5/fitness_average_potentials.dat
load /home/biorobotica/data/data_5/fitness_worst_potentials.dat
load /home/biorobotica/data/data_5/fitness_best_potentials.dat


s=size(fitness_best_potentials);
num_gen = s(1) 
num_gen_potentials = num_gen

i=1:s(:,1);
n=1;
i=n:s(:,1);
figure
%plot(i,fitness_average_potentials(i),'r+-',i,fitness_best_potentials(i),'kx-',i,fitness_worst_potentials(i),'b*-')
%xlabel("Generations Worst, Average (red) and Best Potentials")
plot(i,fitness_average_potentials(i),'r+-',i,fitness_best_potentials(i),'kx-')
xlabel("Generations Worst and Average (red) Potentials")
ylabel("Fitness")


[best_value_potentials index]=max(fitness_best_potentials(n:num_gen))
n+index-1
%mean_best= mean(fitness_best_potentials(n:num_gen))
mean_best= fitness_best_potentials(num_gen)
std_best= std(fitness_best_potentials(n:num_gen))

[average_value index]=max(fitness_average_potentials(n:num_gen))
n+index-1
%mean_average=mean(fitness_average_potentials(n:num_gen))
mean_average=fitness_average_potentials(num_gen)
std_average=std(fitness_average_potentials(n:num_gen))

[worst_value index]=max(fitness_worst_potentials(n:num_gen))
n+index-1
mean_worst=mean(fitness_worst_potentials(n:num_gen))
std_worst=std(fitness_worst_potentials(n:num_gen))

%bests(1)=best_value_potentials;
bests(1)=fitness_best_potentials(s(:,1));
%bests_no_memory(1)=best_value_potentials;
bests_no_memory(1)=fitness_best_potentials(num_gen);
%average(1)=average_value;
average(1)=mean_average;
worst(1)=worst_value;
mean_bests(1)=mean_best;



disp("")
disp("")
disp("**************************************************")
disp ("RESULTS FSM BEHAVIOR")


load /home/biorobotica/data/data_6/fitness_average_fsm.dat
load /home/biorobotica/data/data_6/fitness_worst_fsm.dat
load /home/biorobotica/data/data_6/fitness_best_fsm.dat

s=size(fitness_best_fsm);
num_gen = s(1) 
num_gen_fsm = num_gen
  
i=1:s(:,1);
n=1;
i=n:s(:,1);
figure
%plot(i,fitness_average_fsm(i),'r+-',i,fitness_best_fsm(i),'kx-',i,fitness_worst_fsm(i),'b*-')
%xlabel("Generations Worst, Average (red) and Best FSM")
plot(i,fitness_average_fsm(i),'r+-',i,fitness_best_fsm(i),'kx-')
xlabel("Generations Average (red) and Best FSM")
ylabel("Fitness")


[best_value_fsm index]=max(fitness_best_fsm(n:num_gen))
n+index-1
mean_best= mean(fitness_best_fsm(n:num_gen))
%mean_best= fitness_best_fsm(num_gen)
std_best= std(fitness_best_fsm(n:num_gen))

[average_value index]=max(fitness_average_fsm(n:num_gen))
n+index-1
mean_average=mean(fitness_average_fsm(n:num_gen))
%mean_average=fitness_average_fsm(num_gen)
std_average=std(fitness_average_fsm(n:num_gen))

[worst_value index]=max(fitness_worst_fsm(n:num_gen))
n+index-1
mean_worst=mean(fitness_worst_fsm(n:num_gen))
std_worst=std(fitness_worst_fsm(n:num_gen))

bests(2)=best_value_fsm;
%bests(2)=fitness_best_fsm(num_gen);
bests_memory(1)=best_value_fsm;
%bests_memory(1)=fitness_best_fsm(num_gen);
average(2)=average_value;
%average(2)=mean_average;
worst(2)=worst_value;
mean_bests(2)=mean_best;


disp("")
disp("")
disp("**************************************************")
disp ("RESULTS HMM BEHAVIOR")


load /home/biorobotica/data/data_5/fitness_average_hmm.dat
load /home/biorobotica/data/data_5/fitness_worst_hmm.dat
load /home/biorobotica/data/data_5/fitness_best_hmm.dat

s=size(fitness_best_hmm);
num_gen = s(1) 
num_gen_hmm = num_gen
  
i=1:s(:,1);
n=1;
i=n:s(:,1);
figure
%plot(i,fitness_average_hmm(i),'r+-',i,fitness_best_hmm(i),'kx-',i,fitness_worst_hmm(i),'b*-')
%xlabel("Generations Worst, Average (red) and Best HMM")
plot(i,fitness_average_hmm(i),'r+-',i,fitness_best_hmm(i),'kx-')
xlabel("Generations Average (red) and Best HMM")
ylabel("Fitness")


[best_value_hmm index]=max(fitness_best_hmm(n:num_gen))
n+index-1
mean_best= mean(fitness_best_hmm(n:num_gen))
std_best= std(fitness_best_hmm(n:num_gen))

[average_value index]=max(fitness_average_hmm(n:num_gen))
n+index-1
%mean_average=mean(fitness_average_hmm(n:num_gen))
mean_average=fitness_average_hmm(num_gen)
std_average=std(fitness_average_hmm(n:num_gen))

[worst_value index]=max(fitness_worst_hmm(n:num_gen))
n+index-1
mean_worst=mean(fitness_worst_hmm(n:num_gen))
std_worst=std(fitness_worst_hmm(n:num_gen))

%bests(3)=best_value_hmm;
bests(3)=fitness_best_hmm(num_gen);
%bests_memory(2)=best_value_hmm;
bests_memory(2)=fitness_best_hmm(num_gen);
%average(3)=average_value;
average(3)=mean_average;
worst(3)=worst_value;
mean_bests(3)=mean_best;



disp("")
disp("")
disp("**************************************************")
disp ("RESULTS REACTIVE BEHAVIOR")

load /home/biorobotica/data/data_5/fitness_average_reactive.dat
load /home/biorobotica/data/data_5/fitness_worst_reactive.dat
load /home/biorobotica/data/data_5/fitness_best_reactive.dat


s=size(fitness_best_reactive);
num_gen = s(1)
num_gen_reactive = num_gen

i=1:s(:,1);
n=1;
i=n:s(:,1);
figure
%plot(i,fitness_average_reactive(i),'r+-',i,fitness_best_reactive(i),'kx-',i,fitness_worst_reactive(i),'b*-')
%xlabel("Generations Worst, Average (red) and Best Reactive")
plot(i,fitness_average_reactive(i),'r+-',i,fitness_best_reactive(i),'kx-')
xlabel("Generations Average (red) and Best Reactive")
ylabel("Fitness")


[best_value_reactive index]=max(fitness_best_reactive(n:num_gen))
n+index-1
mean_best= mean(fitness_best_reactive(n:num_gen))
std_best= std(fitness_best_reactive(n:num_gen))

[average_value index]=max(fitness_average_reactive(n:num_gen))
n+index-1
%mean_average=mean(fitness_average_reactive(n:num_gen))
mean_average=fitness_average_reactive(num_gen)
std_average=std(fitness_average_reactive(n:num_gen))

[worst_value index]=max(fitness_worst_reactive(n:num_gen))
n+index-1
mean_worst=mean(fitness_worst_reactive(n:num_gen))
std_worst=std(fitness_worst_reactive(n:num_gen))

%bests(4)=best_value_reactive;
bests(4)=fitness_best_reactive(num_gen);
%bests_no_memory(2)=best_value_reactive;
bests_no_memory(2)=fitness_best_reactive(num_gen);

%average(2)=average_value;
average(4)=mean_average;
worst(4)=worst_value;
mean_bests(4)=mean_best;




disp("")
disp("")
disp("**************************************************")
disp ("BEST VALUES BEHAVIORS")

num_gen_potentials
best_value_potentials
num_gen_fsm
best_value_fsm
num_gen_hmm
best_value_hmm


%bests
[s_bests, ind] = sort(bests)
[best_value_best index]=max(bests)
figure
bar(s_bests)
var = sprintf("B. %d   ",ind)
xlabel(var)
ylabel("Behaviors Fitness Best")


%mean_bests
[s_mean_bests, ind] = sort(mean_bests)
[best_value_mean_best index]=max(mean_bests)
[s_average, ind] = sort(average)
[best_value_average index]=max(average)
figure
bar(s_mean_bests)
var = sprintf("B. %d   ",ind)
xlabel(var)
ylabel("Behaviors Average Fitness")


