clear

hs = 0.1:0.3:1

for i = 1:length(hs)
    t = 0:hs(i):20;
    
    [y, t] = euler(1, t, hs(i));    
    ysol = xsol(t, 1);
    erroSol=abs(y-ysol);
    
    % subplot(2, 2, i)
    % plot(t, y);
    % hold on;
    % plot(t, ysol);
    % legend(strcat('h= ', num2str(hs(i), 2)), 'Solução analítica');
    
    plot(t, erroSol);
    hold on;
end
    legend('h=0.1','h=0.4','h=0.7','h=1');
    ylabel('Erro');


function [x, t] = euler(x0, t, h)
    x = ones(1, length(t));
    x(1) = x0;
  
    for k = 2:length(t)
      k1 = fx(t(k-1), x(k-1));
      k2 = fx(t(k-1) + h/2, x(k-1) + h*k1/2);
      k3 = fx(t(k-1) + h/2, x(k-1) + h*k2/2);
      k4 = fx(t(k-1) + h, x(k-1) + h*k3);
      x(k) = x(k-1) +  h/6*(k1 + 2*k2 + 2*k3 + k4);
    end
end

function f = fx(~, x)
 f = -x.^3;
end

function x = xsol(t, x0)
 x = 1./sqrt(2*t+1/x0^2);
end