#ifndef SRC_USR_NL_EAMT_H_
#define SRC_USR_NL_EAMT_H_

#include "common/config.h"
#include "jool_socket.h"

typedef struct jool_result (*eamt_foreach_cb)(struct eamt_entry *entry,
		void *args);

struct jool_result eamt_foreach(struct jool_socket *sk, char *iname,
		eamt_foreach_cb cb, void *args);
struct jool_result eamt_add(struct jool_socket *sk, char *iname,
		struct ipv6_prefix *p6, struct ipv4_prefix *p4, bool force);
struct jool_result eamt_rm(struct jool_socket *sk, char *iname,
		struct ipv6_prefix *p6, struct ipv4_prefix *p4);
struct jool_result eamt_flush(struct jool_socket *sk, char *iname);

struct jool_result eamt_query_v6(struct jool_socket *sk, char *iname,
		struct in6_addr *in, struct in_addr *out);
struct jool_result eamt_query_v4(struct jool_socket *sk, char *iname,
		struct in_addr *in, struct in6_addr *out);

#endif /* SRC_USR_NL_EAMT_H_ */
