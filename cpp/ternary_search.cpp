long double min() {
    long double lo = -1e6, hi = 1e6, res = 3e6;
    while(fabs(lo-hi) > EPS) {
        long double left = (hi-lo)/3 + lo, right = (2*(hi-lo))/3 + lo;
        long double resL = F(left), resR = F(right);
        if(resL < resR)
            hi = right;
        else
            lo = left;
        res = min(res, min(resL, resR));
    }
    return res;
}