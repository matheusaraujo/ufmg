rm(list = ls())

source(file='yperceptron.R')
source(file='trainperceptron.R')

data(iris)

ntrain<-20

# x1 e x2

# classes 1 e 2
xc1<-as.matrix(iris[1:50,1:4])
xc2<-as.matrix(iris[51:100,1:4])

# classes 1 e 3
#xc1<-as.matrix(iris[1:50,1:4])
#xc2<-as.matrix(iris[101:150,1:4])

# classes 2 e 3
#xc1<-as.matrix(iris[51:100,1:4])
#xc2<-as.matrix(iris[101:150,1:4])

# x1 e y1 de treinamento
seqc1<-sample(50)
xc1treina<-xc1[seqc1[1:ntrain],]
yc1treina<-matrix(0,nrow=ntrain)

# x2 e y2 de treinamento
seqc2<-sample(50)
xc2treina<-xc2[seqc2[1:ntrain],]
yc2treina<-matrix(1,nrow=ntrain)

# x1 de teste
xc1teste<-xc1[seqc1[(ntrain+1):50],]
yc1teste<-matrix(0,nrow=(50-ntrain))

xc2teste<-xc2[seqc2[(ntrain+1):50],]
yc2teste<-matrix(1,nrow=(50-ntrain))

xin<-as.matrix(rbind(xc1treina,xc2treina))
yd<-rbind(yc1treina,yc2treina)

xinteste<-as.matrix(rbind(xc1teste,xc2teste))
yteste<-rbind(yc1teste,yc2teste)

retlist<-trainperceptron(xin,yd,0.1,0.01,100,1)

wt<-as.matrix(retlist[[1]])

yt<-yperceptron(xinteste,wt,1)
erroteste<-yteste-yt
hist(erroteste)