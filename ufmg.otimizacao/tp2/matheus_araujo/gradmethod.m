% metodo do gradiente
% entradas
% x - ponto x
% objfun - funcao objetivo
function x = gradmethod (x, objfun)

    k = 0; % iteracoes
    ncf = 0; % numero de chamadas da funcao
    ncfmax = 2000; % ncf maximo

    x = x(:); % vetor coluna

    delta = 1e-10; % perturbacao no calculo do gradiente
    s = 1e-2; % tamanho do passo no cercamento
    e = 1e-3; % tolerancia para sessao aurea
    pre = 0.01; % precisao desejada
    
    [g, ncf1] = gradiente(x, delta, objfun); % gradiente
    d = -g; % direcao de busca
    ncf = ncf + ncf1;
    
    [alpha, ncf1] = linesearch(x, d, s, e, objfun); % valor de alpha
    ncf = ncf + ncf1;
    
    % parada, ||g|| = 0 ou ncf > 200
    while (norm(g) >= pre && ncf <= ncfmax) 
        
        x = x + alpha*d;
        [g, ncf1] = gradiente(x, delta, objfun);
        d = -g;
        ncf = ncf + ncf1;
        
        [alpha, ncf1] = linesearch(x, d, s, e, objfun);
        ncf = ncf + ncf1;
        
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