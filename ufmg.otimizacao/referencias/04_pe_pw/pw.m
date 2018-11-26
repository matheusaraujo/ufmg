clear all;
close all;
clc;

% funcao objetivo
fobj = @fobj1;
%fobj = @fobj2;
%fobj = @fobj3;

% numero de variaveis
n = 2; 

% numero de objetivos
m = 2; 

% criterio de parada
nef = 1000;

% limites - interval, de 1 a n
xlim = repmat([0 1], 1, n);

% ???
lb = xlim(1:2:end);
ub = xlim(2:2:end);

for i = 1:100
    
    % vetor aleatorio com somatorio = 1
    w = rand(m,1);
    w = w/sum(w);
    
    % ponto inicial, vetor aleatorio
    xo = (ub(:) - lb(:)).*rand(n,1) + lb(:);
    
    X(:,i) = random_search(@(x) problema_pw(fobj,x,w), xo, nef, xlim);
    %X(:,i) = newton(@(x) problema_pw(fobj,x,w), xo, nef, xlim);
    
    jX(:,i) = fobj(X(:,i));
    
end

if m == 2
    plot(jX(1,:),jX(2,:),'ro');
    xlabel('f1'), ylabel('f2');
elseif m == 3
    plot3(jX(1,:), jX(2,:), jX(3,:),'ro');
    xlabel('f1'), ylabel('f2'), zlabel('f3');
    box on
end

if n == 2
    figure
    plot(X(1,:),X(2,:),'ro');
    xlabel('x1'), ylabel('x2');
elseif n == 3
    figure
    plot3(X(1,:), X(2,:), X(3,:),'ro');
    xlabel('x1'), ylabel('x2'), zlabel('x3');
    box on
end
    