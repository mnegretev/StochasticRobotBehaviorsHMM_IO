


%b     blue
%g     green
%r     red
%c     cyan
%m     magenta
%y     yellow
%k     black
%w     white



disp("")
disp("")
disp("**************************************************")
disp ("RESULTS POTENTIAL BEHAVIOR")

load /home/biorobotica/data/data_15/fitness_average_potentials.dat
load /home/biorobotica/data/data_15/fitness_worst_potentials.dat
load /home/biorobotica/data/data_15/fitness_best_potentials.dat


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
mean_best= mean(fitness_best_potentials(n:num_gen))
std_best= std(fitness_best_potentials(n:num_gen))

[average_value index]=max(fitness_average_potentials(n:num_gen))
n+index-1
mean_average=mean(fitness_average_potentials(n:num_gen))
std_average=std(fitness_average_potentials(n:num_gen))

[worst_value index]=max(fitness_worst_potentials(n:num_gen))
n+index-1
mean_worst=mean(fitness_worst_potentials(n:num_gen))
std_worst=std(fitness_worst_potentials(n:num_gen))

bests(1)=best_value_potentials;
bests_no_memory(1)=best_value_potentials;
average(1)=average_value;
worst(1)=worst_value;
mean_bests(1)=mean_best;



disp("")
disp("")
disp("**************************************************")
disp ("RESULTS REACTIVE BEHAVIOR")

load /home/biorobotica/data/data_4/fitness_average_reactive.dat
load /home/biorobotica/data/data_4/fitness_worst_reactive.dat
load /home/biorobotica/data/data_4/fitness_best_reactive.dat


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
mean_average=mean(fitness_average_reactive(800:num_gen))
std_average=std(fitness_average_reactive(n:num_gen))

[worst_value index]=max(fitness_worst_reactive(n:num_gen))
n+index-1
mean_worst=mean(fitness_worst_reactive(n:num_gen))
std_worst=std(fitness_worst_reactive(n:num_gen))

bests(2)=best_value_reactive;
bests_no_memory(2)=best_value_reactive;
%average(2)=average_value;
average(2)=mean_average;
worst(2)=worst_value;
mean_bests(2)=mean_best;


disp("")
disp("")
disp("**************************************************")
disp ("RESULTS REACTIVE STOCHASTIC BEHAVIOR")


load /home/biorobotica/data/data_15/fitness_average_reactive_stochastic.dat
load /home/biorobotica/data/data_15/fitness_worst_reactive_stochastic.dat
load /home/biorobotica/data/data_15/fitness_best_reactive_stochastic.dat

s=size(fitness_best_reactive_stochastic);
num_gen = s(1)
num_gen_reactive_stochastic = num_gen
  
i=1:s(:,1);
n=1;
i=n:s(:,1);
figure
%plot(i,fitness_average_reactive_stochastic(i),'r+-',i,fitness_best_reactive_stochastic(i),'kx-',i,fitness_worst_reactive_stochastic(i),'b*-')
%xlabel("Generations Worst, Average (red) and Best Reactive-Stochastic")
plot(i,fitness_average_reactive_stochastic(i),'r+-',i,fitness_best_reactive_stochastic(i),'kx-')
xlabel("Generations Average (red) and Best Reactive-Stochastic")
ylabel("Fitness")


[best_value_reactive_stochastic index]=max(fitness_best_reactive_stochastic(n:num_gen))
n+index-1
mean_best= mean(fitness_best_reactive_stochastic(n:num_gen))
std_best= std(fitness_best_reactive_stochastic(n:num_gen))

[average_value index]=max(fitness_average_reactive_stochastic(n:num_gen))
n+index-1
mean_average=mean(fitness_average_reactive_stochastic(n:num_gen))
std_average=std(fitness_average_reactive_stochastic(n:num_gen))

[worst_value index]=max(fitness_worst_reactive_stochastic(n:num_gen))
n+index-1
mean_worst=mean(fitness_worst_reactive_stochastic(n:num_gen))
std_worst=std(fitness_worst_reactive_stochastic(n:num_gen))

