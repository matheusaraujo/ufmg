rm(list=ls())

library("RSNNS")

N<-200
x<-runif(N,0,2*pi)
y<-sin(x)+rnorm(N,0,0.1)

rede = mlp(x, y, size=5, maxit = 1000, 
      initFunc = "Randomize_Weights",
      initFuncParams = c(-0.3, 0.3), learnFunc = "Rprop",
      learnFuncParams = c(0.1, 0.1), updateFunc = "Topological_Order",
      updateFuncParams = c(0), hiddenActFunc = "Act_Logistic",
      shufflePatterns = TRUE, linOut = TRUE)
      

xt<-seq(0,2*pi,0.1)
yseno<-sin(xt)
yhat<-2*(predict(rede,as.matrix(xt))*0.5)

plot(xt, yseno, type='l', ylim=c(-1,1), xlab='', ylab='')
par(new=T)
plot(xt, yhat, type='p', col='red', ylim=c(-1,1), xlab='', ylab='')