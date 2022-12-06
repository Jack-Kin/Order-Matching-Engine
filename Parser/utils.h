#ifndef ORDER_MATCHING_ENGINE_UTILS_H
#define ORDER_MATCHING_ENGINE_UTILS_H


#include <iostream>
#include <climits>
//#include <filesystem>

typedef double price_type;
typedef long size_type;
typedef uint64_t id_type;
typedef long long time_type;
typedef bool side_type;

extern id_type ID_DEFAULT;
extern side_type SIDE_DEFAULT;
extern size_type SIZE_DEFAULT;
extern price_type PRICE_DEFAULT;

/**
 * swapping bits from little endian to big endian format.
 */
uint16_t bswap_16(uint16_t value);
uint32_t bswap_32(uint32_t value);
uint64_t bswap_64(uint64_t value);

uint16_t parse_uint16(char * a);
uint32_t parse_uint32(char * a);
uint64_t parse_uint64(char * a);
uint64_t parse_ts(char * a);
std::string getFileName(const std::string& s);


long GetNanoSecondInTime(const char *time);
std::string GetTimeInNanoSecond(long nanosecond);


#endif //ORDER_MATCHING_ENGINE_UTILS_H
