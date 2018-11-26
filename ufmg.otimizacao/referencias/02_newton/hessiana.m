function F = hessiana(fun, x)

n = length(x);

E = eye(n);
d = 1e-3;

for i=1:n
    F(:,i) = (gradiente(fun, x + d * E(:,i)) - gradiente(fun,x) ) / d;
end