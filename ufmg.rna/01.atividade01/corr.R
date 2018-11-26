corr <- function(diretorio, threshold = 0) {
  
  source("complete.R")
  
  completos <- complete(diretorio)
  casosAbaixoThreshold <- completos[completos$nobs > threshold,1]
  arquivos <- list.files(path = diretorio, full.names = TRUE)
  correlacoes <- rep(NA,length(casosAbaixoThreshold))
  
  for (i in casosAbaixoThreshold) {
    dadosArquivo <- (read.csv(arquivos[i]))
    completos <- complete.cases(dadosArquivo)
    dadoValidoSulfato <- dadosArquivo[completos, 2]
    dadoValidoNitrato <- dadosArquivo[completos, 3]
    correlacoes[i] <- cor(x = dadoValidoSulfato, y = dadoValidoNitrato)
  }
  
  correlacoes <- correlacoes[complete.cases(correlacoes)]
}