bests(3)=best_value_reactive_stochastic;
bests_no_memory(3)=best_value_reactive_stochastic;
average(3)=average_value;
worst(3)=worst_value;
mean_bests(3)=mean_best;


disp("")
disp("")
disp("**************************************************")
disp ("RESULTS FSM BEHAVIOR")


load /home/biorobotica/data/data_4/fitness_average_fsm.dat
load /home/biorobotica/data/data_4/fitness_worst_fsm.dat
load /home/biorobotica/data/data_4/fitness_best_fsm.dat

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
std_best= std(fitness_best_fsm(n:num_gen))

[average_value index]=max(fitness_average_fsm(n:num_gen))
n+index-1
mean_average=mean(fitness_average_fsm(n:num_gen))
std_average=std(fitness_average_fsm(n:num_gen))

[worst_value index]=max(fitness_worst_fsm(n:num_gen))
n+index-1
mean_worst=mean(fitness_worst_fsm(n:num_gen))
std_worst=std(fitness_worst_fsm(n:num_gen))

bests(4)=best_value_fsm;
bests_memory(1)=best_value_fsm;
average(4)=average_value;
worst(4)=worst_value;
mean_bests(4)=mean_best;


disp("")
disp("")
disp("**************************************************")
disp ("RESULTS FSM STOCHASTIC BEHAVIOR")

load /home/biorobotica/data/data_15/fitness_average_fsm_st.dat
load /home/biorobotica/data/data_15/fitness_worst_fsm_st.dat
load /home/biorobotica/data/data_15/fitness_best_fsm_st.dat


s=size(fitness_best_fsm_st);
s_st=s;
num_gen = s(1)
num_gen_fsm_st = num_gen
  
i=1:s(:,1);
n=1;
i=n:s(:,1);
figure
%plot(i,fitness_average_fsm_st(i),'r+-',i,fitness_best_fsm_st(i),'kx-',i,fitness_worst_fsm_st(i),'b*-')
%xlabel("Generations Worst, Average (red) and Best FSM-STOCHASTIC")
plot(i,fitness_average_fsm_st(i),'r+-',i,fitness_best_fsm_st(i),'kx-')
xlabel("Generations Average (red) and Best FSM-STOCHASTIC")
ylabel("Fitness")


[best_value_fsm_st index]=max(fitness_best_fsm_st(n:num_gen))
n+index-1
mean_best= mean(fitness_best_fsm_st(n:num_gen))
std_best= std(fitness_best_fsm_st(n:num_gen))

[average_value index]=max(fitness_average_fsm_st(n:num_gen))
n+index-1
mean_average=mean(fitness_average_fsm_st(n:num_gen))
std_average=std(fitness_average_fsm_st(n:num_gen))

[worst_value index]=max(fitness_worst_fsm_st(n:num_gen))
n+index-1
mean_worst=mean(fitness_worst_fsm_st(n:num_gen))
std_worst=std(fitness_worst_fsm_st(n:num_gen))


bests(5)=best_value_fsm_st;
bests_memory(2)=best_value_fsm_st;
average(5)=average_value;
worst(5)=worst_value;
mean_bests(5)=mean_best;

disp("")
disp("")
disp("**************************************************")
disp ("RESULTS HMM BEHAVIOR")


load /home/biorobotica/data/data_15/fitness_average_hmm.dat
load /home/biorobotica/data/data_15/fitness_worst_hmm.dat
load /home/biorobotica/data/data_15/fitness_best_hmm.dat

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
mean_average=mean(fitness_average_hmm(n:num_gen))
std_average=std(fitness_average_hmm(n:num_gen))

[worst_value index]=max(fitness_worst_hmm(n:num_gen))
n+index-1
mean_worst=mean(fitness_worst_hmm(n:num_gen))
std_worst=std(fitness_worst_hmm(n:num_gen))

