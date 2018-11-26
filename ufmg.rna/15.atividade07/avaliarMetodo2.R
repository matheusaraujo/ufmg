rm(list=ls())

library("RSNNS")

# dados de entrada
x_train<-seq(from=0, to=2*pi, by=0.15)
x_train<-x_train + (runif(length(x_train))-0.5)/5
i <- sample(length(x_train))
x_train <- x_train[i]

y_train <- sin(x_train)
y_train<-y_train + (runif(length(y_train))-0.5)/5

x_test <-seq(from=0, to=2*pi, by=0.01)
y_test <-sin(x_test)

model <- elman(x_train, y_train,
   size = c(8, 8), learnFuncParams = c(0.1), maxit = 500,
   inputsTest = x_test, targetsTest = y_test,
   linOut = TRUE)

n_test<-length(x_test)
erro<-0
for(i in 1:n_test) {
  erro<-erro + (y_test[i]-model$fittedTestValues[i])^2
}

erro<-erro/n_test
erro