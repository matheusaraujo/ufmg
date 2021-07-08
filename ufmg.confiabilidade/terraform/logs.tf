resource "aws_cloudwatch_log_group" "dotnet-webapi-log-group" {
  name              = "/ecs/dotnet-webapi"
  retention_in_days = var.log_retention_in_days
}

resource "aws_cloudwatch_log_stream" "dotnet-webapi-log-stream" {
  name           = "dotnet-webapi-log-stream"
  log_group_name = aws_cloudwatch_log_group.dotnet-webapi-log-group.name
}
