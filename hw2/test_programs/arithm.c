int arithmTest(int i)
{
    a = !a;
    a = b % c;
    a = a ^ b; 
    a = a & b; 
    a = a * b;
    a = a - b;
    a = a + b;
    a = !a;
    a = a = b;
    a = ~ a;
    a = a | b;
    a = a < b;
    a = a > b;
    a = a / b;
    a = a > b ? c : d;  
    a += b;
    a -= b;
    a *= b;
    a /= b;
    a %= b;
    a <<= b;
    a >>= b;
    a &= b;
    a ^= b;
    a |= b;

    a += 123;
    a -= 123;
    a *= 123;
    a /= 123;
    a %= 123;
    a <<= 12;
    a >>= 12;
    a &= 123;
    a ^= 123;
    a |= 123;

    a++;
    a--;
    a = a << b;
    a = a << 12;
    a = a >> b;
    a = a >> 12;

    a = a <= b ? 1 : 2;
    a = a >= b ? 1 : 2;
    a = a != b ? 1 : 2;
    a = a == b ? 1 : 2;
    a =( a!=b);
    a = ( (a==1) && (b == 2) ) ?  1 : d; 
    a = ( (a==1) || (b == 2) ) ?  1 : d; 
    a = (a + 123*b>>c%3%a+a+b)+d<<(3&8);
}   

