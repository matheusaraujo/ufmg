% funcao de estimativa numerica do grandiente
% entradas:
% x - ponto x
% delta - tamanho da perturbacao
% objfun - funcao objetivo
% saidas:
% g - vetor gradiente
% ncf - numero de chamadas da funcao
function [g, ncf] = gradiente(x, delta, objfun)
    x = x(:);
    n = length(x);
    E = eye(n);
    fx = feval(objfun,x);
    ncf = 1;
    for i=1:n
        g(i) = (feval(objfun,x+delta*E(:,i))-fx)/delta;
        ncf = ncf + 1;
    end
    g = g(:);
end