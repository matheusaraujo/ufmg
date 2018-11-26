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
%   Imprime a solu��o atual, o n�mero de itera��es (k), e a trajet�ria
%   percorrida at� que se atinja o ponto de �timo (probs. com 2 vari�veis)
% =========================================================================


function percurso (fun, vetor, k, xlimites)

%
% Sintaxe
% percurso (fun, vetor, k, xlimites)
% fun     : fun��o objetivo
% vetor   : conjunto de solu��es determinadas at� a itera��o k
% k       : itera��o corrente
% xlimites: limites inferior e superior das vari�veis 
%           [x1min x1max x2min x2max ... xnmin xnmax]
%

% -------------------------------------------------------------------------

tam   = length(xlimites);
[L,C] = size(vetor);

fprintf(1, 'x = [')
fprintf(1, '%+6.4f  ', vetor(L,1:end-1)')
fprintf(1, '\b\b]; \t f(x) = %+6.4f; \t k = %d\n', vetor(L,end),k)
% -------------------------------------------------------------------------

% Esta parte do c�digo � definida apenas para fun��es com duas vari�veis 
% (2D). Caso contr�rio, o processo de otimiza��o continua, por�m, a 
% trajet�ria das solu��es determinadas n�o � plotada.
if (tam ~= 4)    
    return
end

% -------------------------------------------------------------------------
% Este 'if' � acessado apenas uma vez, com o objetivo de plotar as curvas
% de n�vel da fun��o objetivo
if (k == 0)
    % fecha a janela corrente
    close
    
    % Plota as curvas de n�vel da fun��o objetivo    
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



