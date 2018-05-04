#ifndef _JOOL_USR_ARGP_OPTIONS_H
#define _JOOL_USR_ARGP_OPTIONS_H

#include <argp.h>
#include "nat64/common/config.h"

#define BOOL_FORMAT "BOOL"
#define NUM_FORMAT "NUM"
#define NUM_ARRAY_FORMAT "NUM[,NUM]*"
#define TRANSPORT6_FORMAT "ADDR6#NUM"
#define TRANSPORT4_FORMAT "ADDR4#NUM"
#define PREFIX6_FORMAT "ADDR6/NUM"
#define PREFIX4_FORMAT "ADDR4/NUM"
#define OPTIONAL_PREFIX6_FORMAT "(ADDR6/NUM|null)"

/**
 * The flags the user can write as program parameters.
 */
enum argp_flags {
	/* Modes */
	ARGP_POOL6 = '6',
	ARGP_POOL4 = '4',
	ARGP_BIB = 'b',
	ARGP_SESSION = 's',
	ARGP_JOOLD = 7002,
	ARGP_EAMT = 'e',
	ARGP_BLACKLIST = 7000,
	ARGP_RFC6791 = 6791,
	ARGP_GLOBAL = 'g',
	ARGP_PARSE_FILE = 'p',
	ARGP_INSTANCE = 7001,

	/* Operations */
	ARGP_DISPLAY = 'd',
	ARGP_COUNT = 'c',
	ARGP_ADD = 'a',
	ARGP_UPDATE = 5000,
	ARGP_REMOVE = 'r',
	ARGP_FLUSH = 'f',
	ARGP_ADVERTISE = 5002,
	ARGP_TEST = 5001,

	/* Pools */
	ARGP_PREFIX = 3000,
	ARGP_ADDRESS = 3001,
	ARGP_QUICK = 'q',
	ARGP_MARK = 'm',
	ARGP_MAX_ITERATIONS = 3003,
	ARGP_FORCE = 3002,

	/* BIB, session */
	ARGP_TCP = 't',
	ARGP_UDP = 'u',
	ARGP_ICMP = 'i',
	ARGP_NUMERIC_HOSTNAME = 'n',
	ARGP_CSV = 2022,
	ARGP_NO_HEADERS = 2023,
	ARGP_BIB_IPV6 = 2020,
	ARGP_BIB_IPV4 = 2021,

	/* Global */
	ARGP_ENABLE_TRANSLATION = ENABLE,
	ARGP_DISABLE_TRANSLATION = DISABLE,
	ARGP_MANUAL_ENABLE = ENABLE_BOOL,
	ARGP_RESET_TCLASS = RESET_TCLASS,
	ARGP_RESET_TOS = RESET_TOS,
	ARGP_NEW_TOS = NEW_TOS,
	ARGP_PLATEAUS = MTU_PLATEAUS,
	ARGP_COMPUTE_CSUM_ZERO = COMPUTE_UDP_CSUM_ZERO,
	ARGP_RANDOMIZE_RFC6791 = RANDOMIZE_RFC6791,
	ARGP_EAM_HAIRPIN_MODE = EAM_HAIRPINNING_MODE,
	ARGP_DROP_ADDR = DROP_BY_ADDR,
	ARGP_DROP_INFO = DROP_ICMP6_INFO,
	ARGP_DROP_TCP = DROP_EXTERNAL_TCP,
	ARGP_SRC_ICMP6ERRS_BETTER = SRC_ICMP6ERRS_BETTER,
	ARGP_F_ARGS = F_ARGS,
	ARGP_HANDLE_RST_DURING_FIN_RCV = HANDLE_RST_DURING_FIN_RCV,
	ARGP_UDP_TO = UDP_TIMEOUT,
	ARGP_ICMP_TO = ICMP_TIMEOUT,
	ARGP_TCP_TO = TCP_EST_TIMEOUT,
	ARGP_TCP_TRANS_TO = TCP_TRANS_TIMEOUT,
	ARGP_FRAG_TO = FRAGMENT_TIMEOUT,
	ARGP_BIB_LOGGING = BIB_LOGGING,
	ARGP_SESSION_LOGGING = SESSION_LOGGING,
	ARGP_STORED_PKTS = MAX_PKTS,
	ARGP_SS_ENABLED = SS_ENABLED,
	ARGP_SS_FLUSH_ASAP = SS_FLUSH_ASAP,
	ARGP_SS_FLUSH_DEADLINE = SS_FLUSH_DEADLINE,
	ARGP_SS_CAPACITY = SS_CAPACITY,
	ARGP_SS_MAX_PAYLOAD = SS_MAX_PAYLOAD,
	ARGP_RFC6791V6_PREFIX = RFC6791V6_PREFIX,
};

struct argp_option *build_opts(void);
struct argp_option *get_global_opts(void);

#endif /* _JOOL_USR_ARGP_OPTIONS_H */
