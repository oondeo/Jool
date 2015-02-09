#include "nat64/usr/global.h"
#include "nat64/usr/str_utils.h"
#include "nat64/usr/types.h"
#include "nat64/usr/netlink.h"
#include <errno.h>


static int handle_display_response(struct nl_msg *msg, void *arg)
{
	struct global_config *conf = nlmsg_data(nlmsg_hdr(msg));
	__u16 *plateaus;
	int i;

#ifdef STATEFUL
	printf("Address dependent filtering (--%s): %s\n", DROP_BY_ADDR_OPT,
			conf->filtering.drop_by_addr ? "ON" : "OFF");
	printf("Filtering of ICMPv6 info messages (--%s): %s\n", DROP_ICMP6_INFO_OPT,
			conf->filtering.drop_icmp6_info ? "ON" : "OFF");
	printf("Dropping externally initiated TCP connections (--%s): %s\n", DROP_EXTERNAL_TCP_OPT,
			conf->filtering.drop_external_tcp ? "ON" : "OFF");

	printf("UDP session lifetime (--%s): ", UDP_TIMEOUT_OPT);
	print_time_friendly(conf->sessiondb.ttl.udp);
	printf("TCP established session lifetime (--%s): ", TCP_EST_TIMEOUT_OPT);
	print_time_friendly(conf->sessiondb.ttl.tcp_est);
	printf("TCP transitory session lifetime (--%s): ", TCP_TRANS_TIMEOUT_OPT);
	print_time_friendly(conf->sessiondb.ttl.tcp_trans);
	printf("ICMP session lifetime (--%s): ", ICMP_TIMEOUT_OPT);
	print_time_friendly(conf->sessiondb.ttl.icmp);

	printf("Maximum number of stored packets (--%s): %llu\n", STORED_PKTS_OPT,
			conf->pktqueue.max_pkts);
#endif

	printf("Override IPv6 traffic class (--%s): %s\n", RESET_TCLASS_OPT,
			conf->translate.reset_traffic_class ? "ON" : "OFF");
	printf("Override IPv4 type of service (--%s): %s\n", RESET_TOS_OPT,
			conf->translate.reset_tos ? "ON" : "OFF");
	printf("IPv4 type of service (--%s): %u\n", NEW_TOS_OPT,
			conf->translate.new_tos);
	printf("DF flag always on (--%s): %s\n", DF_ALWAYS_ON_OPT,
			conf->translate.df_always_on ? "ON" : "OFF");
	printf("Generate IPv4 identification (--%s): %s\n", BUILD_IPV4_ID_OPT,
			conf->translate.build_ipv4_id ? "ON" : "OFF");
	printf("Decrease MTU failure rate (--%s): %s\n", LOWER_MTU_FAIL_OPT,
			conf->translate.lower_mtu_fail ? "ON" : "OFF");

	printf("MTU plateaus (--%s): ", MTU_PLATEAUS_OPT);
	plateaus = (__u16 *) (conf + 1);
	for (i = 0; i < conf->translate.mtu_plateau_count; i++) {
		if (i + 1 != conf->translate.mtu_plateau_count)
			printf("%u, ", plateaus[i]);
		else
			printf("%u\n", plateaus[i]);
	}

#ifdef STATEFUL
	printf("Fragments arrival time slot (--%s): ", FRAG_TIMEOUT_OPT);
	print_time_friendly(conf->fragmentation.fragment_timeout);
#else
	printf("Compute incoming IPv4 UDP checksum zero (--%s): %s\n", COMPUTE_UDP_CSUM,
			conf->translate.compute_udp_csum_zero ? "ON" : "OFF");
#endif
	printf("Jool Status: %s\n", conf->translate.jool_status ? "Enable" : "Disable");
	printf("Is Jool Disable: %s\n", conf->translate.is_disable ? "True" : "False");

	return 0;
}

int global_display(void)
{
	struct request_hdr request = {
		.length = sizeof(request),
		.mode = MODE_GLOBAL,
		.operation = OP_DISPLAY,
	};
	return netlink_request(&request, request.length, handle_display_response, NULL);
}

static int handle_update_response(struct nl_msg *msg, void *arg)
{
	log_info("Value changed successfully.");
	return 0;
}

int global_update(__u8 type, size_t size, void *data)
{
	struct request_hdr *main_hdr;
	union request_global *global_hdr;
	void *payload;
	size_t len;
	int result;

	len = sizeof(*main_hdr) + sizeof(*global_hdr) + size;
	main_hdr = malloc(len);
	if (!main_hdr)
		return -ENOMEM;
	global_hdr = (union request_global *) (main_hdr + 1);
	payload = global_hdr + 1;

	main_hdr->length = len;
	main_hdr->mode = MODE_GLOBAL;
	main_hdr->operation = OP_UPDATE;
	global_hdr->update.type = type;
	memcpy(payload, data, size);

	result = netlink_request(main_hdr, len, handle_update_response, NULL);
	free(main_hdr);
	return result;
}
