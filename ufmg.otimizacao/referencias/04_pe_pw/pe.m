% estrategia eps restrito

clear all;
close all;
clc;

% funcao objetivo
%fobj = @fobj1;
%fobj = @fobj2;
fobj = @fobj3;

% numero de variaveis
n = 2; 

% numero de objetivos
m = 2; 

% determina sulocao utopica usando Pw
I = eye(m);
for k = 1:m
    xo = rand(n,1);
    w = I(:,k);
    X(:,k) = random_search(@(x) problema_pw(fobj,x,w), xo, 1000, [0 1 0 1]);
    jX(:,k) = fobj(X(:,k));
end

eps = [min(jX,[],2) max(jX,[],2)];

nef = 1000;
xlim = repmat([0 1], 1, n);
lb = xlim(1:2:end);
ub = xlim(2:2:end);

for i = 1:200
    e = (eps(:,2)- eps(:,1)).*rand(m,1) + eps(:,1);
    xo = (ub(:)-lb(:)).*rand(n,1)+lb(:);
    X(:,i) = random_search(@(x) problema_pe(fobj,x,e), xo, nef, xlim);
    jX(:,i) = fobj(X(:,i));
end

% options = otimset('LargeScale', 'off', 'Display', 'off')
%X(:,i) = fminunc(@(x) problema_pe(fobj,x,e), xo, options)

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
    