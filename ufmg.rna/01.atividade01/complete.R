complete <- function(diretorio, id = 1:332) {
  
  arquivos <- list.files(path = diretorio, full.names = TRUE)
  dados <- data.frame()
  completos <- data.frame()
  nobs <- data.frame();
  
  for (i in id) { 
    dados <- (read.csv(arquivos[i],header=TRUE))
    nobs <- sum(complete.cases(dados))
    completos <- rbind(completos, data.frame(i,nobs))
  }
  return(completos)
}