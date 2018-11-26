% penalidade_exterior(@objfun1, [2 -4], @objfun1_rh1, @objfun1_rg2, 0.1, 0.1, 5, 5)
% metodo da penalidade exterior
% entras
% objfun - funcao objetivo
% x0 - ponto inicial
% res_h - restricao de igualidade
% res_g - restricao de desigualdade
% rh0 e rg0 - constantes de penalizacao iniciais
% ch e cg - constantes multiplicadores de atualizacao
function penalidade_exterior (objfun, x0, res_h, res_g, rh0, rg0, ch, cg)

    global rh
    global rg

    rh = rh0;
    rg = rg0;

    limites_grafico = [-10 10 -10 10];
    
    k = 0;
    x0 = x0(:);
    
    x = x0;
    
    % funcao de penalidade
    px = @(x) (power(res_h(x),2) * rh) + power(max(0,res_g(x)),2) * rg;
    % funcao ajustada
    fun_aj = @(x) objfun(x) + px(x);
    
    % px em x0
    ypx = feval(px, x);
    fprintf(1, 'p(x) = %+6.4f; \t k = %d\n', ypx, k);

    caminho(k+1,:) = [x0' feval(fun_aj, x0)];
    percurso(objfun, caminho, k, limites_grafico);
    
    curva_critica(res_h, caminho, limites_grafico);
    curva_critica(res_g, caminho, limites_grafico);
    
    x_ant = 0;
    
    while (ypx > 0.00001 && k < 100 && ~isequal(x, x_ant))
        
        k = k + 1;
        
        x_ant = x;

        % otimiza fun_aj
        x = gradmethod(x, fun_aj);
        
        ypx = feval(px, x);
        
        fprintf(1, 'p(x) = %+6.4f k = %d\n', ypx, k);
        
        % plota resultado
        caminho(k+1,:) = [x' feval(fun_aj, x)];
        percurso(objfun, caminho, k, limites_grafico);

        % funcao de penalidade
        px = @(x) (power(res_h(x),2) * rh) + power(max(0,res_g(x)),2) * rg;
        % funcao ajustada
        fun_aj = @(x) objfun(x) + px(x);
        
        % atualiza penalidades
        rh = rh * ch;
        rg = rg * cg;
        
    end
    
    fprintf(1, 'x = %f\n', x.');
    fprintf(1, 'f(x) = %g\n', feval(objfun, x));
    fprintf(1, 'rh = %f\n', rh / ch);
    fprintf(1, 'rg = %f\n', rg / cg);
    
end