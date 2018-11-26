% funcao reducao do intervalo usando sessao aurea
% entradas
% x - ponto x
% a, b - intervalo de cercamento
% e - tolerancia
% objfun - funcao objetivo
% saidas
% alpha - tamanho do passo alpha
% ncf - numero de chamadas da funcao
function [alpha, ncf] = aurea (x, a, b, e, objfun)
    x = x(:);
    ra = 0.618;
    xa = b - ra * (b-a);
    xb = a + ra * (b-a);
    
    fa = feval(objfun, x+xa);
    fb = feval(objfun, x+xb);
    
    ncf = 2;
    
    while b - a > e
        if (fa > fb)
            a = xa;
            xa = xb;
            xb = a + ra * (b-a);
            fa = fb;
            fb = feval(objfun, x+xb);
        else
            b = xb;
            xb = xa;
            xa = b - ra * (b-a);
            fb = fa;
            fa = feval(objfun, x+xa);
        end
        ncf = ncf + 1;
    end

    alpha = (a+b)/2;
    
end
