


load test_data/fitness_average_nn.dat
load test_data/fitness_worst_nn.dat
load test_data/fitness_best_nn.dat





s=size(fitness_best_nn);
num_gen = s(1) -1
  
i=1:s(:,1);
%plot(i,fitness_average(i),'b+-',i,fitness_best(i),'kx-',i,fitness_worst(i),'b*-',i,fitness_hmm_human(i),'ro-',i,fitness_state_machine_human(i),'r>-')


figure
plot(i,fitness_average_nn(i),'r+-',i,fitness_best_nn(i),'kx-',i,fitness_worst_nn(i),'b*-')
xlabel("Generations Worst, Average (red) and Best NN")
ylabel("Fitness")

