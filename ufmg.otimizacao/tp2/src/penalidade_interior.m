% penalidade_interior(@objfun2, [0 0], @objfun2_rg1, @objfun2_rg2, 10, 0.5)
% metodo da penalidade exterior
% entras
% objfun - funcao objetivo
% x0 - ponto inicial
% res_g1 - restricao 1
% res_g2 - restricao 2
% u0 - u inicial
% c - fator de atualizacao
function penalidade_interior (objfun, x0, res_g1, res_g2, u0, c)

    global u
    
    u = u0;

    limites_grafico = [-6 14 -6 14];
    
    k = 0;
    x0 = x0(:);
    
    x = x0;
    
    % funcao de barreira
    bx = @(x) -u * (1/res_g1(x) + 1/res_g2(x));
    % funcao ajustada
    fun_aj = @(x) objfun(x) + bx(x);
    
    % px em x0
    ypx = feval(bx, x);
    fprintf(1, 'p(x) = %+6.4f; \t k = %d\n', ypx, k);

    caminho(k+1,:) = [x0' feval(fun_aj, x0)];
    percurso(objfun, caminho, k, limites_grafico);
    
    curva_critica(res_g1, caminho, limites_grafico);
    curva_critica(res_g2, caminho, limites_grafico);
    
    x_ant = 0;
    
    yx = feval(fun_aj, x);

    while (yx > 0.0001 && ~isequal(x_ant, x))
        
        k = k + 1;
        
        x_ant = x;

        % otimiza fun_aj
        x = quasenewtonmethod(x, fun_aj);
        
        ypx = feval(bx, x);
        
        fprintf(1, 'p(x) = %+6.4f k = %d\n', ypx, k);
        
        % plota resultado
        caminho(k+1,:) = [x' feval(fun_aj, x)];
        percurso(objfun, caminho, k, limites_grafico);
        
        % atualiza u
        u = u * c;
        
    end
    
    fprintf(1, 'x = %f\n', x.');
    fprintf(1, 'f(x) = %g\n', feval(objfun, x));
    fprintf(1, 'u = %f\n', u / c);
    
end