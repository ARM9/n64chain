#include <stdlib.h>
#include <string.h>

static int clz (int x) {
    int n = 32;
    unsigned y;

    y = x >>16; if (y != 0) { n = n -16; x = y; }
    y = x >> 8; if (y != 0) { n = n - 8; x = y; }
    y = x >> 4; if (y != 0) { n = n - 4; x = y; }
    y = x >> 2; if (y != 0) { n = n - 2; x = y; }
    y = x >> 1; if (y != 0) return n - 2;
    return n - x;
}

static void reverse (char *b) {
    int i, j;
    char c;
    for (i = 0, j = strlen(b)-1; i < j; i++, j--) {
        c = b[i];
        b[i] = b[j];
        b[j] = c;
    }
}

char * itoa (int value, char * buf, int base) {
    switch (base) {
        case 2: {
            int i = 0,
                lz = 31-clz(value);
            do {
                int bit = (value >> lz) & 1;
                lz--;
                buf[i++] = '0' + bit;
            } while (lz >= 0);
            /*buf[0] = '\0';*/
            break;
        }
        default:
        case 10: {
            int i = 0, sign = value;

            if (value < 0)
                value = -value;

            unsigned v = value;
            do {
                buf[i++] = '0' + v % 10;
                v /= 10;
            } while (v > 0);

            if (sign < 0)
                buf[i++] = '-';

            buf[i] = '\0';

            reverse(buf);

            break;
        }
        case 16: {
            int i = 0,
                lz = clz(value)&0x1c, nyb = 28-lz;
            do {
                int c = (value >> nyb) & 0xf;
                nyb -= 4;
                if (c > 9)
                    c = 'A' + c-10;
                else
                    c = '0' + c;
                buf[i++] = c;
            } while (nyb >= 0);
            buf[i] = '\0';
        }
            break;
    }
    return buf;
}

