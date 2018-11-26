%==========================================================================
% Universidade Federal de Minas Gerais
% Escola de Engenharia da UFMG
% Depto. de Engenharia El�trica
%
% Autores:
%   Jaime A. Ram�rez
%   Lucas S. Batista
%
% Atualiza��o: 16/04/2013
%
% Nota:
%   Aproxima o ponto de �timo (minimiza��o) de um problema irrestrito
%   usando o Algoritmo do Gradiente (VERS�O SIMPLES - MERAMENTE ILUSTRATIVA).
% =========================================================================


function random_search (fun, xo, nfe, xlimites)

%
% Sintaxe
% grad(fun, xo, e, xlimites)
% fun     : fun��o objetivo
% xo      : vetor solu��o inicial [xo1 xo2 ... xon]
% e       : precis�o adotada pelo usu�rio
% xlimites: limites inferior e superior das vari�veis 
%           [x1min x1max x2min x2max ... xnmin xnmax]
%
% Exemplo
% random_search(@fobj1, [+3.0 +3.0], 200, [0 4 0 4])
% random_search(@fobj2, [-1.0 +1.5], 1000, [-1.5 1.5 -1.0 1.5])
%


% Contador de itera��es do m�todo
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

% armazena o caminho percorrido em dire��o ao �timo
caminho(k+1,:) = [xo' feval(fun, xo)];

% imprime o resultado da busca encontrado at� a itera��o k
percurso(fun, caminho, k, xlimites); 

x = xo;
jx = feval(fun, x);

% Crit�rio de parada
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
    
    % Armazena o caminho percorrido em dire��o ao �timo
    caminho(k+1,:) = [x' feval(fun, x)];
    
    % Atualiza o percusso em dire��o ao �timo
    percurso(fun, caminho, k, xlimites);
    
end
fprintf('\n')

figure
plot(0:k,caminho(:,end),'k-','linewidth',2)
xlabel('N�mero de itera��es')
ylabel('Valor da fun��o objectivo')