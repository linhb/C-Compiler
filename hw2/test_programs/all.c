int i;

int func1(int i, int ***b);

int main( void)
{

  int i;
  int b;
  int c;
  i = 1 + 1 - 1 * 1 / 1 % 1 ^ 1 & 1 && 1 | 1 | i-- - i++ + 1 < 1 << 1 > 1 >> 1; 
  
  /*  i = i != 1 ? i:b; */
  i = ~1;
  i = !1;
  i = 2*3-7+9;

  if(b==c)
    {
      i=10;
    }
  else if(b>c/i)
    {
      b = ~c;
    }
  else
    {
      c=(int)&b;
    }
  do
    {

    }while(1);
  while(1){}
  for(i<10;;)
    {
      continue;
      break;
    }
  goto label1;
 label1:
  c = func1(b, (int***)&c);
  return i;

}

int func1(int i, int ***b)
{
  int a[10];
  int t1, t3;
  int t2; 
  a[(int)b] = 17;
  t1 = t2 = a[(int)b] == t2;  

  return (int)b;

  t1 = t2 + t3;
}
