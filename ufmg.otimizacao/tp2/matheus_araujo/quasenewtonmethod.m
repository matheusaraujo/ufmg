% metodo de newton modificado
% entradas
% x - ponto x
% objfun - funcao objetivo
function [x] = quasenewtonmethod (x, objfun)

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
    
    h = eye(length(x));
    
    % eps
    eps = 0.5;
    
    vx(1,:) = x;
    
    % parada, ||g|| = 0 ou ncf > 200
    while (norm(g) >= pre && ncf <= ncfmax) 
        
        d = -h * g;
        
        [alpha, ncf3] = linesearch(x, d, s, e, objfun);
        ncf = ncf + ncf3;
        
        x_ant = x;
        x = x + alpha * d;
        
        g_ant = g;
        [g, ncf1] = gradiente(x, delta, objfun);
        ncf = ncf + ncf1;
        
        v = x - x_ant;
        r = g - g_ant;
        
        c1 = cdfp(v, r, h);
        c2 = cbfgs(v, r, h);
        
        c = (1-eps)*c1+ eps*c2;
        
        h = h + c;
        
        k = k + 1;
        
        vx(k,:) = x;
        y(k) = feval(objfun, x);
        vncf(k) = ncf;
        
    end
    
    %fprintf(1, 'k = %d\n', k);
    %fprintf(1, 'ncf = %d\n', ncf);
    %fprintf(1, 'x = %f\n', x.');
    %fprintf(1, 'f(x) = %g\n', feval(objfun, x));
    
end