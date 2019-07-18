close all
T = 20;
x0 = 1;
tol = 1e-6;
options = odeset('RelTol', tol, 'AbsTol', tol);

% ODE45

tic
[t, x45] = ode45(@fx, [0 T], x0, options);
toc

erro45 = max(abs(x45 - xsol(t, x0)));

plot(t, x45, 'r');
hold on;
clear t x45;

% ODE23

tic
[t,x23]=ode23(@fx,[0 T],x0,options);
toc

erro23 = max(abs(x23 - xsol(t, x0)));

plot(t,x23,'k');
hold on;
clear t x23;

% ODE23

tic
[t, x113]=ode113(@fx, [0 T], x0, options);
toc

erro113 = max(abs(x113 - xsol(t, x0)))

plot(t,x113,'m');
clear x113;

function f = fx(t, x)
 f = -x.^3;
end

function x = xsol(t, x0)
 x = 1./sqrt(2*t+1/x0^2);
end