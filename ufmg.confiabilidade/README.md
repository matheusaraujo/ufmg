# performance-test

teste de performances em apis hospedadas no `aws ecs`

## ferramentas utilizadas

### dotnet webapi

+ api utilizando `dotnet core 5.0` respondendo HTTP 200 na rota `/performance-test`
+ imagem docker hospedada em https://hub.docker.com/repository/docker/matheussaraujo/

```bash
docker build -t matheussaraujo/dotnet-webapi:latest .
docker push matheussaraujo/dotnet-webapi:latest
```

### terraform

+ infra as code, provisiona a infra utilizando código

```bash
terraform init
terraform plan
terraform apply
terraform destroy
```

### taurus

+ ferramenta para testes de performance
```bash
bzt basic_test.yml
```

---

**to-do**
- desenhar big picture da arquitetura aws
- criar variáveis tf para cpu e memória
- estruturar testes
