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
%   Retorna uma matriz z contendo dados para plotar a função objetivo.
% =========================================================================


function z = get_fitness (fun, x, y)

%
% Sintaxe
% z = get_fitness (fun, x, y)
% fun: função objetivo
% x,y: matrizes obtidas por meio do comando 'meshgrid'
%

[L,C] = size(x);
for i = 1:L
    for j = 1:C        
        z(i,j) = feval(fun, [x(i,j) y(i,j)]);
    end
end



