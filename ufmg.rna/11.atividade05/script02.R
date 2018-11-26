# dados de entrada
rm(list = ls())

t<-as.matrix(read.table('Ex2_t'))
x<-as.matrix(read.table('Ex2_x'))
y<-as.matrix(read.table('Ex2_y'))

x1<-x[,1]
x2<-x[,2]
x3<-x[,3]

par(mfrow=c(2,2))
plot(t, x1, type='b', col='red')
plot(t, x2, type='b', col='green')
plot(t, x3, type='b', col='blue')
plot(t, y, type='b', col='orange')

# treinamento
source(file='trainadeline.R')
n<-as.numeric(dim(t)[1])

n_treinamento<-n*0.7
seq_treinamento<-sample(n)
x1_treinamento<-as.matrix(x1[seq_treinamento[1:n_treinamento]])
x2_treinamento<-as.matrix(x2[seq_treinamento[1:n_treinamento]])
x3_treinamento<-as.matrix(x3[seq_treinamento[1:n_treinamento]])
y_treinamento<-as.matrix(y[seq_treinamento[1:n_treinamento]])

x_treinamento<-cbind(x1_treinamento, x2_treinamento, x3_treinamento)

retlist<-trainadeline(x_treinamento,y_treinamento,0.01,0.01,100,1)

wt<-as.matrix(retlist[[1]])
x1_teste<-as.matrix(x1[seq_treinamento[(n_treinamento+1):n]])
x2_teste<-as.matrix(x2[seq_treinamento[(n_treinamento+1):n]])
x3_teste<-as.matrix(x3[seq_treinamento[(n_treinamento+1):n]])
y_teste<-as.matrix(y[seq_treinamento[(n_treinamento+1):n]])

y_validacao<-cbind(1,x1_teste,x2_teste,x3_teste) %*% wt

# calculo do erro
n_teste<-n-n_treinamento
erro<-0
for(i in 1:n_teste)
  erro<-erro + (y_teste[i]-y_validacao[i])^2

erro<-erro/n_teste
erro  

# grafico de comparacao
y_grafico<-cbind(1,x1,x2,x3) %*% wt

par(mfrow=c(1,1))
plot(t,y,type='b',col='gray',ylim=c(-2,10),xlim=c(0,6.5),xlab='',ylab='')
par(new=T)
plot(t,y_grafico,type='b',col='green',ylim=c(-2,10),xlim=c(0,6.5),xlab='',ylab='')
legend(0,6,c("original", "previsto"),col=c("gray","green"),pch=16)

# parametros do modelo
wt