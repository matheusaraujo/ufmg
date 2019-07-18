close all
T = 20;
x0 = 1;
tols = 1e-12:1e-3:1e-2;

for i = 1:length(tols)
    options = odeset('RelTol', tols(i), 'AbsTol', tols(i));
    
    matrix(i, 1) = tols(i);
    
    % ODE45
    tic
    [t, x45] = ode45(@fx, [0 T], x0, options);
    matrix(i, 2) = toc;
    
        
    % ODE23
    tic
    [t,x23]=ode23(@fx,[0 T],x0,options);
    matrix(i, 3) = toc;
    
    % ODE113
    tic
    [t, x113]=ode113(@fx, [0 T], x0, options);
    matrix(i, 4) = toc;
end

subplot(3,1,1);
plot(matrix(:, 1), matrix(:, 2), 'r');
legend('ode45');
title('Tempo de simulação ode45 vs. tolerância');

subplot(3,1,2);
plot(matrix(:, 1), matrix(:, 3), 'g');
legend('ode23');
title('Tempo de simulação ode23 vs. tolerância');

subplot(3,1,3);
plot(matrix(:, 1), matrix(:, 4), 'b');
legend('ode113');
title('Tempo de simulação ode113 vs. tolerância');

%clear matrix;

function f = fx(t, x)
 f = -x.^3;
end

function x = xsol(t, x0)
 x = 1./sqrt(2*t+1/x0^2);
end