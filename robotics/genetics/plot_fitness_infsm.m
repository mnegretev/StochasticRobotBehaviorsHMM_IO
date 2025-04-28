clear

%load /home/biorobotica/data/data_5/fitness_average_infsm.dat
%load /home/biorobotica/data/data_5/fitness_worst_infsm.dat
%load /home/biorobotica/data/data_5/fitness_best_infsm.dat
%s=size(fitness_best_infsm);
%num_gen = s(1);
%num_gen_infsm = num_gen
%i=1:s(:,1);
%figure
%plot(i,fitness_average_infsm(i),'r+-',i,fitness_best_infsm(i),'kx-',fitness_worst_infsm(i),'b*-')
%xlabel("Generations Best (black), Worst (blue) and Average (red) Input/State FSM 32 VQ")
%ylabel("Fitness")
%[max_INFSM I_FSM] = max(fitness_best_infsm)
%[max_average_FSM I_A_FSM] = max(fitness_average_infsm)



load ../../data/data_8/fitness_average_infsm.dat
load ../../data/data_8/fitness_worst_infsm.dat
load ../../data/data_8/fitness_best_infsm.dat
s=size(fitness_best_infsm);
num_gen = s(1);
num_gen_infsm_Meally = num_gen
i=1:s(:,1);
figure
plot(i,fitness_average_infsm(i),'r+-',i,fitness_best_infsm(i),'kx-',fitness_worst_infsm(i),'b*-')
xlabel("Generations Best (black), Worst (blue) and Average (red) Input/State Meally FSM 8 VQ")
ylabel("Fitness")
[max_INFSM_Meally I_INFSM_Meally] = max(fitness_best_infsm)
[max_average_INFSM_Meally I_A_INFSM_Meally] = max(fitness_average_infsm)
%bests(1)=fitness_best_infsm(s(:,1));
bests(1)=max_INFSM_Meally;
averages(1)=max_average_INFSM_Meally;
medians(1)=median(fitness_best_infsm);

load ../../data/data_9/fitness_average_infsm.dat
load ../../data/data_9/fitness_worst_infsm.dat
load ../../data/data_9/fitness_best_infsm.dat
s=size(fitness_best_infsm);
num_gen = s(1);
num_gen_infsm_Moore = num_gen
i=1:s(:,1);
figure
plot(i,fitness_average_infsm(i),'r+-',i,fitness_best_infsm(i),'kx-',fitness_worst_infsm(i),'b*-')
xlabel("Generations Best (black), Worst (blue) and Average (red) Input/State Moore FSM 8 VQ")
ylabel("Fitness")
[max_INFSM_Moore I_FSM_Moore] = max(fitness_best_infsm)
[max_average_FSM_Moore I_A_FSM_Moore] = max(fitness_average_infsm)
%bests(2)=fitness_best_infsm(s(:,1));
bests(2)=max_INFSM_Moore;
averages(2)=max_average_FSM_Moore;
medians(2)=median(fitness_best_infsm);


load ../../data/data_6/fitness_average_hmm.dat
load ../../data/data_6/fitness_worst_hmm.dat
load ../../data/data_6/fitness_best_hmm.dat
s=size(fitness_best_hmm);
num_gen = s(1);
num_gen_hmm_8 = num_gen
i=1:s(:,1)-1;
figure
plot(i,fitness_average_hmm(i),'r+-',i,fitness_best_hmm(i),'kx-',fitness_worst_hmm(i),'b*-')
xlabel("Generations Best (black), Worst (blue) and Average (red) HMM 8 VQ")
ylabel("Fitness")
[max_HMM_8 I_HMM_8] = max(fitness_best_hmm)
[max_average_HMM_8 I_A_HMM_8] = max(fitness_average_hmm)
%bests(3)=fitness_best_hmm(s(:,1));
bests(3)=max_HMM_8;
averages(3)=max_average_HMM_8;
medians(3)=median(fitness_best_hmm);

load ../../data/data_7/fitness_average_mdp.dat
load ../../data/data_7/fitness_worst_mdp.dat
load ../../data/data_7/fitness_best_mdp.dat
s=size(fitness_best_mdp);
num_gen = s(1);
num_gen_mdp = num_gen
i=1:s(:,1);
figure
plot(i,fitness_average_mdp(i),'r+-',i,fitness_best_mdp(i),'kx-',fitness_worst_mdp(i),'b*-')
xlabel("Generations Best (black), Worst (blue) and Average (red) MDP")
ylabel("Fitness")
[max_MDP I_MDP] = max(fitness_best_mdp)
[max_average_MDP_8 I_A_MDP_8] = max(fitness_average_mdp)
bests(4)=max_MDP;
averages(4)=max_average_MDP_8;
medians(4)=median(fitness_best_mdp);