bests(6)=best_value_hmm;
bests_memory(3)=best_value_hmm;
average(6)=average_value;
worst(6)=worst_value;
mean_bests(6)=mean_best;


disp("")
disp("")
disp("**************************************************")
disp ("RESULTS NN BEHAVIOR DETERMINISTIC OUTPUTS")


load /home/biorobotica/data/data_4/fitness_average_nn.dat
load /home/biorobotica/data/data_4/fitness_worst_nn.dat
load /home/biorobotica/data/data_4/fitness_best_nn.dat

s=size(fitness_best_nn);
num_gen = s(1)
num_gen_nn = num_gen

i=1:s(:,1);
n=1;
i=n:s(:,1);
figure
%plot(i,fitness_average_nn(i),'r+-',i,fitness_best_nn(i),'kx-',i,fitness_worst_nn(i),'b*-')
%xlabel("Generations Worst, Average (red) and Best NN")
plot(i,fitness_average_nn(i),'r+-',i,fitness_best_nn(i),'kx-')
xlabel("Generations Average (red) and Best NN")
ylabel("Fitness")


[best_value_nn index]=max(fitness_best_nn(n:num_gen))
n+index-1
mean_best= mean(fitness_best_nn(n:num_gen))
std_best= std(fitness_best_nn(n:num_gen))

[average_value index]=max(fitness_average_nn(n:num_gen))
n+index-1
mean_average=mean(fitness_average_nn(n:num_gen))
std_average=std(fitness_average_nn(n:num_gen))

[worst_value index]=max(fitness_worst_nn(n:num_gen))
n+index-1
mean_worst=mean(fitness_worst_nn(n:num_gen))
std_worst=std(fitness_worst_nn(n:num_gen))



bests(7)=best_value_nn;
bests_no_memory(4)=best_value_nn;
average(7)=average_value;
worst(7)=worst_value;
mean_bests(7)=mean_best;



disp("")
disp("")
disp("**************************************************")
disp ("RESULTS NN BEHAVIOR STOCHASTIC OUTPUTS")


load /home/biorobotica/data/data_15/fitness_average_nn_st.dat
load /home/biorobotica/data/data_15/fitness_worst_nn_st.dat
load /home/biorobotica/data/data_15/fitness_best_nn_st.dat

s=size(fitness_best_nn_st);
num_gen = s(1) 
num_gen_nn_st = num_gen

i=1:s(:,1);
n=1;
i=n:s(:,1);
figure
%plot(i,fitness_average_nn_st(i),'r+-',i,fitness_best_nn_st(i),'kx-',i,fitness_worst_nn_st(i),'b*-')
%xlabel("Generations Worst, Average (red) and Best NN-ST")
plot(i,fitness_average_nn_st(i),'r+-',i,fitness_best_nn_st(i),'kx-')
xlabel("Generations Average (red) and Best NN-ST")
ylabel("Fitness")


[best_value_nn_st index]=max(fitness_best_nn_st(n:num_gen))
n+index-1
mean_best= mean(fitness_best_nn_st(n:num_gen))
std_best= std(fitness_best_nn_st(n:num_gen))

[average_value index]=max(fitness_average_nn_st(n:num_gen))
n+index-1
mean_average=mean(fitness_average_nn_st(n:num_gen))
std_average=std(fitness_average_nn_st(n:num_gen))

[worst_value index]=max(fitness_worst_nn_st(n:num_gen))
n+index-1
mean_worst=mean(fitness_worst_nn_st(n:num_gen))
std_worst=std(fitness_worst_nn_st(n:num_gen))

bests(8)=best_value_nn_st;
bests_no_memory(5)=best_value_nn_st;
average(8)=average_value;
worst(8)=worst_value;
mean_bests(8)=mean_best;

disp("")
disp("")
disp("**************************************************")
disp ("RESULTS RNN BEHAVIOR DETERMINISTIC OUTPUTS")


