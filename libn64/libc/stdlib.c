#include <stdlib.h>
#include <string.h>
#include <stdint.h>


static int32_t clz32 (int32_t x) {
    int32_t n = 32;
    uint32_t y;

    y = x >>16; if (y != 0) { n = n -16; x = y; }
    y = x >> 8; if (y != 0) { n = n - 8; x = y; }
    y = x >> 4; if (y != 0) { n = n - 4; x = y; }
    y = x >> 2; if (y != 0) { n = n - 2; x = y; }
    y = x >> 1; if (y != 0) return n - 2;
    return n - x;
}

static int64_t clz64 (int64_t x) {
    int64_t n = 64;
    uint64_t y;

    y = x >>32; if (y != 0) { n = n -32; x = y; }
    y = x >>16; if (y != 0) { n = n -16; x = y; }
    y = x >> 8; if (y != 0) { n = n - 8; x = y; }
    y = x >> 4; if (y != 0) { n = n - 4; x = y; }
    y = x >> 2; if (y != 0) { n = n - 2; x = y; }
    y = x >> 1; if (y != 0) return n - 2;
    return n - x;
}

static void reverse (char *b) {
    int32_t i, j;
    char c;
    for (i = 0, j = strlen(b)-1; i < j; i++, j--) {
        c = b[i];
        b[i] = b[j];
        b[j] = c;
    }
}

char * lltoa (int64_t value, char * buf, int base) {
    switch (base) {
        //case 2: {
            //int i = 0,
                //lz = 63-clz64(value);
            //do {
                //int64_t bit = (value >> lz) & 1;
                //lz--;
                //buf[i++] = '0' + bit;
            //} while (lz >= 0);
            //buf[i] = '\0';
            //break;
        //}
        default:
        case 10: {
            int i = 0;
            int64_t sign = value;

            if (value < 0)
                value = -value;

            uint64_t v = value;
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
                lz = clz64(value)&0x3c, nyb = 60-lz;
            do {
                int64_t c = (value >> nyb) & 0xf;
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

char * itoa (int32_t value, char * buf, int base) {
    switch (base) {
        case 2: {
            int i = 0,
                lz = 31-clz32(value);
            do {
                int32_t bit = (value >> lz) & 1;
                lz--;
                buf[i++] = '0' + bit;
            } while (lz >= 0);
            buf[i] = '\0';
            break;
        }
        default:
        case 10: {
            int i = 0;
            int32_t sign = value;

            if (value < 0)
                value = -value;

            uint32_t v = value;
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
                lz = clz32(value)&0x1c, nyb = 28-lz;
            do {
                int32_t c = (value >> nyb) & 0xf;
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

//void ftoa (double n, char *buf, unsigned n_decimals) {
    //if (n_decimals > 10) n_decimals = 10;
    //int64_t int_part = (int64_t)n;
    //double decimal_part = n - (double)int_part;

    //lltoa(int_part, buf, 10);
    //if (n_decimals != 0) {
        //int i = strlen(buf);
        //buf[i++] = '.';

        //decimal_part *= pow(10, decimal_part);
        //itoa((int)decimal_part, buf + i, 10);
    //}
//}

