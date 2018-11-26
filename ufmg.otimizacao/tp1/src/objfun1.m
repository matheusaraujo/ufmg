% funcao objetivo 1
function f = objfun1(x)
    x = x(:);    
    n = length(x);
    vf = 0;
    for i=1:n-1
        vf = vf + 100*power(x(i+1)-power(x(i),2),2)+power(1-x(i),2);
    end
    f = vf;
end