pollutantmean <- function(diretorio, poluente, id = 1:332) {
  
  arquivos <- list.files(path = diretorio, full.names = TRUE)
  dados <- data.frame()
  
  for (i in id) {
    dados <- rbind(dados, read.csv(arquivos[i]))
  }
  
  switch(poluente,
   sulfate={
     mean(dados$sulfate, na.rm = TRUE)          
   },
   nitrate={
     mean(dados$nitrate, na.rm = TRUE)
   }
  )
}