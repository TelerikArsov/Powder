#pragma once
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
//ELEMENT_IDS
#define EL_NONE nullptr
#define EL_NONE_ID 0
#define EL_ACID 1
#define EL_BRICK 2
#define EL_CAUS 3
#define EL_COAL 4
#define EL_DUST 5
#define EL_EXC4 6
#define EL_FIRE 7
#define EL_GAS 8
#define EL_GOL 9
#define EL_GOLD 10
#define EL_GUN 11
#define EL_ICE 12
#define EL_LAVA 13
#define EL_NITR 14
#define EL_OIL 15
#define EL_SAND 16
#define EL_STONE 17
#define EL_WATER 18
#define EL_WOOD 19
#define EL_WTRV 20
