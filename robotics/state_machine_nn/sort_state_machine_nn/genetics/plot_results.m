
%load ../test_data_2/fitness_nn.dat
%nn=fitness_nn(:,3)';
%nn=fitness_nn(:,2)';
%nn=fitness_nn(:,1)';
%igure
%lot3(xnn,ynn,znn)
%label("X, Size Polygons")
%label("Y, Power Noise")
%label("Z, NN Performance")


%oad ../test_data_2/fitness_fsm.dat
%fsm=fitness_fsm(:,3)';
%fsm=fitness_fsm(:,2)';
%fsm=fitness_fsm(:,1)';
%igure
%lot3(xfsm,yfsm,zfsm)
%label("X, Size Polygons")
%label("Y, Power Noise")
%label("Z, FSM Performance")



load ../test_data_2/fitness_hmm.dat
zhmm=fitness_hmm(:,3)';
yhmm=fitness_hmm(:,2)';
xhmm=fitness_hmm(:,1)';
%figure
%plot(yhmm(1:40),zhmm(1:40))
%plot3(xhmm,yhmm,zhmm)
%xlabel("X, Size Polygons")
%ylabel("Y, Power Noise")
%zlabel("Z, HMM Performance")



%oad ../test_data_2/fitness_viterbi.dat
%viterbi=fitness_viterbi(:,3)';
%viterbi=fitness_viterbi(:,2)';
%viterbi=fitness_viterbi(:,1)';
%igure
%lot3(xviterbi,yviterbi,zviterbi)
%label("X, Size Polygons")
%label("Y, Power Noise")
%label("Z, Viterbi Performance")



load ../test_data_2/fitness_fsm_human.dat
zhuman=fitness_fsm_human(:,3)';
yhuman=fitness_fsm_human(:,2)';
xhuman=fitness_fsm_human(:,1)';
%figure
%plot(yhuman(1:40),zhuman(1:40))
%figure
%plot3(xhuman,yhuman,zhuman)
%xlabel("X, Size Polygons")
%ylabel("Y, Power Noise")
%zlabel("Z, FSM Human Performance")

size_z=size(zhmm)
j=1
max_mean_human=0;
max_mean_hmm=0;
xvalues= xhuman(1:40:size_z(2));

for i=1:40:size_z(2)
	j
	%figure
	%plot(yhuman(i:i+39),zhuman(i:i+39))
	%xlabel("FSM")
	%ylabel("performance")

	mean_human(j)=mean(zhuman(i:i+39));
	max_human(j)=max(zhuman(i:i+39));

	if mean_human(j) > max_mean_human  
		max_mean_human=mean_human(j);
		arg_max_mean_human=j;
	end

	%figure
	%plot(yhmm(i:i+39),zhmm(i:i+39))
	%xlabel("HMM FSM")
	%ylabel("performance")
	mean_hmm(j)=mean(zhmm(i:i+39));
        max_hmm(j)=max(zhmm(i:i+39));

	if mean_hmm(j) > max_mean_hmm
                max_mean_hmm=mean_hmm(j);
                arg_max_mean_hmm=j;
	end
	
	figure
	plot(yhuman(i:i+39),zhuman(i:i+39),'r-',yhmm(i:i+39),zhmm(i:i+39),'b-')
	%xlabel("FSM (red) HMM FSM (Blue)")
	xlabel("NOISE LEVEL")
	ylabel("MEAN PERFORMANCE")
	j=j+1;

end

%figure
%plot(mean_human)
%xlabel("FSM")
%ylabel("Mean values")
%figure
%plot(max_human)
%xlabel("FSM")
%ylabel("Maximum values")

%figure
%plot(mean_hmm)
%xlabel("HMM FSM")
%ylabel("Mean values")
%figure
%plot(max_hmm)
%xlabel("HMM FSM")
%ylabel("Maximum values")


max_mean_human
arg_max_mean_human

max_mean_hmm
arg_max_mean_hmm

figure
plot(xvalues,mean_human,'r-',xvalues,mean_hmm,'b-')
xlabel("OBSTACLES' SIZE")
%xlabel("FSM (red) HMM FSM (Blue)")
%ylabel("mean performance")
ylabel("MEAN PERFORMANCE")

figure
plot(xvalues,max_human,'r-',xvalues,max_hmm,'b-')
xlabel("OBSTACLES' SIZE")
%xlabel("FSM (red) HMM FSM (Blue)")
ylabel("MAXIMUM PERFORMANCE")



