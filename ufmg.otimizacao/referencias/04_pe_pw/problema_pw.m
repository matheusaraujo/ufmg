% problema_pw � o nome da fun��o? e fitness?
function fitness = problema_pw(fobj, x, w)

f = feval(fobj, x);

fitness = w(:)'*f(:);