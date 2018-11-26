%funcao objetivo 1
function f = objfun1(x)
    f = x(1)^4 - 2*x(1)^2*x(2) + x(1)^2 + x(1)*x(2)^2 - 2*x(1) + 4;
end