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
%   Define a fun��o objetivo.
% =========================================================================


function f = fobj1(x)

% Fun��o objetivo 1
f = (x(1) - 2).^4 + (x(1) - 2*x(2)).^2;

