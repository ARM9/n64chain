#ifndef LIBN64_BITFIELD_H
#define LIBN64_BITFIELD_H

/* use ifdefs to fix C/asm incompatibilities with 64 bit ints */
#ifdef __LANGUAGE_ASSEMBLY
/* Mask n lowest bits in x.
 *  x = Value to mask
 *  n = Number of least significant bits set in mask 
 */
#   define _Mask(x,n) ((x)&((1<<(n))-1))
#else
#   define _Mask(x,n) ((x)&((1ULL<<(n))-1))
#endif

/* set "bit field" hb:lb
 *  v = Value to write
 *  hb = High bit of bit field (inclusive)
 *  lb = Low bit of bit field (inclusive)
 */
#define SetField(v,hb,lb) (_Mask((v),(hb)-(lb)+1)<<(lb))

#ifndef __LANGUAGE_ASSEMBLY
// These don't really make sense to use in assembly

/* Overwrite bit field x[hb:lb]
 *  x = The data to overwrite range hb:lb in
 *  v = The new value to set in x[hb:lb]
 *  hb = High bit of bit field (inclusive)
 *  lb = Low bit of bit field (inclusive)
 *  First line clears the field x[hb:lb], then the shifted and masked value v
 *  is ORed in.
 */
#define WriteBits(x,v,hb,lb) \
    ((x) & (~(((1ULL<< ((hb)-(lb)+1) )-1) <<(lb)))) \
    | SetField(v,hb,lb)

/* Read bit field x[hb:lb]
 *  x = Data to read field x[hb:lb] from
 *  hb = High bit of bit field (inclusive)
 *  lb = Low bit of bit field (inclusive)
 */
#define ReadBits(x,hb,lb) (((x)&(((1ULL<< ((hb)-(lb)+1) )-1)<<(lb))) >> (lb))
#endif

#endif
