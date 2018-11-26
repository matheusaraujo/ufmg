% metodo de newton modificado
% entradas
% x - ponto x
% objfun - funcao objetivo
function [vx, y, vncf] = conjgradmethod (x, objfun)

    k = 0; % iteracoes
    ncf = 0; % numero de chamadas da funcao
    ncfmax = 2000; % ncf maximo
    
    x = x(:); % vetor coluna
    
    delta = 1e-3; % perturbacao no calculo do gradiente
    s = 1e-2; % tamanho do passo no cercamento
    e = 1e-3; % tolerancia para sessao aurea
    pre = 0.01; % precisao desejada
    
    [g, ncf1] = gradiente(x, delta, objfun); % gradiente
    %d = -g; % direcao de busca
    ncf = ncf + ncf1;
    
    r = -g;
    d = r;
    
    % parada, ||g|| = 0 ou ncf > 200
    while (norm(g) >= pre && ncf <= ncfmax) 
        
        [alpha, ncf3] = linesearch(x, d, s, e, objfun);
        ncf = ncf + ncf3;
        
        x = x + alpha * d;
        
        [g, ncf1] = gradiente(x, delta, objfun);
        ncf = ncf + ncf1;
        
        r_ant = r;
        r = -g;
        
        %b = bfr(r, r_ant);
        b = bpr(r, r_ant);
        
        d = r + b * r_ant;
        
        k = k + 1;
        
        vx(k,:) = x;
        y(k) = feval(objfun, x);
        vncf(k) = ncf;
        
    end
    
    fprintf(1, 'k = %d\n', k);
    fprintf(1, 'ncf = %d\n', ncf);
    fprintf(1, 'x = %f\n', x.');
    fprintf(1, 'f(x) = %g\n', feval(objfun, x));
    
end