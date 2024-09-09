typedef unsigned char uint_8;
typedef signed char   sint_8;
typedef unsigned short uint_16;
typedef signed short sint_16;
typedef unsigned int uint_32;
typedef signed int sint_32;

#define ZERO 0

#define true 1
#define false 0

#define SET_BIT(REG, BIT) ((REG) |= (1 << (BIT)))
#define CLEAR_BIT(REG, BIT) ((REG) &= ~(1 << (BIT)))
#define TOGGLE_BIT(REG, BIT) ((REG) ^= (1 << (BIT)))

#define BIT_IS_SET(REG, BIT) ((REG) & (1 << (BIT)))
#define BIT_IS_CLEAR(REG, BIT) (!((REG) & (1 << (BIT))))