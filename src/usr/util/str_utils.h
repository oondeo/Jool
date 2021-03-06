#ifndef SRC_USR_UTIL_STR_UTILS_H_
#define SRC_USR_UTIL_STR_UTILS_H_

/**
 * @file
 * Two-liners (since you need to check the return value) for string-to-something
 * else conversions.
 * This is very noisy on the console on purpose because it is only used by the
 * parser of the userspace app's arguments.
 */

#include "result.h"
#include "common/types.h"

/**
 * Parses @str as a boolean value, which it then copies to @out.
 */
struct jool_result str_to_bool(const char *str, __u8 *out);

struct jool_result validate_int(const char *str);

/**
 * Parses @str" as a number, which it then copies to @out.
 * Refuses to succeed if @out is less than @min or higher than @max.
 */
struct jool_result str_to_u8(const char *str, __u8 *out, __u8 min, __u8 max);
struct jool_result str_to_u16(const char *str, __u16 *out, __u16 min, __u16 max);
struct jool_result str_to_u32(const char *str, __u32 *out, __u32 min, __u32 max);
struct jool_result str_to_u64(const char *str, __u64 *out, __u64 min, __u64 max);

struct jool_result str_to_timeout(const char *str, __u32 *out, __u32 min, __u32 max);
struct jool_result str_to_port_range(char *str, struct port_range *range);

/**
 * Parses @str as a comma-separated array of __u16s, which it then copies to
 * @result.
 *
 * @result is assumed to length PLATEAUS_MAX elements. The actual length is
 * going to be copied to @count.
 */
struct jool_result str_to_plateaus_array(const char *str, __u16 *plateaus, __u16 *count);

/**
 * Converts "str" to a IPv4 address. Stores the result in "result".
 *
 * Useful mainly in code common to kernelspace and userspace, since their
 * conversion functions differ, but meant to be used everywhere to strip the
 * parameters from in4_pton() we don't want.
 */
struct jool_result str_to_addr4(const char *str, struct in_addr *result);
/**
 * Converts "str" to a IPv6 address. Stores the result in "result".
 *
 * Useful mainly in code common to kernelspace and userspace, since their
 * conversion functions differ, but meant to be used everywhere to strip the
 * parameters from in6_pton() we don't want.
 */
struct jool_result str_to_addr6(const char *str, struct in6_addr *result);

/**
 * Parses @str as a '#' separated l3-address and l4-identifier, which it then
 * copies to @out".
 */
struct jool_result str_to_addr4_port(const char *str, struct ipv4_transport_addr *out);
struct jool_result str_to_addr6_port(const char *str, struct ipv6_transport_addr *out);

/**
 * Parses @str as an IP prefix (<prefix address>/<mask>), which it then copies
 * to @out.
 * If str contains no mask, it will default to @out's maximum sensible mask.
 */
struct jool_result str_to_prefix6(const char *str, struct ipv6_prefix *out);
struct jool_result str_to_prefix4(const char *str, struct ipv4_prefix *out);

/**
 * Converts the @millis amount of milliseconds to a string.
 * The format is "HH:MM:SS.mmm".
 * The allocated size of @string must be TIMEOUT_BUFLEN.
 */
void timeout2str(unsigned int millis, char *string);
/*
 * If my math is correct, the hour part of it can span up to 12 digits.
 * ((2^64 - 1) / (60 * 60 * 1000))
 * If it includes milliseconds, the longest possible string is
 * "123456789ABC:12:12.123" plus null chara.
 * Rounded up to the next power of 2 because I'm a wuss.
 */
#define TIMEOUT_BUFLEN 32

#define STR_EQUAL(s1, s2) (strcmp(s1, s2) == 0)

#endif /* SRC_USR_UTIL_STR_UTILS_H_ */
