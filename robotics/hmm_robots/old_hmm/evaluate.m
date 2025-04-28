cd ~/robotics/data
load random_1.evl
maxi=max(random_1(:,2))
ran= random_1(:,2)/maxi;
figure
plot(random_1(:,1),ran)
cd ~/robotics/hmm_robots