load ../../data/data_10/fitness_average_reactive.dat
load ../../data/data_10/fitness_worst_reactive.dat
load ../../data/data_10/fitness_best_reactive.dat
s=size(fitness_best_reactive);
num_gen = s(1);
num_gen_reactive = num_gen
i=1:s(:,1);
figure
plot(i,fitness_average_reactive(i),'r+-',i,fitness_best_reactive(i),'kx-',fitness_worst_reactive(i),'b*-')
xlabel("Generations Best (black), Worst (blue) and Average (red) Reactive")
ylabel("Fitness")
[max_REACTIVE I_REACTIVE] = max(fitness_best_reactive)
[max_average_REACTIVE_8 I_A_REACTIVE_8] = max(fitness_average_reactive)
%bests(5)=fitness_best_reactive(s(:,1));
bests(5)=max_REACTIVE;
averages(5)=max_average_REACTIVE_8;
medians(5)=median(fitness_best_reactive);


load ../../data/data_3/fitness_average_fsm.dat
load ../../data/data_3/fitness_worst_fsm.dat
load ../../data/data_3/fitness_best_fsm.dat
s=size(fitness_best_fsm);
num_gen = s(1);
num_gen_fsm_Meally = num_gen
i=1:s(:,1);
figure
plot(i,fitness_average_fsm(i),'r+-',i,fitness_best_fsm(i),'kx-',fitness_worst_fsm(i),'b*-')
xlabel("Generations Best (black), Worst (blue) and Average (red) Meally FSM 8 VQ")
ylabel("Fitness")
[max_FSM_Meally I_FSM_Meally] = max(fitness_best_fsm)
[max_average_FSM_Meally I_A_FSM_Meally] = max(fitness_average_fsm)
%bests(6)=fitness_best_fsm(s(:,1));
bests(6)=max_FSM_Meally;
averages(6)=max_average_FSM_Meally;
medians(6)=median(fitness_best_fsm);


load ../../data/data_1/fitness_average_nn.dat
load ../../data/data_1/fitness_worst_nn.dat
load ../../data/data_1/fitness_best_nn.dat
s=size(fitness_best_nn);
num_gen = s(1);
num_gen_nn = num_gen
i=1:s(:,1);
figure
plot(i,fitness_average_nn(i),'r+-',i,fitness_best_nn(i),'kx-',fitness_worst_nn(i),'b*-')
xlabel("Generations Best (black), Worst (blue) and Average (red) NN")
ylabel("Fitness")
[max_NN I_NN] = max(fitness_best_nn)
[max_average_NN I_A_NN] = max(fitness_average_nn)
bests(7)=max_NN;
averages(7)=max_average_NN;
medians(7)=median(fitness_best_nn);


load ../../data/data_2/fitness_average_rnn.dat
load ../../data/data_2/fitness_worst_rnn.dat
load ../../data/data_2/fitness_best_rnn.dat
s=size(fitness_best_rnn);
num_gen = s(1);
num_gen_rnn = num_gen
i=1:s(:,1);
figure
plot(i,fitness_average_rnn(i),'r+-',i,fitness_best_rnn(i),'kx-',fitness_worst_rnn(i),'b*-')
xlabel("Generations Best (black), Worst (blue) and Average (red) RNN")
ylabel("Fitness")
[max_RNN I_RNN] = max(fitness_best_rnn)
[max_average_RNN I_A_RNN] = max(fitness_average_rnn)
bests(8)=max_RNN;
averages(8)=max_average_RNN;
medians(8)=median(fitness_best_rnn);


load ../../data/data_4/fitness_average_potentials.dat
load ../../data/data_4/fitness_worst_potentials.dat
load ../../data/data_4/fitness_best_potentials.dat
s=size(fitness_best_potentials);
num_gen = s(1);
num_gen_potentials = num_gen
i=1:s(:,1);
figure
plot(i,fitness_average_potentials(i),'r+-',i,fitness_best_potentials(i),'kx-',fitness_worst_potentials(i),'b*-')
xlabel("Generations Best (black), Worst (blue) and Average (red) POTENTIALS")
ylabel("Fitness")
[max_POTENTIALS I_POTENTIALS] = max(fitness_best_potentials)
[max_average_POTENTIALS I_A_POTENTIALS] = max(fitness_average_potentials)
bests(9)=max_POTENTIALS;
averages(9)=max_average_POTENTIALS;
medians(9)=median(fitness_best_potentials);



