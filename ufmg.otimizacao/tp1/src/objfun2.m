% funcao objetivo 2
function f = objfun2(x)
    x = x(:);
    n = length(x);
    vf = 0;
    for i=1:n
        for j=1:i
            vf = vf + power(x(j)-j,2);
        end
    end
    f = vf;
end

