rm(list=ls())

library(neuralnet)

x_train<-seq(from=0, to=2*pi, by=0.15)
x_train<-x_train + (runif(length(x_train))-0.5)/5
y_train <- sin(x_train)
y_train<-y_train + (runif(length(y_train))-0.5)/5

dff<-data.frame(x=x_train,y=y_train)

set.seed(120917)
nn<-neuralnet(y~x,data=dff,linear.output=TRUE,hidden=c(3),lifesign="full",threshold=0.01,stepmax=5000)

x_test<-seq(0,2*pi,by=0.01)
y_test<-sin(x_test)

nny<-compute(nn,x_test)

n_test<-length(x_test)
erro<-0
for(i in 1:n_test) {
  erro<-erro + (y_test[i]-nny$net.result[i])^2
}

erro<-erro/n_test
erro