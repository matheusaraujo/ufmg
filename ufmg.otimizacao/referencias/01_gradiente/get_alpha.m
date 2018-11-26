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
%   Estima o valor ótimo de 'alpha'.
% =========================================================================


function alpha = get_alpha(fun, xo, d)

% switch func2str(fun)
%     case 'fobj1'
%         alpha = 0.1;
%     case 'fobj2'
%         alpha = 0.001;
%     otherwise
%         disp('Função não definida!')

% Algoritmo 1 %

a = 0;
s = 1e-2;
b = s;
theta_A = feval(fun,xo);
theta_B = feval(fun,xo+b*d);
nfe = 2;

while theta_B < theta_A
    a = b;
    theta_A = theta_B;
    b = b * 2;
    theta_B = feval(fun, xo+b*d);
    nfe = nfe + 1;
end

if nfe <= 3 
    a = 0;
else
    a = a / 2;
end

% Algoritmo 2 %

r_a = 0.618;

x_a = b - r_a * (b - a);
x_b = a + r_a * (b - a);

theta_A = feval(fun, xo+x_a);
theta_B = feval(fun, xo+x_b);

e = 1e-3;

while b - a > e
    if theta_A > theta_B
        a = x_a;
        x_a = x_b;
        x_b = a + 0.618 * (b - a);
        theta_A = theta_B;
        theta_B = feval(fun, xo+x_b);
    else
        b = x_b;
        x_b = x_a;
        x_a = b - 0.618 * (b - a);
        theta_B = theta_A;
        theta_A = feval(fun, xo+x_a);
    end
end

alpha = (a + b) / 2;

end



