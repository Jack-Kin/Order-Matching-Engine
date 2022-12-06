#include "utils.h"


side_type SIDE_DEFAULT = false;
id_type ID_DEFAULT = LLONG_MAX;
price_type PRICE_DEFAULT = -1;
size_type SIZE_DEFAULT = -1;

std::string getFileName(const std::string& path) {
    char sep = '/';

#ifdef _WIN32
    sep = '\\';
#endif

    size_t i = path.rfind(sep, path.length());
    if (i != std::string::npos) {
        std::string name = path.substr(i+1, path.length() - i);
        return(name);
    }

    return("");
}

uint16_t bswap_16(uint16_t value){
    return static_cast<uint16_t>(((value) & 0xff) << 8 | ((value) >> 8));
}

uint32_t bswap_32(uint32_t value){
    return ((static_cast<uint32_t>(bswap_16(static_cast<uint16_t>((value) & 0xffff))) << 16) |
            static_cast<uint32_t>(bswap_16(static_cast<uint16_t>((value) >> 16))));
}

uint64_t bswap_64(uint64_t value){
    return ((static_cast<uint64_t>(bswap_32(static_cast<uint32_t>((value) & 0xffffffff))) << 32) |
            static_cast<uint64_t>(bswap_32(static_cast<uint32_t>((value) >> 32))));
}

uint16_t parse_uint16(char * a){
    return bswap_16(*(reinterpret_cast<uint16_t *>(a)));
}

uint32_t parse_uint32(char * a){
    return bswap_32(*(reinterpret_cast<uint32_t *>(a)));
}

uint64_t parse_uint64(char * a){
    return bswap_64(*(reinterpret_cast<uint64_t *>(a)));
}

uint64_t parse_ts(char * a){
    return (((static_cast<uint64_t>(bswap_16(*(reinterpret_cast<uint16_t *>(a))))) << 32) |
            static_cast<uint64_t>(bswap_32(*(reinterpret_cast<uint32_t *>(a+2)))));
}

long GetNanoSecondInTime(const char *time){
    long h = 0, m = 0, s = 0, ns = 0, time_ns = 0;
    h = 10 * (time[0] - '0') + (time[1] - '0');
    m = 10 * (time[3] - '0') + (time[4] - '0');
    s = 10 * (time[6] - '0') + (time[7] - '0');
    ns = 100000000 * (time[9] - '0') + 10000000 * (time[10] - '0') + 1000000 * (time[11] - '0')
         + 100000 * (time[12] - '0')+ 10000 * (time[13] - '0') +  1000 * (time[14] - '0')
         + 100 * (time[15] - '0') + 10 * (time[16] - '0') +  (time[17] - '0');
    time_ns = (h * 3600 + m * 60 + s) * 1000000000L + ns;
    return time_ns;
}

std::string GetTimeInNanoSecond(long nanosecond){
    char buffer[sizeof"09:30:00.000000000"];
    long hms = nanosecond/1000000000L;
    long ns = nanosecond - 1000000000L * hms;
    long hm = hms/100L;
    long ss = hms - 100L * hm;
    long hh = (hms-ss)/3600L;
    long mm = (hms-ss-hh*3600)/60L;
    sprintf(buffer, "%02ld:%02ld:%02ld.%09ld",
            hh,
            mm,
            ss,
            ns);
    return buffer;
}