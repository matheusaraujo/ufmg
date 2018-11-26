rm(list = ls())

x<-matrix(c(0.4,1.2,1),ncol=1)
w<-matrix(c(-0.21,3.35,0.5),ncol=1)

#w+as.numeric(0.1*(4.64-t(w)%*%x)*x)

yhat<-t(w)%*%x

w+(0.1*(4.64-as.numeric(yhat)))

#t1<-c(-0.21,3.35,0.5)
#t2<-0.1
#t3<-4.640
#t4<-4.436
#t5<-c(0.4,1.2,1)

#t1+t2*(t3-t4)*t5