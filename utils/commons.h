#pragma once

#ifndef __COMMONS
#define __COMMONS

#include <stdint.h>
#include <stddef.h>



#if _WIN32 || _WIN64
	#define ENV_WIN

	#if _WIN64
		#define ENV_64BIT
	#else
		#define ENV_32BIT
	#endif
#endif

#if __GNUC__
	#define ENV_GCC

	#if __x86_64__ || __ppc64__
		#define ENV_64BIT
	#else
		#define ENV_32BIT
	#endif
#endif



#if defined(ENV_WIN)

	#define ENV_FORMAT_INT64_DEC			"%lld"
	#define ENV_FORMAT_UINT64_DEC			"%llu"
	#define ENV_FORMAT_UINT64_HEX			"%llx"

	#define ENV_FORMAT_SIZE_DEC				"%llu"
	#define ENV_FORMAT_SIZE_HEX				"%llx"

	#ifdef ENV_64BIT

		#define ENV_PTR_INT					uint64
		#define ENV_PTR_INT_T				uint64_t

	#else

		#define ENV_PTR_INT					uint32
		#define ENV_PTR_INT_T				uint32_t

	#endif

#elif defined(ENV_GCC)

	#ifdef ENV_64BIT

		#define ENV_FORMAT_INT64_DEC		"%ld"
		#define ENV_FORMAT_UINT64_DEC		"%lu"
		#define ENV_FORMAT_UINT64_HEX		"%lx"

		#define ENV_FORMAT_SIZE_DEC			"%lu"
		#define ENV_FORMAT_SIZE_HEX			"%lx"

		#define ENV_PTR_INT					uint64
		#define ENV_PTR_INT_T				uint64_t

	#else

		#define ENV_FORMAT_INT64_DEC		"%lld"
		#define ENV_FORMAT_UINT64_DEC		"%llu"
		#define ENV_FORMAT_UINT64_HEX		"%llx"

		#define ENV_FORMAT_SIZE_DEC			"%u"
		#define ENV_FORMAT_SIZE_HEX			"%x"

		#define ENV_PTR_INT					uint32
		#define ENV_PTR_INT_T				uint32_t

	#endif

#endif



#define RANGED(X, S, E)						((X) >= (S) && (X) <= (E))
#define NOT_RANGED(X, S, E)					((X) < (S) || (X) > (E))

#define RANGED_NE(X, S, E)					((X) >= (S) && (X) < (E))
#define RANGED_NS(X, S, E)					((X) > (S) && (X) <= (E))

#define NEW_DATA(T, V)						((data_t) {.T = V})
#define DATA_NULL							NEW_DATA(uint64, 0)

#define TO_PTR(I)							((void*) ((ENV_PTR_INT_T) (I)))
#define FROM_PTR(P)							((ENV_PTR_INT_T) (P))



typedef union {
	uint8_t uint8;
	int8_t int8;
	uint16_t uint16;
	int16_t int16;
	uint32_t uint32;
	int32_t int32;
	uint64_t uint64;
	int64_t int64;

	float float32;
	double float64;

	void *ptr;
} data_t;

typedef struct {
	int flags_n;

	data_t *flags;
	uint8_t *flags_type;
	data_t *flags_iival; //implicit invocation (when you put the flag without specifying any value)

	char *flags_name;
	char **flags_fullname;
} flags_info_t;



int commons_get_flags(flags_info_t flags_info, int argc, char **argv);
void commons_print_flags(flags_info_t flags_info);



#endif