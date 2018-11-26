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


function f = fobj3(x)

% Fun��o objetivo 3
f1 = x(1);
f2 = x(2);

g(1) = -x(1);
g(2) = -x(2);
g(3) = -x(1)^4 - x(2) + 1;

f1 = f1 + 100 * sum(max(0,g).^2);
f2 = f2 + 100 * sum(max(0,g).^2);

f = [f1 f2]';