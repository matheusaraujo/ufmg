# dados de entrada
rm(list = ls())

t<-as.matrix(read.table('Ex1_t'))
x<-as.matrix(read.table('Ex1_x'))
y<-as.matrix(read.table('Ex1_y'))

plot(t,x,type='b',col='blue',ylim=c(-1,1),xlim=c(0,6),xlab='',ylab='')
par(new=T)
plot(t,y,type='b',col='red',ylim=c(-1,1),xlim=c(0,6),xlab='',ylab='')
legend(0,0.25,c("entrada", "saida"),col=c("blue","red"),pch=16)

# treinamento
source(file='trainadeline.R')

n<-as.numeric(dim(x)[1])

n_treinamento<-n*0.7
seq_treinamento<-sample(n)
x_treinamento<-as.matrix(x[seq_treinamento[1:n_treinamento]])
y_treinamento<-as.matrix(y[seq_treinamento[1:n_treinamento]])

retlist<-trainadeline(x_treinamento,y_treinamento,0.01,0.01,100,1)

wt<-as.matrix(retlist[[1]])
x_teste<-as.matrix(x[seq_treinamento[(n_treinamento+1):n]])
y_teste<-as.matrix(y[seq_treinamento[(n_treinamento+1):n]])
y_validacao<-cbind(1,x_teste) %*% wt

# calculo do erro
n_teste<-n-n_treinamento
erro<-0
for(i in 1:n_teste)
  erro<-erro + (y_teste[i]-y_validacao[i])^2

erro<-erro/n_teste
erro  

# grafico de comparacao
y_grafico<-cbind(1,x) %*% wt

plot(t,y,type='b',col='gray',ylim=c(0,1),xlim=c(0,6),xlab='',ylab='')
par(new=T)
plot(t,y_grafico,type='b',col='green',ylim=c(0,1),xlim=c(0,6),xlab='',ylab='')
legend(0,0.25,c("original", "previsto"),col=c("gray","green"),pch=16)

# parametros do modelo
wt
