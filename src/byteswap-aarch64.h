#ifndef _BITS_BYTESWAP_H
#define _BITS_BYTESWAP_H

/** @file
 *
 * Byte-order swapping functions
 *
 */

#include <stdint.h>

//FILE_LICENCE ( GPL2_OR_LATER_OR_UBDL );

static inline __attribute__ (( always_inline, const )) uint16_t
__bswap_variable_16 ( uint16_t x ) {
	__asm__ ( "rev16 %0, %1" : "=r" ( x ) : "r" ( x ) );
	return x;
}

static inline __attribute__ (( always_inline )) void
__bswap_16s ( uint16_t *x ) {
	*x = __bswap_variable_16 ( *x );
}

static inline __attribute__ (( always_inline, const )) uint32_t
__bswap_variable_32 ( uint32_t x ) {
	__asm__ ( "rev32 %0, %1" : "=r" ( x ) : "r" ( x ) );
	return x;
}

static inline __attribute__ (( always_inline )) void
__bswap_32s ( uint32_t *x ) {
	*x = __bswap_variable_32 ( *x );
}

// TODO
static inline __attribute__ (( always_inline )) uint32_t
__bswap_32 ( uint32_t x ) {
	return __bswap_variable_32(x);
}

static inline __attribute__ (( always_inline, const )) uint64_t
__bswap_variable_64 ( uint64_t x ) {
	__asm__ ( "rev %0, %1" : "=r" ( x ) : "r" ( x ) );
	return x;
}

static inline __attribute__ (( always_inline )) void
__bswap_64s ( uint64_t *x ) {
	*x = __bswap_variable_64 ( *x );
}

// TODO
static inline __attribute__ (( always_inline )) uint64_t
__bswap_64 ( uint64_t x ) {
	return __bswap_variable_64(x);
}

#define __cpu_to_leNN( bits, value ) (value)
#define __cpu_to_beNN( bits, value ) __bswap_ ## bits (value)
#define __leNN_to_cpu( bits, value ) (value)
#define __beNN_to_cpu( bits, value ) __bswap_ ## bits (value)
#define __cpu_to_leNNs( bits, ptr ) do { } while ( 0 )
#define __cpu_to_beNNs( bits, ptr ) __bswap_ ## bits ## s (ptr)
#define __leNN_to_cpus( bits, ptr ) do { } while ( 0 )
#define __beNN_to_cpus( bits, ptr ) __bswap_ ## bits ## s (ptr)

#define cpu_to_le16( value ) __cpu_to_leNN ( 16, value )
#define cpu_to_le32( value ) __cpu_to_leNN ( 32, value )
#define cpu_to_le64( value ) __cpu_to_leNN ( 64, value )
#define cpu_to_be16( value ) __cpu_to_beNN ( 16, value )
#define cpu_to_be32( value ) __cpu_to_beNN ( 32, value )
#define cpu_to_be64( value ) __cpu_to_beNN ( 64, value )
#define le16_to_cpu( value ) __leNN_to_cpu ( 16, value )
#define le32_to_cpu( value ) __leNN_to_cpu ( 32, value )
#define le64_to_cpu( value ) __leNN_to_cpu ( 64, value )
#define be16_to_cpu( value ) __beNN_to_cpu ( 16, value )
#define be32_to_cpu( value ) __beNN_to_cpu ( 32, value )
#define be64_to_cpu( value ) __beNN_to_cpu ( 64, value )
#define cpu_to_le16s( ptr ) __cpu_to_leNNs ( 16, ptr )
#define cpu_to_le32s( ptr ) __cpu_to_leNNs ( 32, ptr )
#define cpu_to_le64s( ptr ) __cpu_to_leNNs ( 64, ptr )
#define cpu_to_be16s( ptr ) __cpu_to_beNNs ( 16, ptr )
#define cpu_to_be32s( ptr ) __cpu_to_beNNs ( 32, ptr )
#define cpu_to_be64s( ptr ) __cpu_to_beNNs ( 64, ptr )
#define le16_to_cpus( ptr ) __leNN_to_cpus ( 16, ptr )
#define le32_to_cpus( ptr ) __leNN_to_cpus ( 32, ptr )
#define le64_to_cpus( ptr ) __leNN_to_cpus ( 64, ptr )
#define be16_to_cpus( ptr ) __beNN_to_cpus ( 16, ptr )
#define be32_to_cpus( ptr ) __beNN_to_cpus ( 32, ptr )
#define be64_to_cpus( ptr ) __beNN_to_cpus ( 64, ptr )

#define htonll( value ) cpu_to_be64 (value)
#define ntohll( value ) be64_to_cpu (value)
#define htonl( value ) cpu_to_be32 (value)
#define ntohl( value ) be32_to_cpu (value)
#define htons( value ) cpu_to_be16 (value)
#define ntohs( value ) be16_to_cpu (value)

#endif
