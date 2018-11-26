% funcao de cercamento unidimensional
% entradas:
% x - ponto x
% d - direcao de busca
% s - tamanho do passo inicial
% objfun - funcao objetivo
% saidas:
% a, b - intervalo de cercamento
% fa, fb - valor da funcao objetivo em a e b
% ncf - numero de chamadas da funcao
function [a, b, fa, fb, ncf] = cercamento (x, d, s, objfun)
    
    x = x(:);
    a = 0;
    b = s;
    fa = feval(objfun, x);
    fb = feval(objfun, x+b*d);
    ncf = 2;
    
    while (fb < fa)
        a = b;
        fa = fb;
        b = 2*b;
        fb = feval(objfun, x+b*d);
        ncf = ncf + 1;
    end
    
    if ncf <= 3
        a = 0;
    else
        a = a/2;
    end
    
end