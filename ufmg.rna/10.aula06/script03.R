rm(list = ls())
source(file='trainadeline.R')

t<-seq(0,2*pi,0.1*pi)
x1<-matrix(sin(t)+cos(t),ncol=1)
x2<-matrix(tanh(t),ncol=1)
x3<-matrix(sin(4*t),ncol=1)
x4<-matrix(abs(sin(t)),ncol=1)

y<-x1+2*x2+0.8*x3+3.2*x4+pi/2

x<-cbind(x1,x2,x3,x4)
retlist<-trainadeline(x,y,0.01,0.01,100,1)
w<-retlist[[1]]
erro<-retlist[[2]]

#par(mfrow=c(3,2))
#plot(t,x1,type='b')
#plot(t,x2,type='b')
#plot(t,x3,type='b')
#plot(t,x4,type='b')
#plot(t,y,type='b')

#par(mfrow=c(1,1))
#plot(erro)

tteste<-seq(0,2*pi,0.01*pi)
x1t<-matrix(sin(tteste)+cos(tteste),ncol=1)
x2t<-matrix(tanh(tteste),ncol=1)
x3t<-matrix(sin(4*tteste),ncol=1)
x4t<-matrix(abs(sin(tteste)),ncol=1)

xt<-cbind(1,x1t,x2t,x3t,x4t)

yt<-xt%*%w

plot(t,y,type='b',col='red',ylim=c(2,8))
par(new=T)
plot(tteste,yt,type='l',col='black',ylim=c(2,8))
