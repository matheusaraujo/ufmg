% funcao de estimativa numerica da hessiana
% entradas:
% x - ponto x
% delta - tamanho da perturbacao
% objfun - funcao objetivo
% saidas:
% h - hessiana
% ncf - numero de chamadas da funcao
function [h, ncf] = hessiana(x, delta, objfun)
    x = x(:);
    n = length(x);
    E = eye(n);
    ncf = 0;
    
    [g0, ncf0] = gradiente(x, delta, objfun);
    ncf = ncf + ncf0;
    
    for i=1:n
        [gi, ncfi] = gradiente(x + delta * E(:,i), delta, objfun);
        ncf = ncf + ncfi;
        h(:,i) = (gi - g0) / delta;
    end
end