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


function grad (fun, xo, e, xlimites)

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
% grad(@fobj1, [+3.0 +3.0], 0.01, [0 4 0 4])
% grad(@fobj2, [-1.0 +1.5], 0.01, [-1.5 1.5 -1.0 1.5])
%


% Contador de iterações do método
k = 0;

% Garante que xo seja um vetor coluna
xo = xo(:);

g = gradiente(fun, xo);     % Estima o grandiente da função no ponto xo
d = -g;                     % Determina a direção de busca

% Estima o valor de 'alpha^*' usando o Algoritmo da Seção Áurea
alpha = get_alpha(fun, xo, d);

% Armazena o caminho percorrido em direção ao ótimo
caminho(k+1,:) = [xo' feval(fun, xo)];

% Imprime o resultado da busca encontrado até a iteração k
percurso(fun, caminho, k, xlimites); 

x = xo;

% Critério de parada: condição necessária de primeira ordem (||g|| = 0)
while (norm(g) >= e)            
    x = x + alpha*d;            % Determina a nova solução        
    g = gradiente(fun, x);      % Calcula o grandiente da função no ponto x
    d = -g;                     % Determina a direção de busca    
    k = k + 1;                  % Atualiza o contador
    
    % Estima um novo valor para 'alpha^*'
    alpha = get_alpha(fun, x, d); 
    
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



