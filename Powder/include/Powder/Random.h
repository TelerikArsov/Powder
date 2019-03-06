#pragma once
#include <stdint.h>
// xoroshiro128+ by David Blackman and Sebastiano Vigna
// http://vigna.di.unimi.it/xorshift/xoroshiro128plus.c
class Random
{
public:
	void seed(uint64_t x);
	uint32_t next_uint32();
	unsigned int between(unsigned int lower, unsigned int upper);
	float next_float();
	bool next_bool();
	Random();
	~Random();
private:
	// seed
	uint64_t s[2];
	uint64_t next();
	static uint32_t next_uint32_temp;
	static bool has_next_uint32;
};
extern Random random;