load /home/biorobotica/data/data_4/fitness_average_rnn.dat
load /home/biorobotica/data/data_4/fitness_worst_rnn.dat
load /home/biorobotica/data/data_4/fitness_best_rnn.dat

s=size(fitness_best_rnn);
num_gen = s(1)
num_gen_rnn = num_gen

i=1:s(:,1);
n=1;
i=n:s(:,1);
figure
%plot(i,fitness_average_rnn(i),'r+-',i,fitness_best_rnn(i),'kx-',i,fitness_worst_rnn(i),'b*-')
%xlabel("Generations Worst, Average (red) and Best RNN")
plot(i,fitness_average_rnn(i),'r+-',i,fitness_best_rnn(i),'kx-')
xlabel("Generations Average (red) and Best RNN")
ylabel("Fitness")


[best_value_rnn index]=max(fitness_best_rnn(n:num_gen))
n+index-1
mean_best= mean(fitness_best_rnn(n:num_gen))
std_best= std(fitness_best_rnn(n:num_gen))

[average_value index]=max(fitness_average_rnn(n:num_gen))
n+index-1
%mean_average=mean(fitness_average_rnn(n:num_gen))
mean_average=mean(fitness_average_rnn(800:num_gen))
std_average=std(fitness_average_rnn(n:num_gen))

[worst_value index]=max(fitness_worst_rnn(n:num_gen))
n+index-1
mean_worst=mean(fitness_worst_rnn(n:num_gen))
std_worst=std(fitness_worst_rnn(n:num_gen))

bests(9)=best_value_rnn;
bests_memory(4)=best_value_rnn;
%average(9)=average_value;
average(9)=mean_average;
worst(9)=worst_value;
mean_bests(9)=mean_best;

disp("")
disp("")
disp("**************************************************")
disp ("RESULTS RNN BEHAVIOR STOCHASTIC OUTPUTS")


load /home/biorobotica/data/data_4/fitness_average_rnn_st.dat
load /home/biorobotica/data/data_4/fitness_worst_rnn_st.dat
load /home/biorobotica/data/data_4/fitness_best_rnn_st.dat

s=size(fitness_best_rnn_st);
num_gen = s(1) 
num_gen_rnn_st = num_gen

i=1:s(:,1);
n=1;
i=n:s(:,1);
figure
%plot(i,fitness_average_rnn_st(i),'r+-',i,fitness_best_rnn_st(i),'kx-',i,fitness_worst_rnn_st(i),'b*-')
%xlabel("Generations Worst, Average (red) and Best RNN-ST")
plot(i,fitness_average_rnn_st(i),'r+-',i,fitness_best_rnn_st(i),'kx-')
xlabel("Generations Average (red) and Best RNN-ST")
ylabel("Fitness")


[best_value_rnn_st index]=max(fitness_best_rnn_st(n:num_gen))
n+index-1
mean_best= mean(fitness_best_rnn_st(n:num_gen))
std_best= std(fitness_best_rnn_st(n:num_gen))

[average_value index]=max(fitness_average_rnn_st(n:num_gen))
n+index-1
%average_value = fitness_average_rnn_st(num_gen)
%mean_average=mean(fitness_average_rnn_st(n:num_gen))
mean_average=mean(fitness_average_rnn_st(2000:num_gen))
std_average=std(fitness_average_rnn_st(n:num_gen))

[worst_value index]=max(fitness_worst_rnn_st(n:num_gen))
n+index-1
mean_worst=mean(fitness_worst_rnn_st(n:num_gen))
std_worst=std(fitness_worst_rnn_st(n:num_gen))


bests(10)=best_value_rnn_st;
bests_memory(5)=best_value_rnn_st;
%average(10)=average_value;
average(10)=mean_average;
worst(10)=worst_value;
mean_bests(10)=mean_best;



disp("")
disp("")
disp("**************************************************")
disp ("RESULTS MDP BEHAVIOR")

load /home/biorobotica/data/data_3/fitness_average_mdp.dat
load /home/biorobotica/data/data_3/fitness_worst_mdp.dat
load /home/biorobotica/data/data_3/fitness_best_mdp.dat

