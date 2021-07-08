# Estrutura TCC

## Estrutura 

### Teoria de Grafos
- **Vértice** 
  - `V` - objeto atômico, é uma das duas unidades básicas de um grafo;
- **Aresta**
  - `E` - outra unidade básica do grafo, representa um par ordenado de vértices (para os grafos utilizados nesse estudo);
- **Grau** (de um vértice)
  - Número de arestas que incidem sobre um vértice;
    - Grau de saída: número de arestas divergentes de um nó;
    - Grau de entrada: número de arestas convergentes de um nó;
- **Super Grau**
  - _Ainda não encontrei referências para esse conceito na literatura_
  - É a definição "recursiva" do grau de um vértice. O grau de um nó é a soma de todos os graus dos nós que incidem sobre ele;
  - _Esse conceito será útil para calcular os vértices "chave" em um grafo de maturidade_
- **Grafo**
  - `G(V,E)` - estrutura formada por um conjunto não vazio de vértices `V` e um conjunto de arestas `E`;
- **Arestas múltiplas**
  - Arestas que possuem o mesmo par ordenado de vértices;
- **Multigrafo**
  - Grafo que possui arestas múltiplas;

#### Definições
  - **Redes de fluxo**
    - "Imagine um material percorrendo um sistema desde uma fonte onde o material é produzido até um sorvedouro, onde ele é consumido; A fonte produz o material a alguma taxa fixa, e o sorvedouro consome o material à mesma taxa. O _fluxo_ do material em qualquer ponto no sistema é intuitivamente ataxa pela qual o material se movo" (Cormen)
    - _Acredito que os algoritmos de redes de fluxo podem ser adaptados para cálculos de como o "conhecimento flui" pelo modelo de maturidade.
  - **Componentes conexas**
    - "Um grafo é conexo se cada um de seus vértices está _ao alcance_ de um dos demais." Uma componente conexa é um subgrafo conexo dentro de um grafo.
    - _Esse conceito pode ser útil para encontrar conjuntos isolados de disciplinas, no exemplo do grafo das disciiplinas de graduação._
  - **Ordenação topológica**
    - É uma ordenação linear dos vértices de um grafo em que cada vértice vem antes de todos os nós para os quais ele tenha aresta de saída.
    - _Pode ser útil para calcular sequenciamento de arestas_

### Gestão do Conhecimento
- **Capacidade**
  - Habilidade física ou mental de um indivíduo ou sistema
- **Maturidade**
  - Conjunto de capacidades
- **Modelos de maturidade**
  - Representação do conjunto de capacidades do indivíduo ou sistema
  - Modelos de maturidade conhecidos:
    - CMMI
    - Modelo de maturidade DevOps
    - The Agility Maturity Map - Packlick
    - Disciplinas da Graduação em Engenharia de Sistemas
    - ...

**_Necessário fazer mais pesquisas_**

### Pensamento sistêmico
  
- Elements
- Interconnections
- Stock
- Flow
- Purpose

#### Archetypes
  - Success to Successfull
  - Seeking the wrong goal
  - Drigt to Low Performance

**_Necessário descrever os conceitos levantados_**

### Relações

| Teoria de Grafos | Pensamento sistêmico | Gestão do Conhecimento              |
|------------------|----------------------|-------------------------------------|
| Vértice          | Element              | Capacidade                          |
| Aresta           | Interconnections     | Capacidades habilitando capacidades |
| Fluxo            | Flow                 | Amadurecimento                      |
| Grafo            | Sistema              | Maturidade                          |
| ?                | Purpose              | ?                                   |


### Principais referências
- Thinking in Systems, Donella H. Meadows
- Algoritmos, Thomas E. Cormen
- Maturity in Agile Software Development, Rafaela M. Fontana