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


function f = fobj2(x)

% Fun��o objetivo 2
f1 = x(1)^2 + x(2)^2;
f2 = (x(1)-1)^2 + (x(2)-0.5)^2;
f3 = (x(1)-0.5)^2 + (x(2)-1)^2;

f = [f1 f2 f3]';

