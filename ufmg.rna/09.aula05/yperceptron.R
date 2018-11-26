yperceptron<-function(xvec, w, par)
{
  if(par == 1)
    xvec <- cbind(-1,xvec)
    
  u <-  xvec %*% w
  y <- 1.0*((u>=0))
  return ((as.matrix(y)))
}