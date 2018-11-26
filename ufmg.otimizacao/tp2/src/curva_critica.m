function curva_critica (fun, vetor, xlimites)

    [L,~] = size(vetor);

    deltax = (xlimites(2) - xlimites(1))/30;
    deltay = (xlimites(4) - xlimites(3))/30;
    [x, y] = meshgrid(xlimites(1):deltax:xlimites(2), ...
                      xlimites(3):deltay:xlimites(4));
    hold on
    z = get_fitness(fun, x, y);
    
    % Plot em 2D
    c = contour(x,y,z,[1,1]); clabel(c), grid on

end