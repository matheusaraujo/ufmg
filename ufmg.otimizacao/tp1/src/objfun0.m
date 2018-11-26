%funcao objetivo 0
function f = objfun0(x)
    f = power((x(1)-2),4) + power(x(1)-2*x(2),2);
end