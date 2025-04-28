
load ../data/fitness_average.dat
load ../data/fitness_worst.dat
load ../data/fitness_best.dat
load ../data/fitness_hmm_human.dat
load ../data/fitness_state_machine_human.dat
load ../data/fitness_hmm_viterbi.dat

s=size(fitness_best)  
i=1:s(:,1);
%plot(i,fitness_average(i),'b+-',i,fitness_best(i),'kx-',i,fitness_worst(i),'b*-',i,fitness_hmm_human(i),'ro-',i,fitness_state_machine_human(i),'r>-')

figure
plot(i,fitness_average(i),'r+-',i,fitness_best(i),'kx-',i,fitness_worst(i),'b*-')
xlabel("Generations")
ylabel("Fitness")
%figure
%plot(i,fitness_hmm_viterbi(i),'k-',i,fitness_hmm_human(i),'r-',i,fitness_state_machine_human(i),'b*-')
%figure
%plot(i,fitness_best(i),'k-',i,fitness_hmm_human(i),'r-',i,fitness_state_machine_human(i),'b*-',i,fitness_hmm_viterbi(i),'g-')
figure
plot(i,fitness_best(i),'r-',i,fitness_state_machine_human(i),'k-')
xlabel("Generations")
ylabel("Fitness")
figure
plot(i,fitness_best(i),'r-',i,fitness_hmm_human(i),'k-')
xlabel("Generations")
ylabel("Fitness")
figure
plot(i,fitness_best(i),'r-',i,fitness_hmm_viterbi(i),'k-')
xlabel("Generations")
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



