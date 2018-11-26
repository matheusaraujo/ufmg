% problema_pw é o nome da função? e fitness?
function fitness = problema_pw(fobj, x, w)

f = feval(fobj, x);

fitness = w(:)'*f(:);