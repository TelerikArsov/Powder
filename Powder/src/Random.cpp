#include "Random.h"
#include <chrono>

bool Random::has_next_uint32 = false;
uint32_t Random::next_uint32_temp = 0;

static inline uint64_t rotl(const uint64_t x, int k) 
{
	return (x << k) | (x >> (64 - k));
}
// splitmix64 generator (written by Sebastiano Vigna)
// http://xoroshiro.di.unimi.it/splitmix64.c
// used in the seed generation
static uint64_t splitmix64next(uint64_t x) 
{
	uint64_t z = (x += 0x9e3779b97f4a7c15);
	z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
	z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
	return z ^ (z >> 31);
}

static inline double to_double(uint64_t x) 
{
	const union { uint64_t i; double d; } u = { UINT64_C(0x3FF) << 52 | x >> 12 };
	return u.d - 1.0;
}

static uint64_t time_based() 
{
	using namespace std::chrono;
	milliseconds ms = duration_cast< milliseconds >(
		system_clock::now().time_since_epoch()
	);
	uint64_t value = ms.count();
	// Combine and generate the seed.
	uint64_t x = (value << 32) ^ value;
	return x;
}

void Random::seed(uint64_t x) 
{
	has_next_uint32 = false;
	s[0] = splitmix64next(x);
	s[1] = splitmix64next(x);
}

uint32_t Random::next_uint32()
{
	// Generate 2 ints at a time out of one call to next()
	// This makes use of both halves of the 64 bits generated

	uint32_t result;
	if (has_next_uint32) 
	{
		result = next_uint32_temp;
	}
	else 
	{
		uint64_t full = next();
		result = full >> 32;                            // The upper half
		next_uint32_temp = static_cast<uint32_t>(full); // The lower half
	}
	has_next_uint32 = !has_next_uint32;
	return result;
}

unsigned int Random::between(unsigned int lower, unsigned int upper)
{
	unsigned int r = next_uint32();

	return r % (upper - lower + 1) + lower;
}

uint64_t Random::next()
{
	const uint64_t s0 = s[0];
	uint64_t s1 = s[1];
	const uint64_t result = s0 + s1;

	s1 ^= s0;
	s[0] = rotl(s0, 24) ^ s1 ^ (s1 << 16); // a, b
	s[1] = rotl(s1, 37); // c

	return result;
}



double Random::next_double()
{
	return to_double(next());
}

bool Random::next_bool()
{
	return (next() >> 63) & 1;
}

Random::Random()
{
	seed(time_based());
}


Random::~Random()
{
}

Random random;