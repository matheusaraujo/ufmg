rm(list=ls())
require("RSNNS")

be<-read.table("balance-scale.data", header=F, sep=",") 

be <- be[sample(1:nrow(be), length(1:nrow(be))), 1:ncol(be)]

beValues <- be[,2:5]
beTargets <- be[,1]
beDecTargets <- decodeClassLabels(beTargets)

be <- splitForTrainingAndTest(beValues, beDecTargets, ratio = 0.15)
be <- normTrainingAndTestSet(be)

rna <- mlp(be$inputsTrain, be$targetsTrain, 
  size = 5, learnFunc="SCG", learnFuncParams=c(0, 0, 0, 0), maxit = 50, 
  inputsTest = be$inputsTest, targetsTest = be$targetsTest)

predictions <- predict(rna, be$inputsTest)
matrix = confusionMatrix(be$targetsTest, predictions)

matrix

sum(diag(matrix))/sum(matrix)