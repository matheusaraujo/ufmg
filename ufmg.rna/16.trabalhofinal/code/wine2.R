rm(list=ls())
require("RSNNS")

wine<-read.table("wine.data", header=F, sep=",") 

wine <- wine[sample(1:nrow(wine), length(1:nrow(wine))), 1:ncol(wine)]

wineValues <- wine[,2:13]
wineTargets <- wine[,1]
wineDecTargets <- decodeClassLabels(wineTargets)

wine <- splitForTrainingAndTest(wineValues, wineDecTargets, ratio = 0.15)
wine <- normTrainingAndTestSet(wine)

rna <- mlp(wine$inputsTrain, wine$targetsTrain, 
  size = 5, 
  learnFunc="SCG", learnFuncParams=c(0, 0, 0, 0),
  maxit = 50, 
  inputsTest = wine$inputsTest, targetsTest = wine$targetsTest)

predictions <- predict(rna, wine$inputsTest)
matrix = confusionMatrix(wine$targetsTest, predictions)

sum(diag(matrix))/sum(matrix)