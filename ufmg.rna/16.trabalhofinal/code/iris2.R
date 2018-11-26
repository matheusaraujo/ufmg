rm(list=ls())
require("RSNNS")

iris<-read.table("iris.data", header=F, sep=",") 

iris <- iris[sample(1:nrow(iris), length(1:nrow(iris))), 1:ncol(iris)]

irisValues <- iris[,1:4]
irisTargets <- iris[,5]
irisDecTargets <- decodeClassLabels(irisTargets)

iris <- splitForTrainingAndTest(irisValues, irisDecTargets, ratio = 0.15)

iris <- normTrainingAndTestSet(iris)

rna <- mlp(iris$inputsTrain, iris$targetsTrain,
  learnFunc="SCG", learnFuncParams=c(0, 0, 0, 0),
  size = 5, maxit = 50, 
  inputsTest = iris$inputsTest, targetsTest = iris$targetsTest)

predictions <- predict(rna, iris$inputsTest)
matrix = confusionMatrix(iris$targetsTest, predictions)

sum(diag(matrix))/sum(matrix)
