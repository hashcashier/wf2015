int lo=0, hi= MAX_VAL+1;
while(lo<hi){
  int mid = lo + (hi-lo)/2;
  if(f(mid)) 	hi = mid
  else			lo = mid+1;
}