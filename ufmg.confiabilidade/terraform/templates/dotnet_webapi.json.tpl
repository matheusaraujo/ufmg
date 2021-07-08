[{
    "name": "dotnet-webapi",
    "image": "${docker_image_url_dotnet_webapi}",
    "essential": true,
    "cpu": 1024,
    "memory": 1024,
    "links": [],
    "portMappings": [{
        "containerPort": 80,
        "hostPort": 0,
        "protocol": "tcp"
    }],
    "command": ["dotnet", "dotnet-webapi.dll"],
    "environment": [],
    "logConfiguration": {
        "logDriver": "awslogs",
        "options": {
            "awslogs-group": "/ecs/dotnet-webapi",
            "awslogs-region": "${region}",
            "awslogs-stream-prefix": "dotnet-webapi-log-stream"
        }
    }
}]