int abs(int number) {
  if (number >= 0) {
    return number;
  }
  else {
    return -number;
  }
}
int gcd(int a, int b) {
  while (b != 0) {
    int t = b;
    b = a % b;
    a = t;
  }
  return abs(a);
}