load ../../data/data_5/fitness_average_nn_st.dat
load ../../data/data_5/fitness_worst_nn_st.dat
load ../../data/data_5/fitness_best_nn_st.dat
s=size(fitness_best_nn_st);
num_gen = s(1);
num_gen_nn_st = num_gen
i=1:s(:,1);
figure
plot(i,fitness_average_nn_st(i),'r+-',i,fitness_best_nn_st(i),'kx-',fitness_worst_nn_st(i),'b*-')
xlabel("Generations Best (black), Worst (blue) and Average (red) NN Stochastic")
ylabel("Fitness")
[max_NN_ST I_NN_ST] = max(fitness_best_nn_st)
[max_average_NN_ST I_A_NN_ST] = max(fitness_average_nn_st)
bests(10)=max_NN_ST;
averages(10)=max_average_NN_ST;
medians(10)=median(fitness_best_nn_st);


load ../../data/data_11/fitness_average_rnn_st.dat
load ../../data/data_11/fitness_worst_rnn_st.dat
load ../../data/data_11/fitness_best_rnn_st.dat
s=size(fitness_best_rnn_st);
num_gen = s(1);
num_gen_rnn_st = num_gen
i=1:s(:,1);
figure
plot(i,fitness_average_rnn_st(i),'r+-',i,fitness_best_rnn_st(i),'kx-',fitness_worst_rnn_st(i),'b*-')
xlabel("Generations Best (black), Worst (blue) and Average (red) RNN Stochastic")
ylabel("Fitness")
[max_RNN_ST I_RNN_ST] = max(fitness_best_rnn_st)
[max_average_RNN_ST I_A_RNN_ST] = max(fitness_average_rnn_st)
bests(11)=max_RNN_ST;
averages(11)=max_average_RNN_ST;
medians(11)=median(fitness_best_rnn_st);



load ../../data/data_12/fitness_average_fsm_st.dat
load ../../data/data_12/fitness_worst_fsm_st.dat
load ../../data/data_12/fitness_best_fsm_st.dat
s=size(fitness_best_fsm_st);
num_gen = s(1);
num_gen_fsm_st = num_gen
i=1:s(:,1);
figure
plot(i,fitness_average_fsm_st(i),'r+-',i,fitness_best_fsm_st(i),'kx-',fitness_worst_fsm_st(i),'b*-')
xlabel("Generations Best (black), Worst (blue) and Average (red) FSM Stochastic")
ylabel("Fitness")
[max_FSM_ST I_FSM_ST] = max(fitness_best_fsm_st)
[max_average_FSM_ST I_A_FSM_ST] = max(fitness_average_fsm_st)
bests(12)=max_FSM_ST;
averages(12)=max_average_FSM_ST;
medians(12)=median(fitness_best_fsm_st);



load ../../data/data_13/fitness_average_reactive_stochastic.dat
load ../../data/data_13/fitness_worst_reactive_stochastic.dat
load ../../data/data_13/fitness_best_reactive_stochastic.dat
s=size(fitness_best_reactive_stochastic);
num_gen = s(1);
num_gen_reactive_st = num_gen
i=1:s(:,1);
figure
plot(i,fitness_average_reactive_stochastic(i),'r+-',i,fitness_best_reactive_stochastic(i),'kx-',fitness_worst_reactive_stochastic(i),'b*-')
xlabel("Generations Best (black), Worst (blue) and Average (red) REACTIVE Stochastic")
ylabel("Fitness")
[max_REACTIVE_ST I_REACTIVE_ST] = max(fitness_best_reactive_stochastic)
[max_average_REACTIVE_ST I_A_REACTIVE_ST] = max(fitness_average_reactive_stochastic)
bests(13)=max_REACTIVE_ST;
averages(13)=max_average_REACTIVE_ST;
medians(13)=median(fitness_best_reactive_stochastic);


%dif_MAX_32 = abs(max_MDP - max_HMM)
%dif_AVR_32 = abs(max_average_MDP_8 - max_average_HMM)

%dif_MAX_8 = abs(max_MDP - max_HMM_8)
%dif_AVR_8 = abs(max_average_MDP_8 - max_average_HMM_8)


[s_bests, ind] = sort(bests)
[best_value_best index]=max(bests)
figure
bar(s_bests)
var = sprintf("B. %d   ",ind)
xlabel(var)
ylabel("Behaviors Fitness Best")


[s_averages, ind_a] = sort(averages)
[best_value_average index_ave]=max(averages)
figure
bar(s_averages)
var = sprintf("B. %d   ",ind_a)
xlabel(var)
ylabel("Average Fitness Best")

[s_medians, ind_a] = sort(medians)
[best_value_medians index_ave]=max(medians)
figure
bar(s_medians)
var = sprintf("B. %d   ",ind_a)
xlabel(var)
ylabel("Average Medians Best")

