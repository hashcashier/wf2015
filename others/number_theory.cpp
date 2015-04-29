#include <bitset>
#include <cstdio>

using namespace std;

const int __PRIME_SZ = 1000000;
bitset <__PRIME_SZ> is_prime;
void sieve() {
  int M = __PRIME_SZ;
  is_prime.set();
  is_prime[0] = is_prime[1] = 0;
  for (int i = 2; i * i < M; ++i) {
    if (is_prime[i]) {
      for (int j = i * i; j < M; j += i) {
        is_prime[j] = 0;
      }
    }
  }
}

// Accepted, Mobius inverstion precomputation
const int __MOBIUS_SIZE = 1000000;
char mu[__MOBIUS_SIZE + 1];

void mobius() {
  int i, j, M = __MOBIUS_SIZE;
  mu[1] = 1;
  for(i = 1; i < M + 1; i++) {
    for (j = i + i; j < M + 1; j += i)
      mu[j] -= mu[i];
  }
}


// Accepted, Euler Totient function
const int __EULER_SIZE = 1000000;
int phi[__EULER_SIZE + 1];

void euler() {
  int i, j, M = __EULER_SIZE + 1;
  for (i = 0; i < M; i++) {
    phi[i] = i;
  }
  for (i = 2; i < M; i++) {
    if (phi[i] == i) {
      for (j = i; j < M; j += i)
        phi[j] -= phi[j] / i;
    }
  }
  for (i = 2; i < M; i++) {
    if (phi[i] == i) {
      phi[i] -= 1;
    }
  }
}

// Accepted disceret roots
// Check if g is a primitive multiplicative root of p; where p is a prime
// P is the list of the prime factors in the factorization of phi(p)
// req: power function working
bool is_primitive_root(int g, int p) {
  // P = factorize(p - 1); Psz = p.size();
  for (int i = 0; i < Psz; ++i) {
    if (pow(g, (p - 1) / P[i]) == 1) {
      return false;
    }
  }
  return true;
}

// Accepted disceret roots
// extended Euclidean algorithm
// solves d = ax + by , for x, y; given that d = gcd(a, b)
int ext_gcd(int a, int b, int &x, int &y) {
  if (b == 0) {
    x = 1;
    y = 0;
    return a;
  }
  int d = ext_gcd(b, a % b, x, y);
  int temp = x - y * (a / b);
  x = y;
  y = temp;
  return d;
}


// Accepted disceret roots
// Solving linear modular equation ax = b (mod n) 
// Returns a vector of the valid solutions
vector <int> solve(int a, int b, int n) {
  int x, y;
  int d = ext_gcd(a, n, x, y);
  if (b % d) {
    return vector <int> ();
  }
  int x0 = (long long) x * (b / d) % n;
  x0 = (x0 + n) % n;
  int t = n / d;
  vector <int> ans(d);
  x = x0;
  for (int i = 0; i < d; ++i) {
    ans[i] = x;
    x = (x + t) % n;
  }
  return ans;
}


// Accepted disceret roots
// Discrete logarithm such that
// g^x = a (mod p), where p is a prime, g is a primitive root of p
// req: sqrt function
int disc_log(int g, int a, int p) {
  int m = sqrt(p) + 1;
  map <int, int> inv;
  int _a = 1;
  for (int i = 0; i < m; ++i) {
    if (!inv.count(_a))
      inv[_a] = i;
    _a = (long long) _a * g % p;
  }
  int x = a;
  int r = pow(pow(g, m), p - 2);
  for (int i = 0; i < m; ++i) {
    if (inv.count(x)) {
      return i * m + inv[x];
    }
    x = (long long) x * r % p;
  }
}

const int __NUMDIV_SZ = 1000000;
int t[__NUMDIV_SZ + 1];
// Precompute the number of divisors for numbers
void num_of_div() {
  int i, j, M = __NUMDIV_SZ;
  for (i = 1; i < M + 1; ++i) {
    for (j = i; j < M + 1; j += i) {
      t[j]++;
    }
  }
}


const int __NUMSUM_SZ = 1000000;
int d[__NUMSUM_SZ + 1];
// Precompute the sum of divisors for the numbers
void num_of_div() {
  int i, j, M = __NUMSUM_SZ;
  for (i = 1; i < M + 1; ++i) {
    for (j = i; j < M + 1; j += i) {
      d[j] += i;
    }
  }
}


// n Choose k Mod p; for small primes p, Lucas' Theorem
int C(int n, int k) {
  if (k > n) {
    return (long long) C(n % p, k % p) * C(n / p, k / p) % p;
  }
  if (k == n || k == 0) {
    return 1;
  } else {
    return c[n][k];
  }
}


// factorize all number less than n
bool is_prime[MAX + 1];
int pr[80000];
int primes = 0;

int p[MAX + 1][7];
char e[MAX + 1][7];
char _cnt[MAX + 1];

void sieve() {
  is_prime[0] = is_prime[1] = true;

  for (int i = 2; i < MAX + 1; ++i) {
    if (!is_prime[i]) {
      pr[primes++] = i;
      for (int j = i; j < MAX + 1; j += i) {
        if (j != i)
          is_prime[j] = true;
        p[j][_cnt[j]++] = i;
        int k = j / i;
        int q;
        for (q = 0; q < _cnt[j]; ++q) {
          if (i == p[k][q])
            break;
        }
        if (q < _cnt[j])
          e[j][_cnt[j] - 1] = (1 + e[k][q]);
        else
          e[j][_cnt[j] - 1] = (1);
      }
    }
  }
}

// power of a prime p in n!
int f (int n, int p) {
  int r = 0;
  long long div = p;
  while (n >= div) {
    r += n / div;
    div *= p;
  }
  return r;
}


// Both merge functions are accepted. Boring Card Game

bool merge(long long a1, long long a2, long long n1, long long n2, long long &a0, long long &n0) {
    long long p1, p2, d = ext_gcd(n1, n2, p1, p2);
    assert(n1 * p1 + n2 * p2 == d);
    if (not ((a1 - a2) % d == 0))
        return false;
    long long r = a1 % d, q1 = a1 / d, q2 = a2 / d;
    n0 = n1 / d * n2;
    long long e1 = mulmod(q2, mulmod(p1, n1, n0), n0), e2 = mulmod(q1, mulmod(p2, n2, n0), n0);
    a0 = ((e1 + e2 + r) % n0 + n0) % n0;
    return true;
}

 
bool merge(long long &a0, long long a1, long long &n0, long long n1) {
    long long p0, p1, d = ext_gcd(n0, n1, p0, p1);
    assert(n0 * p0 + n1 * p1 == d);
    if (not ((a1 - a0) % d == 0))
        return false;
    long long ns = n0 / d * n1;
    a0 = (a0 + mulmod(mulmod(p0, n0, ns), (a1 - a0) / d, ns)) % ns;
    a0 = (a0 + ns) % ns;
    n0 = ns;
    return true;
}
 
long long chinese_remainder(const vector <int> &a, const vector <int> &n) {
    for (int i = 0; i < a.size(); ++i)
        for (int j = 0; j < i; ++j)
            if (not ((a[i] - a[j]) % __gcd(n[i], n[j]) == 0))
                return -1;
 
    long long as = 0, ns = 1;
    for (int i = 0; i < a.size(); ++i)
        merge(as, a[i], ns, n[i]);
//      merge(a[i], as, n[i], ns, as, ns);
 
    if (as == 0) as += ns;
    for (int i = 0; i < a.size(); ++i)
        assert((as - a[i]) % n[i] == 0);
    return as;
}
