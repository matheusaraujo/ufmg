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
%   Define a função objetivo.
% =========================================================================


function f = fobj2(x)

% Função objetivo 2
f = 100*(x(2)-x(1)^2)^2 + (1-x(1))^2;

