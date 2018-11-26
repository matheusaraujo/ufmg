function b = bfr (rk1, rk)
    rk1 = rk1(:);
    rk = rk(:);
    b = (rk1'*rk1)/(rk'*rk);
end