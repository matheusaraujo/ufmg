rm(list = ls())

source(file='trainadeline.R')

t<-matrix(seq(0,2*pi,0.1*pi),ncol=1)
x<-sin(t)
y<-matrix(4*x+2,ncol=1)

retlist<-trainadeline(x,y,0.01,0.01,50,1)
w<-retlist[[1]]
erro<-retlist[[2]]