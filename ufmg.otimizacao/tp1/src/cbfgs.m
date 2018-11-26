function c = cbfgs(vk, rk, hk)

    vk = vk(:);
    rk = rk(:);
    
    c1 = 1 + (rk'*hk*rk)/(rk'*vk);
    c2 = (vk*vk')/(vk'*rk);
    c3 = (vk*rk'*hk+hk*rk*vk')/(rk'*vk);
    
    c = c1*c2-c3;

end