%load /home/biorobotica/data/data_15/fitness_average_mdp.dat
%load /home/biorobotica/data/data_15/fitness_worst_mdp.dat
%load /home/biorobotica/data/data_15/fitness_best_mdp.dat

s=size(fitness_best_mdp);
num_gen = s(1)
num_gen_mdp = num_gen

i=1:s(:,1);
n=1;
i=n:s(:,1);
figure
%plot(i,fitness_average_mdp(i),'r+-',i,fitness_best_mdp(i),'kx-',i,fitness_worst_mdp(i),'b*-')
%xlabel("Generations Worst, Average (red) and Best MDP")
plot(i,fitness_average_mdp(i),'r+-',i,fitness_best_mdp(i),'kx-')
xlabel("Generations Average (red) and Best MDP")
ylabel("Fitness")


[best_value_mdp index]=max(fitness_best_mdp(n:num_gen))
n+index-1
mean_best= mean(fitness_best_mdp(n:num_gen))
std_best= std(fitness_best_mdp(n:num_gen))

[average_value index]=max(fitness_average_mdp(n:num_gen))
n+index-1
mean_average=mean(fitness_average_mdp(n:num_gen))
std_average=std(fitness_average_mdp(n:num_gen))

[worst_value index]=max(fitness_worst_mdp(n:num_gen))
n+index-1
mean_worst=mean(fitness_worst_mdp(n:num_gen))
std_worst=std(fitness_worst_mdp(n:num_gen))


bests(11)=best_value_mdp;
bests_memory(6)=best_value_mdp;
average(11)=average_value;
worst(11)=worst_value;
mean_bests(11)=mean_best;


%disp("")
%disp("")
%disp("**************************************************")
%disp ("RESULTS 5 LAYERS RNN_ST BEHAVIOR")

%fitness_average_rnn_st_layers=load("/home/biorobotica/data/data_15/fitness_average_rnn_st.dat");
%fitness_worst_rnn_st_layers=load("/home/biorobotica/data/data_15/fitness_worst_rnn_st.dat");
%fitness_best_rnn_st_layers=load("/home/biorobotica/data/data_15/fitness_best_rnn_st.dat");

%s=size(fitness_best_rnn_st_layers);
%num_gen = s(1)
%num_gen_rnn_st_layers = num_gen

%i=1:s(:,1);
%n=1;
%i=n:s(:,1);
%figure
%plot(i,fitness_average_rnn_st_layers(i),'r+-',i,fitness_best_rnn_st_layers(i),'kx-',i,fitness_worst_rnn_st_layers(i),'b*-')
%xlabel("Generations Worst, Average (red) and Best RNN-ST-LAYERS")
%plot(i,fitness_average_rnn_st_layers(i),'r+-',i,fitness_best_rnn_st_layers(i),'kx-')
%xlabel("Generations Average (red) and Best RNN-ST-LAYERS")
%ylabel("Fitness")


%[best_value_rnn_st_layers index]=max(fitness_best_rnn_st_layers(n:num_gen))
%n+index-1
%mean_best= mean(fitness_best_rnn_st_layers(n:num_gen))
%std_best= std(fitness_best_rnn_st_layers(n:num_gen))

%[average_value index]=max(fitness_average_rnn_st_layers(n:num_gen))
%n+index-1
%mean_average=mean(fitness_average_rnn_st_layers(n:num_gen))
%std_average=std(fitness_average_rnn_st_layers(n:num_gen))

%[worst_value index]=max(fitness_worst_rnn_st_layers(n:num_gen))
%n+index-1
%mean_worst=mean(fitness_worst_rnn_st_layers(n:num_gen))
%std_worst=std(fitness_worst_rnn_st_layers(n:num_gen))


%bests(12)=best_value_rnn_st_layers;
%average(12)=average_value;
%worst(12)=worst_value;
%mean_bests(12)=mean_best;





