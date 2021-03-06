#include "common/globals.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common/config.h"
#include "usr/util/cJSON.h"
#include "usr/util/str_utils.h"

void print_bool(void *value, bool csv)
{
	bool bvalue = *((bool *)value);
	if (csv)
		printf("%s", bvalue ? "TRUE" : "FALSE");
	else
		printf("%s", bvalue ? "true" : "false");
}

void print_u8(void *value, bool csv)
{
	__u8 *uvalue = value;
	printf("%u", *uvalue);
}

void print_u32(void *value, bool csv)
{
	__u32 *uvalue = value;
	printf("%u", *uvalue);
}

void print_timeout(void *value, bool csv)
{
	__u32 *uvalue = value;
	char string[TIMEOUT_BUFLEN];

	timeout2str(*uvalue, string);
	printf("%s", string);

	if (!csv)
		printf(" (HH:MM:SS)");
}

void print_plateaus(void *value, bool csv)
{
	struct mtu_plateaus *plateaus = value;
	unsigned int i;

	if (csv)
		printf("\"");

	for (i = 0; i < plateaus->count; i++) {
		printf("%u", plateaus->values[i]);
		if (i != plateaus->count - 1)
			printf(",");
	}

	if (csv)
		printf("\"");
}

static void print_prefix(int af, const void *addr, __u8 len, bool set, bool csv)
{
	const char *str;
	char buffer[INET6_ADDRSTRLEN];

	if (!set) {
		printf("%s", csv ? "" : "(unset)");
		return;
	}

	str = inet_ntop(af, addr, buffer, sizeof(buffer));
	if (str)
		printf("%s/%u", str, len);
	else
		perror("inet_ntop");
}

void print_prefix6(void *value, bool csv)
{
	struct config_prefix6 *prefix = value;
	print_prefix(AF_INET6, &prefix->prefix.addr, prefix->prefix.len,
			prefix->set, csv);
}

void print_prefix4(void *value, bool csv)
{
	struct config_prefix4 *prefix = value;
	print_prefix(AF_INET, &prefix->prefix.addr, prefix->prefix.len,
			prefix->set, csv);
}

void print_hairpin_mode(void *value, bool csv)
{
	switch (*((__u8 *)value)) {
	case EHM_OFF:
		printf("off");
		return;
	case EHM_SIMPLE:
		printf("simple");
		return;
	case EHM_INTRINSIC:
		printf("intrinsic");
		return;
	}

	printf("unknown");
}

void print_fargs(void *value, bool csv)
{
	__u8 uvalue = *((__u8 *)value);
	int i;

	printf("%u", uvalue);
	if (csv)
		return;

	printf(" (0b");
	for (i = 3; i >= 0; i--)
		printf("%u", (uvalue >> i) & 0x1);
	printf("): ");

	printf("SrcAddr:%u ", (uvalue >> 3) & 1);
	printf("SrcPort:%u ", (uvalue >> 2) & 1);
	printf("DstAddr:%u ", (uvalue >> 1) & 1);
	printf("DstPort:%u",  (uvalue >> 0) & 1);
}

struct jool_result parse_bool(struct global_field *field, char *str,
		void *result)
{
	return str_to_bool(str, result);
}

struct jool_result parse_u8(struct global_field *field, char *str,
		void *result)
{
	return str_to_u8(str, result, field->min, field->max);
}

struct jool_result parse_u32(struct global_field *field, char *str,
		void *result)
{
	return str_to_u32(str, result, field->min, field->max);
}

struct jool_result parse_timeout(struct global_field *field, char *str,
		void *result)
{
	return str_to_timeout(str, result, field->min, field->max);
}

struct jool_result parse_plateaus(struct global_field *field, char *str,
		void *result)
{
	struct mtu_plateaus *plateaus = result;
	return str_to_plateaus_array(str, plateaus->values, &plateaus->count);
}

struct jool_result parse_prefix6(struct global_field *field, char *str,
		void *result)
{
	struct config_prefix6 *prefix = result;

	if (strcmp(str, "null") == 0) {
		prefix->set = false;
		memset(&prefix->prefix, 0, sizeof(prefix->prefix));
		return result_success();
	}

	prefix->set = true;
	return str_to_prefix6(str, &prefix->prefix);
}

struct jool_result parse_prefix4(struct global_field *field, char *str,
		void *out)
{
	struct config_prefix4 *prefix = out;

	if (strcmp(str, "null") == 0) {
		prefix->set = false;
		memset(&prefix->prefix, 0, sizeof(prefix->prefix));
		return result_success();
	}

	prefix->set = true;
	return str_to_prefix4(str, &prefix->prefix);
}

struct jool_result parse_hairpin_mode(struct global_field *field, char *str,
		void *result)
{
	__u8 *mode = result;

	if (strcmp(str, "off") == 0) {
		*mode = EHM_OFF;
		return result_success();
	} else if (strcmp(str, "simple") == 0) {
		*mode = EHM_SIMPLE;
		return result_success();
	} else if (strcmp(str, "intrinsic") == 0) {
		*mode = EHM_INTRINSIC;
		return result_success();
	}

	return result_from_error(
		-EINVAL,
		"'%s' cannot be parsed as a hairpinning mode.\n"
		"Available options: off, simple, intrinsic", str
	);
}
