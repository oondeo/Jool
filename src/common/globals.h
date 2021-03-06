#ifndef SRC_COMMON_GLOBALS_H_
#define SRC_COMMON_GLOBALS_H_

#ifdef __KERNEL__
#include <linux/types.h>
#else
#include <stddef.h>
#endif
#include "common/config.h"

typedef enum global_type_id {
	GTI_BOOL,
	GTI_NUM8,
	GTI_NUM32,
	GTI_TIMEOUT,
	GTI_PLATEAUS,
	GTI_PREFIX6,
	GTI_PREFIX4,
	GTI_HAIRPIN_MODE,
} global_type_id;

struct global_field;

#ifdef __KERNEL__

/* This function does not need to validate xlator_type nor type->size. */
typedef int (*validate_function)(struct global_field *field, void *value,
		bool force);

int validate_u8(struct global_field *field, void *value, bool force);
int validate_u32(struct global_field *field, void *value, bool force);
int validate_pool6(struct global_field *field, void *value, bool force);
int validate_plateaus(struct global_field *field, void *value, bool force);
int validate_prefix6(struct global_field *field, void *value, bool force);
int validate_prefix4(struct global_field *field, void *value, bool force);
int validate_prefix6791v4(struct global_field *field, void *value, bool force);
int validate_hairpin_mode(struct global_field *field, void *value, bool force);


#else

typedef void (*print_function)(void *value, bool csv);
typedef struct jool_result (*parse_function)(struct global_field *field,
		char *str, void *result);

void print_bool(void *value, bool csv);
void print_u8(void *value, bool csv);
void print_u32(void *value, bool csv);
void print_timeout(void *value, bool csv);
void print_plateaus(void *value, bool csv);
void print_prefix6(void *value, bool csv);
void print_prefix4(void *value, bool csv);
void print_hairpin_mode(void *value, bool csv);
void print_fargs(void *value, bool csv);

struct jool_result parse_bool(struct global_field *, char *, void *);
struct jool_result parse_u8(struct global_field *, char *, void *);
struct jool_result parse_u32(struct global_field *, char *, void *);
struct jool_result parse_timeout(struct global_field *, char *, void *);
struct jool_result parse_plateaus(struct global_field *, char *, void *);
struct jool_result parse_prefix6(struct global_field *, char *, void *);
struct jool_result parse_prefix4(struct global_field *, char *, void *);
struct jool_result parse_hairpin_mode(struct global_field *, char *, void *);

#endif

struct global_type {
	global_type_id id;
	const char *name;
	size_t size;
#ifdef __KERNEL__
	validate_function validate;
#else
	print_function print;
	parse_function parse;
#endif
	char *candidates; /* Same as in struct wargp_type. */
};

struct global_field {
	char *name; /* This being NULL means the end of the array. */
	struct global_type *type;
	const char *doc;
	size_t offset;
	xlator_type xt;
	__u64 min;
	__u64 max;
#ifdef __KERNEL__
	validate_function validate; /* Overrides type->validate. */
#else
	print_function print; /* Overrides type->print. */
#endif
	char *candidates; /* Overrides type->candidates. */
};

void get_global_fields(struct global_field **fields, unsigned int *len);
long int global_field_index(struct global_field *field);

#endif /* SRC_COMMON_GLOBALS_H_ */
