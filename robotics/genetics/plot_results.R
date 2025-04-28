install.packages("plotly")
install.packages("ramify")

#source("~/robotics/genetics/plot_results.R")

library(plotly)
packageVersion('plotly')
library("ramify")


fsm_human_data = read.table("fitness_fsm_human.dat")
fsm_human_x <- fsm_human_data[,1]
fsm_human_y <- fsm_human_data[,2]
fsm_human_z <- fsm_human_data[,3]
x11()
scatter3D(fsm_human_x,fsm_human_y,fsm_human_z,xlab='X, Size Polygons', ylab='Y, Power Noise', zlab='Z, FSM Human Performance')
plot_ly(x = fsm_human_x, y = fsm_human_y,z = fsm_human_z,type = "mesh3d")
max_fsm_human=max(fsm_human_z)
min_fsm_human=min(fsm_human_z)
mean_fsm_human=mean(fsm_human_z)
standar_fsm_human=sqrt(var(fsm_human_z))
cat("\n-+-+-+-+- FSM_HUMAN +-+-+-+-+-+-+-+-+-+\n")
cat("Max. FSM_HUMAN ",max_fsm_human,"\n")
cat("Min. FSM_HUMAN ",min_fsm_human,"\n")
cat("Mean FSM_HUMAN ",mean_fsm_human,"\n")
cat("Standard Dev. FSM_HUMAN ",standar_fsm_human,"\n")
cat("-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n\n")




hmm_human_data = read.table("fitness_hmm_human.dat")
hmm_human_x <- hmm_human_data[,1]
hmm_human_y <- hmm_human_data[,2]
hmm_human_z <- hmm_human_data[,3]
#x11()
#scatter3D(hmm_human_x,hmm_human_y,hmm_human_z,xlab='X, Size Polygons', ylab='Y, Power Noise', zlab='Z, FSM Human Performance')
plot_ly(x = hmm_human_x, y = hmm_human_y,z = hmm_human_z,type = "mesh3d")
max_hmm_human=max(hmm_human_z)
min_hmm_human=min(hmm_human_z)
mean_hmm_human=mean(hmm_human_z)
standard_hmm_human=sqrt(var(hmm_human_z))
cat("\n-+-+-+-+- HMM_HUMAN +-+-+-+-+-+-+-+-+-+\n")
cat("Max. HMM_HUMAN ",max_hmm_human,"\n")
cat("Min. HMM_HUMAN ",min_hmm_human,"\n")
cat("Mean HMM_HUMAN ",mean_hmm_human,"\n")
cat("Standard Dev. HMM_HUMAN ",standard_hmm_human,"\n")
cat("-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n\n")


viterbi_data = read.table("fitness_viterbi.dat")
viterbi_x <- viterbi_data[,1]
viterbi_y <- viterbi_data[,2]
viterbi_z <- viterbi_data[,3]
#x11()
#scatter3D(viterbi_x,viterbi_y,viterbi_z,xlab='X, Size Polygons', ylab='Y, Power Noise', zlab='Z, FSM Human Performance')
#plot_ly(x = viterbi_x, y = viterbi_y,z = viterbi_z,type = "mesh3d")
max_viterbi=max(viterbi_z)
min_viterbi=min(viterbi_z)
mean_viterbi=mean(viterbi_z)
standard_viterbi=sqrt(var(viterbi_z))
cat("\n-+-+-+-+- VITERBI +-+-+-+-+-+-+-+-+-+\n")
cat("Max. VITERBI ",max_viterbi,"\n")
cat("Min. VITERBI ",min_viterbi,"\n")
cat("Mean VITERBI ",mean_viterbi,"\n")
cat("Standard Dev. VITERBI ",standard_viterbi,"\n")
cat("-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n\n")


fsm_data = read.table("fitness_fsm.dat")
fsm_x <- fsm_data[,1]
fsm_y <- fsm_data[,2]
fsm_z <- fsm_data[,3]
#x11()
#scatter3D(fsm_x,fsm_y,fsm_z,xlab='X, Size Polygons', ylab='Y, Power Noise', zlab='Z, FSM Human Performance')
#plot_ly(x = fsm_x, y = fsm_y,z = fsm_z,type = "mesh3d")
max_fsm=max(fsm_z)
min_fsm=min(fsm_z)
mean_fsm=mean(fsm_z)
standard_fsm=sqrt(var(fsm_z))
cat("\n-+-+-+-+- FSM +-+-+-+-+-+-+-+-+-+\n")
cat("Max. FSM ",max_fsm,"\n")
cat("Min. FSM ",min_fsm,"\n")
cat("Mean FSM ",mean_fsm,"\n")
cat("Standard Dev. FSM ",standard_fsm,"\n")
cat("-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n\n")


