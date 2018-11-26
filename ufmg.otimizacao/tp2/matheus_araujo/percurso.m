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
%   Imprime a solução atual, o número de iterações (k), e a trajetória
%   percorrida até que se atinja o ponto de ótimo (probs. com 2 variáveis)
% =========================================================================


function percurso (fun, vetor, k, xlimites)

%
% Sintaxe
% percurso (fun, vetor, k, xlimites)
% fun     : função objetivo
% vetor   : conjunto de soluções determinadas até a iteração k
% k       : iteração corrente
% xlimites: limites inferior e superior das variáveis 
%           [x1min x1max x2min x2max ... xnmin xnmax]
%

% -------------------------------------------------------------------------

tam   = length(xlimites);
[L,C] = size(vetor);

fprintf(1, 'x = [')
fprintf(1, '%+6.4f  ', vetor(L,1:end-1)')
fprintf(1, '\b\b]; \t f(x) = %+6.4f; \t k = %d\n', vetor(L,end),k)
% -------------------------------------------------------------------------

% Esta parte do código é definida apenas para funções com duas variáveis 
% (2D). Caso contrário, o processo de otimização continua, porém, a 
% trajetória das soluções determinadas não é plotada.
if (tam ~= 4)    
    return
end

% -------------------------------------------------------------------------
% Este 'if' é acessado apenas uma vez, com o objetivo de plotar as curvas
% de nível da função objetivo
if (k == 0)
    % fecha a janela corrente
    close
    
    % Plota as curvas de nível da função objetivo    
    deltax = (xlimites(2) - xlimites(1))/30;
    deltay = (xlimites(4) - xlimites(3))/30;
    [x, y] = meshgrid(xlimites(1):deltax:xlimites(2), ...
                      xlimites(3):deltay:xlimites(4));    
    hold on
    z = get_fitness(fun, x, y);      
    cnivel = [linspace(0,vetor(L,end),10) linspace(vetor(L,end),vetor(L,end)+50,10)];
    
    % Plot em 2D
    c = contour(x,y,z,cnivel); clabel(c), grid on
    
    % ou,
    
    % Plot em 3D
    %mesh(x,y,z); box on, view([30 70])
end
% -------------------------------------------------------------------------

% -------------------------------------------------------------------------
% Imprime o processo iterativo
xlabel('x1'), ylabel('x2'), zlabel('f(x)')
plot3 (vetor(:,1), vetor(:,2), vetor(:,3), 'k*-')
axis(xlimites);
%if (k == 0), pause, else pause(0.01), end
% -------------------------------------------------------------------------



