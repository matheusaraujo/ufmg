rm(list=ls())
require("RSNNS")

letters<-read.table("letter-recognition.data", header=F, sep=",") 

letters <- letters[sample(1:nrow(letters), length(1:nrow(letters))), 1:ncol(letters)]

lettersValues <- letters[,2:17]
lettersTargets <- letters[,1]
lettersDecTargets <- decodeClassLabels(lettersTargets)

letters <- splitForTrainingAndTest(lettersValues, lettersDecTargets, ratio = 0.15)
letters <- normTrainingAndTestSet(letters)

rna <- mlp(letters$inputsTrain, letters$targetsTrain, 
  size = 10, learnFuncParams = 0.1, maxit = 100, 
  inputsTest = letters$inputsTest, targetsTest = letters$targetsTest)

predictions <- predict(rna, letters$inputsTest)
matrix = confusionMatrix(letters$targetsTest, predictions)

sum(diag(matrix))/sum(matrix)