disp("")
disp("")
disp("**************************************************")
disp ("BEST VALUES BEHAVIORS")

num_gen_potentials
best_value_potentials
num_gen_reactive
best_value_reactive
num_gen_reactive_stochastic
best_value_reactive_stochastic
num_gen_fsm
best_value_fsm
num_gen_fsm_st
best_value_fsm_st
num_gen_hmm
best_value_hmm
num_gen_nn
best_value_nn
num_gen_nn_st
best_value_nn_st
num_gen_rnn
best_value_rnn
num_gen_rnn_st
best_value_rnn_st
num_gen_mdp
best_value_mdp
num_gen_rnn_st
%%best_value_rnn_st
%num_gen_rnn_st_layers
%best_value_rnn_st_layers


i=1:s_st(:,1);

%figure
%plot(i,fitness_best_reactive(i),'r',i,fitness_best_reactive_stochastic(i),'k',i,fitness_best_fsm(i),'b', fitness_best_fsm_st(i),'g',i,fitness_best_hmm(i),'k--',i,fitness_best_nn(i),'r--', fitness_best_nn_st(i),'r--',i,fitness_best_rnn(i),'b--',i,fitness_best_rnn_st(i),'r')
% xlabel("Generations best Reactive (r), Reactive-ST (k), FSM (b), FMS-ST (g), HMM (k--), NN (r--), NN-ST (r--), RNN (b--), RNN-ST (r) ")
%ylabel("Fitness")

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
%figure
%bar(s_mean_bests)
%var = sprintf("B. %d   ",ind)
%xlabel(var)
%ylabel("Behaviors Mean Fitness Best")



%average
[s_average, ind] = sort(average)
[best_value_average index]=max(average)
figure
bar(s_average)
var = sprintf("B. %d   ",ind)
xlabel(var)
ylabel("Behaviors Average Fitness")


[s_bests, ind] = sort(bests_no_memory)
[best_value_best index]=max(bests_no_memory)
figure
bar(s_bests)
NM=["POT";"LZ";"LZS";"NN";"NNS"]
var = sprintf("%s            %s         %s         %s           %s",NM(ind(1),:),NM(ind(2),:),NM(ind(3),:),NM(ind(4),:),NM(ind(5),:))
xlabel(var)
ylabel("Behaviors Fitness Best No Memory")

[s_bests, ind] = sort(bests_memory)
[best_value_best index]=max(bests_memory)
figure
bar(s_bests)
M=["FSM";"FSMS";"HMM";"RNN";"RNNS";"MDP"]
var = sprintf("%s       %s         %s       %s        %s     %s",M(ind(1),:),M(ind(2),:),M(ind(3),:),M(ind(4),:),M(ind(5),:),M(ind(6),:))
xlabel(var)
ylabel("Behaviors Fitness Best Memory")



%worst
%[s_worst, ind] = sort(worst)
%[best_value_worst index]=max(worst)
%figure
%bar(s_worst)
%var = sprintf("B. %d   ",ind)
%xlabel(var)
%ylabel("Behaviors Worst Fitness")


%if (num_gen_reactive < num_gen_reactive_stochastic) s=size(fitness_best_reactive);
%else s=size(fitness_best_reactive_stochastic);
%endif
s=size(fitness_best_reactive);
i=1:s(:,1);
s=size(fitness_best_reactive_stochastic);
j=1:s(:,1);
figure
plot(i,fitness_best_reactive(i),'r+-',j,fitness_best_reactive_stochastic(j),'kx-')
xlabel("Generations Best Reactive (red) and Best Reactive Stochastic")
ylabel("Fitness")


%if (num_gen_fsm < num_gen_fsm) s=size(fitness_best_fsm);
%else s=size(fitness_best_fsm_st);
%endif
s=size(fitness_best_fsm);
i=1:s(:,1);
s=size(fitness_best_fsm_st);
j=1:s(:,1);
figure
plot(i,fitness_best_fsm(i),'r+-',j,fitness_best_fsm_st(j),'kx-')
xlabel("Generations Best FSM (red) and Best FSM-ST")
ylabel("Fitness")


