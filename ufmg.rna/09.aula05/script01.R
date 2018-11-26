rm(list = ls())
data(iris)

# 1 variavel
#plot(iris$Petal.Width[1:50],matrix(0,ncol=1,nrow=50),xlim=c(0,3),col='red',xlab='',ylab='')
#par(new=T)
#plot(iris$Petal.Width[51:100],matrix(0,ncol=1,nrow=50),xlim=c(0,3),col='blue',xlab='',ylab='')
#par(new=T)
#plot(iris$Petal.Width[101:150],matrix(0,ncol=1,nrow=50),xlim=c(0,3),col='black',xlab='',ylab='')

# 2 variaveis
data(iris)
plot(iris$Petal.Width[1:50],iris$Petal.Length[1:50],xlim=c(0,3),ylim=c(0,8),col='red',xlab='',ylab='')
par(new=T)
plot(iris$Petal.Width[51:100],iris$Petal.Length[51:100],xlim=c(0,3),ylim=c(0,8),col='blue',xlab='',ylab='')
par(new=T)
plot(iris$Petal.Width[101:150],iris$Petal.Length[101:150],xlim=c(0,3),ylim=c(0,8),col='black',xlab='',ylab='')