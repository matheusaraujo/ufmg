% funcao linesearch: cercamento + aurea
% entradas:
% x - ponto x
% d - direcao de busca
% s - tamanho do passo inicial
% e - tolerancia
% objfun - funcao objetivo
% saidas:
% alpha - tamanho do passo alpha
% ncf - numero de chamadas de funcao
function [alpha, ncf] = linesearch (x, d, s, e, objfun)
    x = x(:);
    [a, b, fa, fb, ncf1] = cercamento(x, d, s, objfun);
    [alpha, ncf2] = aurea(x, a, b, e, objfun);
    ncf = ncf1 + ncf2;
end