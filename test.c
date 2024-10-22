#include <stdio.h>
int main() {
  short sa, sb;
  unsigned short usa, usb;
  int a, b;
  unsigned ua, ub;
  long long int lla, llb;
  unsigned long long int ulla, ullb;
  sa = 0x000F;
  sb = 0xFFFB;
  usa = 0x000F;
  usb = 0xFFFB;
  a = sa;
  b = sb;
  ua = usa;
  ub = usb;
  lla = sa;
  llb = (long long)sb;
  ulla = usa;
  ullb = usb;
  printf(" usa %04.04hX  ua %8.8X  ulla %16.16llX  \n", usa, ua, ulla);
  printf(" sa  %04.04hX   a %8.8X   lla %16.16llX   \n\n", sa, a, lla);
  printf(" usb %04.04hX  ub %8.8X  ullb %16.16llX  \n", usb, ub, ullb);
  printf(" sb  %04.04hX   b %8.8X   llb %16.16llX   \n", sb, b, llb);
}
