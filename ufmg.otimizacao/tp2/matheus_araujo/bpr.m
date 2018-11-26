function b = bpr(rk1, rk)
    rk1 = rk1(:);
    rk = rk(:);
    b = (rk1'*(rk1-rk))/(rk'*rk);
end