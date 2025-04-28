

%load ../data/fitness_average.dat
%load ../data/fitness_worst.dat
%load ../data/fitness_best.dat
%load ../data/fitness_average_fsm.dat
%load ../data/fitness_worst_fsm.dat
%load ../data/fitness_best_fsm.dat
%load ../data/fitness_hmm_human.dat
%load ../data/fitness_state_machine_human.dat
%load ../data/fitness_hmm_viterbi.dat

%load ../observations/fitness_average.dat
%load ../observations/fitness_worst.dat
%load ../observations/fitness_best.dat
%load ../observations/fitness_average_fsm.dat
%load ../observations/fitness_worst_fsm.dat
%load ../observations/fitness_best_fsm.dat
%load ../observations/fitness_hmm_human.dat
%load ../observations/fitness_state_machine_human.dat
%load ../observations/fitness_hmm_viterbi.dat
%load ../observations/fitness_average_nn.dat
%load ../observations/fitness_worst_nn.dat
%load ../observations/fitness_best_nn.dat


%load ../test_data/fitness_average.dat
%load ../test_data/fitness_worst.dat
%load ../test_data/fitness_best.dat
%load ../test_data/fitness_average_fsm.dat
%load ../test_data/fitness_worst_fsm.dat
%load ../test_data/fitness_best_fsm.dat
%load ../test_data/fitness_hmm_human.dat
%load ../test_data/fitness_state_machine_human.dat
%load ../test_data/fitness_hmm_viterbi.dat
%load ../test_data/fitness_average_nn.dat
%load ../test_data/fitness_worst_nn.dat
%load ../test_data/fitness_best_nn.dat


load ../test_data_3/fitness_average.dat
load ../test_data_3/fitness_worst.dat
load ../test_data_3/fitness_best.dat
load ../test_data_3/fitness_average_fsm.dat
load ../test_data_3/fitness_worst_fsm.dat
load ../test_data_3/fitness_best_fsm.dat
load ../test_data_3/fitness_hmm_human.dat
load ../test_data_3/fitness_state_machine_human.dat
load ../test_data_3/fitness_hmm_viterbi.dat
load ../test_data_3/fitness_average_nn.dat
load ../test_data_3/fitness_worst_nn.dat
load ../test_data_3/fitness_best_nn.dat





s=size(fitness_best);
num_gen = s(1) -1
  
i=1:s(:,1);
%plot(i,fitness_average(i),'b+-',i,fitness_best(i),'kx-',i,fitness_worst(i),'b*-',i,fitness_hmm_human(i),'ro-',i,fitness_state_machine_human(i),'r>-')


figure
plot(i,fitness_average_nn(i),'r+-',i,fitness_best_nn(i),'kx-',i,fitness_worst_nn(i),'b*-')
xlabel("Generations Worst, Average (red) and Best NN")
ylabel("Fitness")

figure
plot(i,fitness_average(i),'r+-',i,fitness_best(i),'kx-',i,fitness_worst(i),'b*-')
xlabel("Generations Worst, Average (red) and Best HMM")
ylabel("Fitness")

figure
plot(i,fitness_average_fsm(i),'r+-',i,fitness_best_fsm(i),'kx-',i,fitness_worst_fsm(i),'b*-')
xlabel("Generations Worst, Average (red) and Best FSM")
ylabel("Fitness")



%figure
%plot(i,fitness_hmm_viterbi(i),'k-',i,fitness_hmm_human(i),'r-',i,fitness_state_machine_human(i),'b*-')



figure
plot(i,fitness_best_fsm(i),'r-',i,fitness_best(i),'k-')
xlabel("Generations best FSM (red) and best HMM")
ylabel("Fitness")

figure
plot(i,fitness_best_fsm(i),'r-',i,fitness_state_machine_human(i),'k-')
xlabel("Generations FSM Human and best individual FSM (red)")
ylabel("Fitness")

figure
plot(i,fitness_best(i),'r-',i,fitness_state_machine_human(i),'k-')
xlabel("Generations FSM Human and best individual HMM (red)")
ylabel("Fitness")

