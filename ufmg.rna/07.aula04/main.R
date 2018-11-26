library('plot3D')

rm(list = ls())

source('~/ufmg/rna/07-aula04/treinap.R')

xc1<-matrix(rnorm(100,sd=0.4),ncol=2)+2
xc2<-matrix(rnorm(100,sd=0.4),ncol=2)+4

yc1<-matrix(0,nrow=50,ncol=1)
yc2<-matrix(1,nrow=50,ncol=1)

X = rbind(xc1,xc2)

yd<-rbind(yc1,yc2)

w = treinap(X, yd, 0.1, 0.01, 100, 1)

seqi<-seq(0,6,0.1)
seqj<-seq(0,6,0.1)

M<-matrix(1,nrow=length(seqi),ncol=length(seqj))

ci<-0
cj<-0

for(i in seqi) {
  ci<-ci+1
  cj<-0
  for(j in seqj) {
    cj<-cj+1
    M[ci,cj]<-1*(i*w[[1]][2]+j*w[[1]][3]>=w[[1]][1])
  }
}

persp3D(seqi,seqj,M)