hmm_data = read.table("fitness_hmm.dat")
hmm_x <- hmm_data[,1]
hmm_y <- hmm_data[,2]
hmm_z <- hmm_data[,3]
#x11()
#scatter3D(hmm_x,hmm_y,hmm_z,xlab='X, Size Polygons', ylab='Y, Power Noise', zlab='Z, FSM Human Performance')
#plot_ly(x = hmm_x, y = hmm_y,z = hmm_z,type = "mesh3d")
max_hmm=max(hmm_z)
min_hmm=min(hmm_z)
mean_hmm=mean(hmm_z)
standard_hmm=sqrt(var(hmm_z))
cat("\n-+-+-+-+- HMM +-+-+-+-+-+-+-+-+-+\n")
cat("Max. HMM ",max_hmm,"\n")
cat("Min. HMM ",min_hmm,"\n")
cat("Mean HMM ",mean_hmm,"\n")
cat("Standard Dev. HMM ",standard_hmm,"\n")
cat("-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n\n")


nn_data = read.table("fitness_nn.dat")
nn_x <- nn_data[,1]
nn_y <- nn_data[,2]
nn_z <- nn_data[,3]
#x11()
#scatter3D(nn_x,nn_y,nn_z,xlab='X, Size Polygons', ylab='Y, Power Noise', zlab='Z, FSM Human Performance')
#plot_ly(x = nn_x, y = nn_y,z = nn_z,type = "mesh3d")
max_nn=max(nn_z)
min_nn=min(nn_z)
mean_nn=mean(nn_z)
standard_nn=sqrt(var(nn_z))
cat("\n-+-+-+-+- NN +-+-+-+-+-+-+-+-+-+\n")
cat("Max. NN ",max_nn,"\n")
cat("Min. NN ",min_nn,"\n")
cat("Mean NN ",mean_nn,"\n")
cat("Standard Dev. NN ",standard_nn,"\n")
cat("-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n\n")

#hmm_data[121:160,1]
#hmm_data[121:160,2]
#hmm_data[121:160,3]

num_blocks = 20
mean_hmm_z = 1:num_blocks+1
standard_hmm_z = 1:num_blocks+1
major_hmm_z = 1:num_blocks+1

j = 1
inc = 40
k = inc

for (i in 1:num_blocks+1){

  print(paste("j ", j," k ", k))
  hmm_x <- hmm_data[j:k,1]
  hmm_y <- hmm_data[j:k,2]
  hmm_z <- hmm_data[j:k,3]
  major = 0
  arg_major = 1

  for (l in 1:inc){
	if(hmm_z[l] > major){
		major = hmm_z[l]
		arg_major = l
	}
  }
 
  print(paste("arg major ", arg_major," major ",major))
  major_hmm_z[i] = major
  mean_hmm_z[i] = mean(hmm_z)
  standard_hmm_z[i]=sqrt(var(hmm_z))
  print(paste("i ", i," mean hmm_z ",mean_hmm_z[i]," std ",standard_hmm_z[i]))
  #x11()
  #plot(hmm_y,hmm_z)
  #lines(hmm_y,hmm_z)
  j=j+inc
  k=k+inc
}

x11()
plot(mean_hmm_z)
lines(mean_hmm_z)

x11()
plot(standard_hmm_z)
lines(standard_hmm_z)

x11()
plot(major_hmm_z)
lines(major_hmm_z)



inc = 25
inc_1 = inc 
num_blocks = 8
FSM_Z = matrix(nrow=inc, ncol=num_blocks+1)
FSM_X = matrix(nrow=inc, ncol=num_blocks+1)
FSM_Y = matrix(nrow=inc, ncol=num_blocks+1)
NN_Z = matrix(nrow=inc, ncol=num_blocks+1)
NN_X = matrix(nrow=inc, ncol=num_blocks+1)
NN_Y = matrix(nrow=inc, ncol=num_blocks+1)
HMM_Z = matrix(nrow=inc, ncol=num_blocks+1)
HMM_X = matrix(nrow=inc, ncol=num_blocks+1)
HMM_Y = matrix(nrow=inc, ncol=num_blocks+1)

