#source("~/robotics/genetics/plot_results.R")
install.packages("plotly")
install.packages("ramify")



library(plotly)
packageVersion('plotly')
library("ramify")


n <- 9
k <- seq(0, n, by =1)
plot(k,dbinom(k,n,0.7))
n <- 3
k <- seq(0, n, by =1)
plot(k,dbinom(k,n,0.7))
plot(k,dbinom(k,n,0.6))
plot(k,dbinom(k,n,0.4))
lines(k,dbinom(k,n,0.6))
lines(k,dbinom(k,n,0.7))
lines(k,dbinom(k,n,0.8))
n <- 4
k <- seq(0, n, by =1)
plot(k,dbinom(k,n,0.6))
lines(k,dbinom(k,n,0.8))
plot(k,dbinom(k,n,0.8))
lines(k,dbinom(k,n,0.8))
plot(k,dbinom(k,n,0.5))
lines(k,dbinom(k,n,0.5))
lines(k,dbinom(k,n,0.6))
lines(k,dbinom(k,n,0.7))
plot(k,dbinom(k,n,0.7))
lines(k,dbinom(k,n,0.7))

