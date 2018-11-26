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


function grad (fun, xo, e, xlimites)

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
% grad(@fobj1, [+3.0 +3.0], 0.01, [0 4 0 4])
% grad(@fobj2, [-1.0 +1.5], 0.01, [-1.5 1.5 -1.0 1.5])
%


% Contador de itera��es do m�todo
k = 0;

% Garante que xo seja um vetor coluna
xo = xo(:);

g = gradiente(fun, xo);     % Estima o grandiente da fun��o no ponto xo
d = -g;                     % Determina a dire��o de busca

% Estima o valor de 'alpha^*' usando o Algoritmo da Se��o �urea
alpha = get_alpha(fun, xo, d);

% Armazena o caminho percorrido em dire��o ao �timo
caminho(k+1,:) = [xo' feval(fun, xo)];

% Imprime o resultado da busca encontrado at� a itera��o k
percurso(fun, caminho, k, xlimites); 

x = xo;

% Crit�rio de parada: condi��o necess�ria de primeira ordem (||g|| = 0)
while (norm(g) >= e)            
    x = x + alpha*d;            % Determina a nova solu��o        
    g = gradiente(fun, x);      % Calcula o grandiente da fun��o no ponto x
    d = -g;                     % Determina a dire��o de busca    
    k = k + 1;                  % Atualiza o contador
    
    % Estima um novo valor para 'alpha^*'
    alpha = get_alpha(fun, x, d); 
    
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