mean_FSM_z = 1:inc+1
standard_FSM_z = 1:inc+1
major_FSM_z = 1:inc+1
mean_NN_z = 1:inc+1
standard_NN_z = 1:inc+1
major_NN_z = 1:inc+1
mean_HMM_z = 1:inc+1
standard_HMM_z = 1:inc+1
major_HMM_z = 1:inc+1



for(j in 1:inc_1){
  k = j
  major_hmm = 0
  major_nn = 0
  major_fsm = 0

  for (i in 0:(num_blocks)){

  	print(paste("j ",j,"i ", i," k ", k," k+i ",k+i))
  	FSM_Z[j,i+1] <- fsm_data[k,3]
  	FSM_X[j,i+1] <- fsm_data[k,1]
  	FSM_Y[j,i+1] <- fsm_data[k,2]
  	NN_Z[j,i+1] <- nn_data[k,3]
  	NN_X[j,i+1] <- nn_data[k,1]
  	NN_Y[j,i+1] <- nn_data[k,2]
  	HMM_Z[j,i+1] <- hmm_data[k,3]
  	HMM_X[j,i+1] <- hmm_data[k,1]
  	HMM_Y[j,i+1] <- hmm_data[k,2]
  	k=k+inc

        if(FSM_Z[j,i+1] > major_fsm){
                major_fsm = FSM_Z[j,i+1]
                arg_major_fsm = i+1 
        }
        if(NN_Z[j,i+1] > major_nn){
                major_nn = NN_Z[j,i+1]
                arg_major_nn = i+1 
        }
        if(HMM_Z[j,i+1] > major_hmm){
                major_hmm = HMM_Z[j,i+1]
                arg_major_hmm = i+1 
        }
  }

  print(paste("arg major fsm ", arg_major_fsm," major_fsm ",major_fsm))
  major_FSM_z[j] = major_fsm
  mean_FSM_z[j] = mean(FSM_Z[j,0:num_blocks+1])
  standard_FSM_z[j]=sqrt(var(FSM_Z[j,0:num_blocks+1]))
  print(paste("j ", j," mean FSM_z ",mean_FSM_z[j]," std ",
						standard_FSM_z[j]))

  print(paste("arg major nn ", arg_major_nn," major_nn ",major_nn))
  major_NN_z[j] = major_nn
  mean_NN_z[j] = mean(NN_Z[j,0:num_blocks+1])
  standard_NN_z[j]=sqrt(var(NN_Z[j,0:num_blocks+1]))
  print(paste("j ", j," mean NN_z ",mean_NN_z[j]," std ",
						standard_NN_z[j]))

  print(paste("arg major hmm ", arg_major_hmm," major_hmm ",major_hmm))
  major_HMM_z[j] = major_hmm
  mean_HMM_z[j] = mean(HMM_Z[j,0:num_blocks+1])
  standard_HMM_z[j]=sqrt(var(HMM_Z[j,0:num_blocks+1]))
  print(paste("j ", j," mean HMM_z ",mean_HMM_z[j]," std ",
						standard_HMM_z[j]))

  #x11()
  #plot(HMM_X[j,],HMM_Z[j,])
  #lines(HMM_X[j,],HMM_Z[j,])

}


x11()
plot(FSM_Y[1:inc,1],mean_FSM_z)
lines(FSM_Y[1:inc,1],mean_FSM_z)

x11()
plot(FSM_Y[1:inc,1],standard_FSM_z)
lines(FSM_Y[1:inc,1],standard_FSM_z)

x11()
plot(FSM_Y[1:inc,1],major_FSM_z)
lines(FSM_Y[1:inc,1],major_FSM_z)

x11()
plot(NN_Y[1:inc,1],mean_NN_z)
lines(NN_Y[1:inc,1],mean_NN_z)

x11()
plot(NN_Y[1:inc,1],standard_NN_z)
lines(NN_Y[1:inc,1],standard_NN_z)

x11()
plot(NN_Y[1:inc,1],major_NN_z)
lines(NN_Y[1:inc,1],major_NN_z)

x11()
plot(HMM_Y[1:inc,1],mean_HMM_z)
lines(HMM_Y[1:inc,1],mean_HMM_z)

x11()
plot(HMM_Y[1:inc,1],standard_HMM_z)
lines(HMM_Y[1:inc,1],standard_HMM_z)

x11()
plot(HMM_Y[1:inc,1],major_HMM_z)
lines(HMM_Y[1:inc,1],major_HMM_z)

#source("~/robotics/genetics/plot_results.R")
