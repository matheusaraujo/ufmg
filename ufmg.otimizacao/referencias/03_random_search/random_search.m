%==========================================================================
% Universidade Federal de Minas Gerais
% Escola de Engenharia da UFMG
% Depto. de Engenharia Elétrica
%
% Autores:
%   Jaime A. Ramírez
%   Lucas S. Batista
%
% Atualização: 16/04/2013
%
% Nota:
%   Aproxima o ponto de ótimo (minimização) de um problema irrestrito
%   usando o Algoritmo do Gradiente (VERSÃO SIMPLES - MERAMENTE ILUSTRATIVA).
% =========================================================================


function random_search (fun, xo, nfe, xlimites)

%
% Sintaxe
% grad(fun, xo, e, xlimites)
% fun     : função objetivo
% xo      : vetor solução inicial [xo1 xo2 ... xon]
% e       : precisão adotada pelo usuário
% xlimites: limites inferior e superior das variáveis 
%           [x1min x1max x2min x2max ... xnmin xnmax]
%
% Exemplo
% random_search(@fobj1, [+3.0 +3.0], 200, [0 4 0 4])
% random_search(@fobj2, [-1.0 +1.5], 1000, [-1.5 1.5 -1.0 1.5])
%


% Contador de iterações do método
k = 0;

% Garante que xo seja um vetor coluna
xo = xo(:);

% numero de varias de decisao
n = length(xo);

% quantidade de pontos gerados a cada iteracao
N = 10;

% limites inferior e superior
lb = xlimites(1:2:end);
ub = xlimites(2:2:end);

sigma = 0.05;

% armazena o caminho percorrido em direção ao ótimo
caminho(k+1,:) = [xo' feval(fun, xo)];

% imprime o resultado da busca encontrado até a iteração k
percurso(fun, caminho, k, xlimites); 

x = xo;
jx = feval(fun, x);

% Critério de parada
while (k*N < nfe)   
    
    % gera N amostras aleatorias em torno de x
    for i = 1:N
        delta = sigma * (ub(:) - lb(:)).*randn(n,1);
        y(:,i) = x + delta;
        jy(i) = feval(fun,y(:,i));
    end
    
    % armazena a melhor alternativa em x
    y =  [x   y];
    jy = [jx jy];
    
    [b,jb] = min(jy);
    x = y(:,jb);
    jx = b;
    
    % atualiza o contador
    k = k + 1;                  
    
    % Armazena o caminho percorrido em direção ao ótimo
    caminho(k+1,:) = [x' feval(fun, x)];
    
    % Atualiza o percusso em direção ao ótimo
    percurso(fun, caminho, k, xlimites);
    
end
fprintf('\n')

figure
plot(0:k,caminho(:,end),'k-','linewidth',2)
xlabel('Número de iterações')
ylabel('Valor da função objectivo')