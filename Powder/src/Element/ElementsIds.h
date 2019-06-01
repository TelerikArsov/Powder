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
#define EL_BHOL 2
#define EL_BRICK 3
#define EL_CAUS 4
#define EL_COAL 5
#define EL_DUST 6
#define EL_EXC4 7
#define EL_FIRE 8
#define EL_GAS 9
#define EL_GOL 10
#define EL_GOLD 11
#define EL_GUN 12
#define EL_ICE 13
#define EL_LAVA 14
#define EL_METL 15
#define EL_NITR 16
#define EL_OIL 17
#define EL_SAND 18
#define EL_STONE 19
#define EL_WALL 20
#define EL_WATER 21
#define EL_WHOL 22
#define EL_WOOD 23
#define EL_WTRV 24
