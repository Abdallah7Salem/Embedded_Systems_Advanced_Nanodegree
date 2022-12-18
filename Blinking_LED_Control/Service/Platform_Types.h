/*
 * Platform_Types.h
 *
 * Created: 10/18/2022 1:17:33 PM
 *  Author: Abdallah
 */ 


#ifndef PLATFORM_TYPES_H_
#define PLATFORM_TYPES_H_


typedef unsigned char        boolean;

typedef signed char          int8_t;
typedef unsigned char        uint8_t;
typedef signed short         int16_t;
typedef unsigned short       uint16_t;
typedef signed int           int32_t;
typedef unsigned int         uint32_t;
typedef signed long long     int64_t;
typedef unsigned long long   uint64_t;

typedef int8_t    sint8;
typedef uint8_t   uint8;
typedef int16_t   sint16;
typedef uint16_t  uint16;
typedef int32_t   sint32;
typedef uint32_t  uint32;
typedef int64_t   sint64;
typedef uint64_t  uint64;

typedef volatile int8_t     vint8_t;
typedef volatile uint8_t    vuint8_t;
typedef volatile int16_t    vint16_t;
typedef volatile uint16_t   vuint16_t;
typedef volatile int32_t    vint32_t;
typedef volatile uint32_t   vuint32_t;
typedef volatile int64_t    vint64_t;
typedef volatile uint64_t   vuint64_t;

typedef float float32;
typedef double float64;

#define NULL_PTR       ((void *)0)
#define INLINE         inline 
#define LOCAL_INLINE   static inline

# define STD_HIGH     1u 
# define STD_LOW      0u 

# define STD_ACTIVE   1u 
# define STD_IDLE     0u 

# define STD_ON       1u
# define STD_OFF      0u

typedef uint8 Std_ReturnType;

typedef enum
{
	E_NOT_OK,
	E_OK,
}Error;






#endif /* PLATFORM_TYPES_H_ */
