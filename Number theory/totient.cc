for (int i = 1; i < MN; i++)
  phi[i] = i;

for (int i = 1; i < MN; i++)
  if (!sieve[i]) // is prime
    for (int j = i; j < MN; j += i)
      phi[j] -= phi[j] / i;

long long totient(long long n) {
  if (n == 1) return 0;
  long long ans = n;
  for (int i = 0; primes[i] * primes[i] <= n; ++i) {
    if ((n % primes[i]) == 0) {
      while ((n % primes[i]) == 0) n /= primes[i];
      ans -= ans / primes[i];
    }
  }
  if (n > 1) {
    ans -= ans / n;
  }
  return ans;
}
