#include "nat64/mod/stateful/pool4/db.h"
#include "nat64/mod/stateful/bib/pkt_queue.h"
#include "nat64/unit/unit_test.h"

struct fake_pktqueue {
	int junk;
} dummy;

int mask_domain_next(struct mask_domain *masks,
		struct ipv4_transport_addr *addr,
		bool *consecutive)
{
	return broken_unit_call(__func__);
}

struct pktqueue *pktqueue_create(void)
{
	return (struct pktqueue *)&dummy;
}

void pktqueue_destroy(struct pktqueue *queue)
{
	/* No code. */
}

int pktqueue_add(struct pktqueue *queue, struct packet *pkt,
		struct ipv6_transport_addr *dst6)
{
	return broken_unit_call(__func__);
}

struct pktqueue_session *pktqueue_find(struct pktqueue *queue,
		struct ipv6_transport_addr *addr,
		struct mask_domain *masks)
{
	broken_unit_call(__func__);
	return NULL;
}

void pktqueue_put_node(struct pktqueue_session *node)
{
	broken_unit_call(__func__);
}

void pktqueue_prepare_clean(struct pktqueue *queue, struct list_head *probes)
{
	broken_unit_call(__func__);
}

void pktqueue_clean(struct list_head *probes)
{
	broken_unit_call(__func__);
}
