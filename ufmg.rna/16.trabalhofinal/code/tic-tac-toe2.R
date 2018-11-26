rm(list=ls())
require("RSNNS")

tte<-read.table("tic-tac-toe.data", header=F, sep=",") 

tte <- tte[sample(1:nrow(tte), length(1:nrow(tte))), 1:ncol(tte)]

tteValuesxob <- tte[,1:9]
tteValues <- data.matrix(tteValuesxob)
tteTargets <- tte[,10]
tteDecTargets <- decodeClassLabels(tteTargets)

tte <- splitForTrainingAndTest(tteValues, tteDecTargets, ratio = 0.15)
tte <- normTrainingAndTestSet(tte)

rna <- mlp(tte$inputsTrain, tte$targetsTrain, 
  size = 5, learnFunc="SCG", learnFuncParams=c(0, 0, 0, 0), maxit = 50, 
  inputsTest = tte$inputsTest, targetsTest = tte$targetsTest)

predictions <- predict(rna, tte$inputsTest)
matrix = confusionMatrix(tte$targetsTest, predictions)

sum(diag(matrix))/sum(matrix)