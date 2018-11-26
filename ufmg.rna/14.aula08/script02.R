data("iris")
iris <- iris[sample(1:nrow(iris), length(1:nrow(iris))), 1:ncol(iris)]

irisValues <- iris[, 1:4]
irisTargets <- iris[, 5]
irisDecTargets <- decodeClassLabels(irisTargets)
iris <- splitForTrainingAndTest(irisValues, irisDecTargets, ratio = 0.15)
iris <- normTrainingAndTestSet(iris)

model <- mlp(iris$inputsTrain, iris$targetsTrain, size = 5,
  learnFuncParams = 0.1, maxit = 60, inputsTest = iris$inputsTest,
  targetsTest = iris$targetsTest)

predictions <- predict(model, iris$inputsTest)

plotIterativeError(model)
plotRegressionError(predictions[, 2], iris$targetsTest[, 2], pch = 3)
plotROC(fitted.values(model)[, 2], iris$targetsTrain[, 2])
plotROC(predictions[, 2], iris$targetsTest[, 2])