#pragma once
#define EL_NONE nullptr
#define EL_NONE_ID 0
#define EL_GOL 1
#define EL_SAND 2
#define EL_WATER 3
#define EL_ICE 4
#define EL_FIRE 5

#define ST_GAS 0
#define ST_LIQUID 1
#define ST_POWDER 2
#define ST_SOLID 3

#define C_BLOCK 0
#define C_PASS 1
#define C_SWAP 2

static inline int IDX(int x, int y, int w)
{
	return y * w + x;
}