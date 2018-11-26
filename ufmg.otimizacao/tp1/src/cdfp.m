function c = cdfp(vk, rk, hk)

    vk = vk(:);
    rk = rk(:);
    
    c1 = (vk*vk')/(vk'*rk);
    c2 = (hk*rk*rk'*hk)/(rk'*hk*rk);
    
    c = c1 - c2;

end

