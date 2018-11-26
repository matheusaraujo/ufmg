% problema_pw é o nome da função? e fitness?
function fitness = problema_pe(fobj, x, e)

f = feval(fobj, x);
f = f(:);
e = e(:);

fitness = f(1) + 100 * sum( max(0, f(2:end)-e(2:end)).^2);