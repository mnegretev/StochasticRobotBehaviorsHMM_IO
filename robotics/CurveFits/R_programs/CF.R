#install.packages("plotly")
#install.packages("ramify")

#source("~/robotics/CurveFits/R_programs/CF.R")

#library(plotly)
#packageVersion('plotly')
#library("ramify")


test_1 = read.table("../sensor_data/test_4.dat")
x <- test_1[,1]
y <- test_1[,2]

#y <- y / mean(x)
#x <- x / mean(x)

x11()
plot(x)
lines(x)
x11()
plot(y)
lines(y)

max=max(y)
min=min(y)
mean=mean(y)
standard=sqrt(var(y))
cat("\n-+-+-+-+- Results +-+-+-+-+-+-+-+-+-+\n")
cat("Max. ",max,"\n")
cat("Min. ",min,"\n")
cat("Mean ",mean,"\n")
cat("Standard Dev. ",standard,"\n")
cat("-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n\n")
x11()
hist(y)
abline(v=mean(y),col="blue",lw=2)
mean(y)
abline(v=mean(y)-sd(y),col="red",lw=2)
abline(v=mean(y)+sd(y),col="red",lw=2)



#----------------------------------------------

m1=lm(formula = x ~ I(y))
#summary(m1)
a0=m1$coef[1]
a1=m1$coef[2]
yc1 = a0 + a1*y 
x11()
plot(yc1)
lines(yc1)

#-----------------------------------------

m2=lm(formula = x ~ I(y)+I(y^2))
#summary(m2)
a0=m2$coef[1]
a1=m2$coef[2]
a2=m2$coef[3]
yc2 = a0 + a1*y + a2*y^2
x11()
plot(yc2)
lines(yc2)

#-------------------------------------------
m3=lm(formula = x ~ I(y)+I(y^2)+I(y^3))
#summary(m3)
a0=m3$coef[1]
a1=m3$coef[2]
a2=m3$coef[3]
a3=m3$coef[4]
yc3 = a0 + a1*y + a2*y^2 + a3*y^3
x11()
plot(yc3)
lines(yc3)

#----------------------------------------------
m4=lm(formula = x ~ I(y)+I(y^2)+I(y^3)+I(y^4))
#summary(m4)
a0=m4$coef[1]
a1=m4$coef[2]
a2=m4$coef[3]
a3=m4$coef[4]
a4=m4$coef[5]
#yc4 = a0 + a1*y + a2*y^2 + a3*y^3 + a4*y^4
#x11()
#plot(yc4)
#lines(yc4)


#----------------------------------------------
x11()
z=x-y
h=hist(z)
abline(v=mean(z),col="blue",lw=2)
mean(z)
abline(v=mean(z)-sd(z),col="red",lw=2)
abline(v=mean(z)+sd(z),col="red",lw=2)
sd(z)





