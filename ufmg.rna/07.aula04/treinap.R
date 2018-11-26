treinap <- function (xin, yd, eta, tol, maxepocas, par)
{
  dimxin<-dim(xin)
  N<-dimxin[1] # numero de amostras
  n<-dimxin[2] # dimensao de entrada
  
  # adiciona ou nao termo de polarizacao ao vetor de treinamento w
  if (par==1) {
    wt<-as.matrix(runif(n+1)-0.5)
    xin<-cbind(-1,xin)
  }
  else {
    wt<-as.matrix(runif(n)-0.5)
  }
  
  nepocas<-0 # contador de epocas
  eepoca<-tol+1 # acumulador de erro de epocas
  evec<-matrix(nrow=1,ncol=maxepocas) # vetor de erro de epocas
  
  # laco principal de treinamento
  while((nepocas<maxepocas) && (eepoca>tol)) {
    ei2<-0
    xseq<-sample(N) # sequencia aleatoria de treinamento
    
    for(i in 1:N) {
      
      irand<-xseq[i] # amostra dado da sequencia aleatoria
      
      yhati<-1.0*((xin[irand,]%*%wt) >= 0) # calcula saida do perceptron
      
      ei<-yd[irand]-yhati
      dw<-eta*ei*xin[irand,]
      wt<-wt+dw # ajusta vetor de pesos
      ei2<-ei2+ei*ei # acumula erro por epoca
    }
    
    nepocas<-nepocas+1
    evec[nepocas]<-ei2/N
    eepoca<-evec[nepocas]
  }
  
  retlist<-list(wt,evec[1:nepocas])
  return(retlist)
}