figure
plot(i,fitness_hmm_human(i),'r-',i,fitness_hmm_viterbi(i),'g-')
xlabel("Generations HMM Human (red) and HMM Viterbi")
ylabel("Fitness")

figure
plot(i,fitness_best(i),'r-',i,fitness_hmm_human(i),'k-')
xlabel("Generations HMM Human and best individual HMM (red)")
ylabel("Fitness")

figure
plot(i,fitness_best(i),'r-',i,fitness_hmm_viterbi(i),'k-')
xlabel("Generations HMM Viterbi and best individual HMM (red)")
ylabel("Fitness")

%f=fitness_best_fsm - fitness_best;
%figure
%plot(f)
%xlabel("Generations")
%ylabel("fitness_best_fsm - fitness_best_HMM")

%figure
%plot(i,fitness_best(i),'r+-',i,fitness_best_nn(i),'kx-',i,fitness_best_fsm(i),'b*-')
%xlabel("Generations best HMM (red), NN (black) and FSM (blue)")
%ylabel("Fitness")

figure
plot(i,fitness_best(i),'r+-',i,fitness_best_nn(i),'kx-',i,fitness_best_fsm(i),'b*-',fitness_hmm_viterbi(i),'g-')
xlabel("Gen. HMM (red), NN (black), FSM (blue), and HMM VITERBI (green)")
ylabel("Fitness")


figure
%plot(i,fitness_best_nn(i),'r+-',i,fitness_best_fsm(i),'kx-',i,fitness_best(i),'b*-',fitness_state_machine_human(i),'g-',fitness_hmm_human(i),'m-', fitness_hmm_viterbi(i),'c-')
plot(i,fitness_best_nn(i),'r-',i,fitness_best_fsm(i),'k-',i,fitness_best(i),'b-',fitness_state_machine_human(i),'g-',fitness_hmm_human(i),'m-', fitness_hmm_viterbi(i),'c-')
xlabel("GEN NN (red), GEN FSM (black), GEN HMM (blue),  Human FSM (green), Human HMM (magenta) and HMM VITERBI (cyan)")
ylabel("Fitness")


figure
plot(i,fitness_average_nn(i),'r-',i,fitness_average_fsm(i),'k-',i,fitness_average(i),'b-')
xlabel("Generations  Average nn (red), fsm (black) and hmm (blue)")
ylabel("Fitness")

figure
plot(i,fitness_worst_nn(i),'r+-',i,fitness_worst_fsm(i),'kx-',i,fitness_worst(i),'b*-')
xlabel("Generations  worst nn (red), fsm (black) and hmm (blue)")
ylabel("Fitness")

%plot(i,fitness_hmm_human(i),'k-',i,fitness_state_machine_human(i),'r-')
%figure
%plot(i,fitness_state_machine_human(i),'k-',i,fitness_best(i),'r-')


%e=fitness_state_machine_human(1:s(:,1)) - fitness_best(1:s(:,1));
%e=sqrt((fitness_state_machine_human(1:s(:,1)) - fitness_best(1:s(:,1))).**2);
%figure
%plot(abs(e))

%biggest = 0;
%for j=1:size(fitness_best)
%
	%if abs(e(j)) > biggest
		%biggest = abs(e(j));
	%end

	%if e(j) > 0
		%x(j)=0;
	%else
		%x(j)=e(j);
	%end
%end

%x(1) = biggest;
%figure
%plot(x)



figure
plot(i,fitness_best(i),'r-',i,fitness_state_machine_human(i),'b-',i,fitness_hmm_human(i),'k-')
xlabel("GEN HMM (red),  Human FSM (blue), Human HMM (black)")
ylabel("Fitness")

figure
plot(i,fitness_best(i),'r-',i,fitness_state_machine_human(i),'b-',i,fitness_hmm_viterbi(i),'k-')
xlabel("GEN HMM (red),  HMM Human (blue), Baum-Welch HMM (black)")
ylabel("Fitness")

figure
plot(i,fitness_best(i),'b-',i,fitness_state_machine_human(i),'r-')
xlabel("PFSM (blue),  FSM (red)")
ylabel("Fitness")

