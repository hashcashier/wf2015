import java.math.BigInteger;
import java.security.SecureRandom;
import java.io.*;
import java.util.*;
    
public class Main {
    final static BigInteger ZERO = new BigInteger("0");
    final static BigInteger ONE  = new BigInteger("1");
    final static BigInteger TWO  = new BigInteger("2");
    final static SecureRandom random = new SecureRandom();
    static HashMap<BigInteger, Integer> map;
    static BigInteger divisor, c, x, xx;
    
    static BigInteger rho(BigInteger N) {
        c  = new BigInteger(N.bitLength(), random);
        x  = new BigInteger(N.bitLength(), random);
        xx = x;
        if (N.mod(TWO).compareTo(ZERO) == 0) return TWO;
        do {
            x  =  x.multiply(x).mod(N).add(c).mod(N);
            xx = xx.multiply(xx).mod(N).add(c).mod(N);
            xx = xx.multiply(xx).mod(N).add(c).mod(N);
            divisor = x.subtract(xx).gcd(N);
        } while((divisor.compareTo(ONE)) == 0);
        return divisor;
    }

    static void factor(BigInteger N) {
        if (N.compareTo(ONE) == 0) return;
        if (N.isProbablePrime(   20   )) {
            Integer t = map.get(N);
            if (t == null) map.put(N, 1);
            else map.put(N, t + 1);
            return;
        }
        BigInteger divisor = rho(N);
        factor(divisor);
        factor(N.divide(divisor));
    }

 
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringBuffer sb = new StringBuffer();
        while (true) {
           BigInteger N = new BigInteger(in.readLine().trim());
           if (N.compareTo(ZERO) == 0) break;
           map = new HashMap<BigInteger, Integer>();
           factor(N);
	       BigInteger[] keys = map.keySet().toArray(new BigInteger[0]);
	       Arrays.sort(keys);
	       sb.append(keys[0] + "^" + map.get(keys[0]));
	       for (int i = 1; i < keys.length; i++)
                sb.append(" " + keys[i] + "^" + map.get(keys[i]));
	       sb.append("\n");
        }
        System.out.print(sb);
    }
}

