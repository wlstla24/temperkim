#include <stdio.h>

typedef unsigned char byte;
// unsigned char: 0부터 2^8 크기의 숫자(양수만)
// -> for 바이트 단위 데이터 저장
// ** char는 문자 자체를 저장하는 것이 아닌 그 문자의 해당하는 정수 값을 저장



byte GF256_add(byte a, byte b) {
    return a ^ b;
}

void GF256_print_bin(byte x) {
    byte x_bin[8];

    for (int i = 0; i < 8; i++) {
        x_bin[i] = (x >> (7-i)) & 0x01;
    }

    for (int i = 0; i < 8; i++) {
        printf("%d", x_bin[i]);
    }
    printf("\n");
}


void GF256_print_poly(byte a) {
    byte a_bin[8];

    for (int i = 0; i < 8; i++) {
        a_bin[i] = (a >> (7-i)) & 0x01;
    }

    int coef, expo;

    for (int i = 0; i < 7; i++) {
        coef = a_bin[i];
        expo = 7 - i;
        if (coef == 1)
            printf("x^%d + ", expo);
    }

    coef = a_bin[7];
    if (coef == 1) {
        printf("1\n");
    }
    else {
        printf("0\n");
    }
}


int gcd(int a, int b) {
    int r, q;

    while (b!=0){
        r = a % b;
        q = a / b;
        printf("%d = %d*%d + %d\n", a, b, q, r);
        a = b;
        b = r;
    }
    return a;
}


byte GF256_xtime(byte a){
    int msb;
    byte b;
    msb = (a >> 7) & 0x01;

    if (msb == 1) {
        b = (a << 1) ^ 0x1B;
    }
    else {
        b = (a << 1);
    }
    return b;
}

byte GF256_mul(byte a, byte b) {
    byte c, d, e;
    for (int i = 1; i < 8; i++) {
        c = (a >> (8 - i)) & 0x01;

           if (c == 1) {
                   d = d ^ ((8 - i) * GF256_xtime(b));
                }
            }
    e = (a & 0x01) * b;
    d ^= e;
    return d;
}




void test_mul() {
    byte a, b, c;
    a = 0x05;
    b = 0x0A;
    c = GF256_mul(a, b);
    GF256_print_poly(c);
}

void test_xtime() {
    byte a, b;
    a = 0x94;
    b = GF256_xtime(a);
    GF256_print_poly(b);
}

void test_gcd() {
    int a, b, c;
    a = 90, b = 63;
    c = gcd(a, b);
    printf("%d", c);
}

void test_add() {
    byte a, b, c;
    a = 0x1c;
    b = 0x8b;
    c = GF256_add(a, b);
    GF256_print_bin(c);
    GF256_print_poly(c);
}


int main() {
    test_mul();
}