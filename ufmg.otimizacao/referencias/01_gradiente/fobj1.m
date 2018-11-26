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


function f = fobj1(x)

% Função objetivo 1
f = (x(1) - 2).^4 + (x(1) - 2*x(2)).^2;

