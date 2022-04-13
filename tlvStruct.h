#pragma once
#include <stdint.h>

// Output file structure:
// <uint8_t> record type
// <uint8_t> record length (= 2 + X, sum of lengths of header and body)
// <X bytes> record body

enum T_TlvTypes {
	TypeText = 1,
	TypeNumeric = 2,
};

struct T_TlvStructHdr {
	uint8_t type;		// T_TlvTypes
	uint8_t length;
	//uint8_t val[...];
};