%if (num_gen_nn_st < num_gen_nn) s=size(fitness_best_nn_st);
%else s=size(fitness_best_nn);
%endif
s=size(fitness_best_nn_st)
i=1:s(:,1);
s=size(fitness_best_nn);
j=1:s(:,1);
figure
plot(i,fitness_best_nn_st(i),'r+-',j,fitness_best_nn(j),'kx-')
xlabel("Generations Best NN-ST (red) and Best NN")
ylabel("Fitness")


%if (num_gen_rnn_st < num_gen_rnn) s=size(fitness_best_rnn_st);
%else s=size(fitness_best_rnn);
%endif
s=size(fitness_best_rnn_st);
i=1:s(:,1);
s=size(fitness_best_rnn);
j=1:s(:,1);
figure
plot(i,fitness_best_rnn_st(i),'r+-',j,fitness_best_rnn(j),'kx-')
xlabel("Generations Best RNN-ST (red) and Best RNN")
ylabel("Fitness")


%if (num_gen_hmm < num_gen_mdp) s=size(fitness_best_hmm);
%else s=size(fitness_best_mdp);
%endif
s_mdp=size(fitness_best_mdp);
s_hmm=size(fitness_best_hmm);
k = s_mdp(1):s_hmm(1);
%last=fitness_best_mdp(s_mdp(1));
last=best_value_mdp;
fitness_best_mdp(k)=last;

%s=size(fitness_best_hmm);
i=1:s_hmm(:,1);
%s=size(fitness_best_mdp);
j=1:s_hmm(:,1);

%fitness_best_mdp(size(fitness_best_mdp):size(fitness_best_hmm))=fitness_best_mdp(size(fitness_best_mdp));

figure
plot(i,fitness_best_hmm(i),'r+-',j,fitness_best_mdp(j),'kx-')
xlabel("Generations Best HMM (red) and Best MDP")
ylabel("Fitness")


load /home/biorobotica/data/data_15/fitness_best_mdp.dat
figure
plot(fitness_best_mdp)
xlabel("Generations Best MDP 4")
ylabel("Fitness")
[best_value_mdp index]=max(fitness_best_mdp)



i=1:1000;
%i=i:num_gen_fsm;
j=1:1000;
%j=1:num_gen_hmm;
k=1:1000;
%k=1:num_gen_potentials;

figure
plot(k,fitness_average_potentials(k),'r+-',k,fitness_best_potentials(k),'kx-')
%xlabel("Generations Worst and Average (red) Potentials")
ylabel("Fitness")

figure
plot(i,fitness_average_fsm(i),'r+-',i,fitness_best_fsm(i),'kx-')
%xlabel("Generations Average (red) and Best FSM")
ylabel("Fitness")


figure
plot(j,fitness_average_hmm(j),'r+-',j,fitness_best_hmm(j),'kx-')
%xlabel("Generations Average (red) and Best FSM")
ylabel("Fitness")

figure
plot(i,fitness_best_fsm(i),'b+-',j,fitness_best_hmm(j),'gx-',k,fitness_best_potentials(k),'rx-')
%xlabel("Generations Best FSM (red) and Best hmm")
ylabel("Fitness")


figure
test = [3635.41391278 4267.94411071 4243.06399274];
bar(test,0.4)
M=["BEHAVIORS: POTENTIALS";"FSM";"HMM"]
var = sprintf("%s                        %s      %s",M(1,:),M(2,:),M(3,:))
xlabel(var)
ylabel("FITNESS")

figure
test = [1983.59443201 2541.16705979 2153.66487689];
bar(test,0.4)
M=["BEHAVIORS: POTENTIALS";"FSM";"HMM"]
var = sprintf("%s                        %s      %s",M(1,:),M(2,:),M(3,:))
xlabel(var)
ylabel("FITNESS")

