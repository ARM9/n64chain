//
// libn64/include/math.h: libc math
//
// N64Tool: A (free) open-source N64 development toolchain.
// Copyright 2014 Tyler J. Stachecki <tstache1@binghamton.edu>
//
// This file is subject to the terms and conditions defined in
// 'LICENSE', which is part of this source code package.
//

#ifndef LIBN64_MATH_H
#define LIBN64_MATH_H

#define M_PI    3.14159265358979323846
#define M_PI_2  1.57079632679489661923
#define M_PI_4  0.78539816339744830962

#ifdef __cplusplus
extern "C" {
#endif

float sinf(float x);

static inline float cosf(float x) {
    return sinf(x + M_PI_2);
}

static inline float fabsf(float f) {
	float res;
	__asm__ __volatile__(
		"abs.s %0, %1\n\t"

		: "=f"(res)
		: "f"(f)
	);
	return res;
}

static inline double fabs(double d) {
	double res;
	__asm__ __volatile__(
		"abs.d %0, %1\n\t"

		: "=f"(res)
		: "f"(d)
	);
	return res;
}

static inline double sqrt(double d) {
	double res;
	__asm__ __volatile__(
		"sqrt.d %0, %1\n\t"

		: "=f"(res)
		: "f"(d)
	);
	return res;
}

static inline float sqrtf(float f) {
	float res;
	__asm__ __volatile__(
		"sqrt.s %0, %1\n\t"

		: "=f"(res)
		: "f"(f)
	);
	return res;
}

static inline double floor(double f) {
	double res;
	__asm__ __volatile__(
		"floor.l.d %0, %1\n\t"
                "cvt.d.l %0, %0\n\t"
		: "=f"(res)
		: "f"(f)
	);
	return res;
}

static inline float floorf(float f) {
	float res;
	__asm__ __volatile__(
		"floor.w.s %0, %1\n\t"
                "cvt.s.w %0, %0\n\t"
		: "=f"(res)
		: "f"(f)
	);
	return res;
}

static inline double ceil(double f) {
	double res;
	__asm__ __volatile__(
		"ceil.l.d %0, %1\n\t"
                "cvt.d.l %0, %0\n\t"
		: "=f"(res)
		: "f"(f)
	);
	return res;
}

static inline float ceilf(float f) {
	float res;
	__asm__ __volatile__(
		"ceil.w.s %0, %1\n\t"
                "cvt.s.w %0, %0\n\t"
		: "=f"(res)
		: "f"(f)
	);
	return res;
}

static inline double round(double f) {
	double res;
	__asm__ __volatile__(
		"round.l.d %0, %1\n\t"
                "cvt.d.l %0, %0\n\t"
		: "=f"(res)
		: "f"(f)
	);
	return res;
}

static inline float roundf(float f) {
	float res;
	__asm__ __volatile__(
		"round.w.s %0, %1\n\t"
                "cvt.s.w %0, %0\n\t"
		: "=f"(res)
		: "f"(f)
	);
	return res;
}

#ifdef __cplusplus
}
#endif

#endif
