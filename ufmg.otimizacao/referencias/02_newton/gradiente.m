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
%   Estima o gradiente de uma função no ponto especificado.
% =========================================================================


function g = gradiente (fun, x)

% Gradiente analítico da função 'fun'
% switch func2str(fun)
%     case 'fobj1'
%         g(1) = 4*(x(1)-2)^3 + 2*(x(1)-2*x(2));
%         g(2) = -4*(x(1)-2*x(2));
%     case 'fobj2'
%         g(1) = -400*x(1)*(x(2)-x(1)^2)^2 - 2*(1-x(1));
%         g(2) = 200*(x(2)-x(1)^2);
%     otherwise
%         disp('Gradiente não definido!')
% end

x = x(:);
delta = 1e-10;
n = length(x);
E = eye(n);
for i=1:n
    g(i)=(feval(fun,x+delta*E(:,i)) - feval(fun,x))/delta;
end
g = g(:);



