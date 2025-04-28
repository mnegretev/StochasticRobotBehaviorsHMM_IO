
load /home/biorobotica/data/data_15/fitness_average_hmm.dat
load /home/biorobotica/data/data_15/fitness_worst_hmm.dat
load /home/biorobotica/data/data_15/fitness_best_hmm.dat

s=size(fitness_best_hmm);
num_gen = s(1) -1
  
i=1:s(:,1);
n=1;
i=n:s(:,1);
figure
plot(i,fitness_average_hmm(i),'r+-',i,fitness_best_hmm(i),'kx-',i,fitness_worst_hmm(i),'b*-')
xlabel("Generations Worst, Average (red) and Best FSM-HMM")
ylabel("Fitness")


mean_best= mean(fitness_best_hmm(n:num_gen))
std_best= std(fitness_best_hmm(n:num_gen))
[best_value index]=max(fitness_best_hmm(n:num_gen))
n+index-1

mean_average=mean(fitness_average_hmm(n:num_gen))
std_average=std(fitness_average_hmm(n:num_gen))
[average_value index]=max(fitness_average_hmm(n:num_gen))
n+index-1

mean_worst=mean(fitness_worst_hmm(n:num_gen))
std_worst=std(fitness_worst_hmm(n:num_gen))
[worst_value index]=max(fitness_worst_hmm(n:num_gen))
n+index-1


