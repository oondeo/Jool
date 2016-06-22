# It appears the -C's during the makes below prevent this include from happening
# when it's supposed to.
# For that reason, I can't just do "include ../common.mk". I need the absolute
# path of the file.
# Unfortunately, while the (as always utterly useless) working directory is (as
# always) brain-dead easy to access, the easiest way I found to get to the
# "current" directory is the mouthful below.
# And yet, it still has at least one major problem: if the path contains
# whitespace, `lastword $(MAKEFILE_LIST)` goes apeshit.
# This is the one and only reason why the unit tests need to be run in a
# space-free directory.
include $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))/../common.mk


FILTERING = filtering

obj-m += $(FILTERING).o

$(FILTERING)-objs += $(MIN_REQS)
$(FILTERING)-objs += ../../../common/netlink/config.o
$(FILTERING)-objs += ../../../mod/common/atomic_config.o
$(FILTERING)-objs += ../../../mod/common/config.o
$(FILTERING)-objs += ../../../mod/common/ipv6_hdr_iterator.o
$(FILTERING)-objs += ../../../mod/common/packet.o
$(FILTERING)-objs += ../../../mod/common/pool6.o
$(FILTERING)-objs += ../../../mod/common/rbtree.o
$(FILTERING)-objs += ../../../mod/common/rfc6052.o
$(FILTERING)-objs += ../../../mod/common/xlator.o
$(FILTERING)-objs += ../../../mod/common/nl/nl_common.o
$(FILTERING)-objs += ../../../mod/common/nl/nl_core2.o
$(FILTERING)-objs += ../../../mod/common/rfc6145/4to6.o
$(FILTERING)-objs += ../../../mod/common/rfc6145/6to4.o
$(FILTERING)-objs += ../../../mod/common/rfc6145/common.o
$(FILTERING)-objs += ../../../mod/stateful/fragment_db.o
$(FILTERING)-objs += ../../../mod/stateful/impersonator.o
$(FILTERING)-objs += ../../../mod/stateful/joold.o
$(FILTERING)-objs += ../../../mod/stateful/pool4/db.o
$(FILTERING)-objs += ../../../mod/stateful/bib/table.o
$(FILTERING)-objs += ../../../mod/stateful/bib/db.o
$(FILTERING)-objs += ../../../mod/stateful/bib/port_allocator.o
$(FILTERING)-objs += ../../../mod/stateful/session/entry.o
$(FILTERING)-objs += ../../../mod/stateful/session/table.o
$(FILTERING)-objs += ../../../mod/stateful/session/db.o
$(FILTERING)-objs += ../../../mod/stateful/session/pkt_queue.o
$(FILTERING)-objs += ../framework/skb_generator.o
$(FILTERING)-objs += ../framework/types.o
$(FILTERING)-objs += ../impersonator/icmp_wrapper.o
$(FILTERING)-objs += ../impersonator/nl.o
$(FILTERING)-objs += ../impersonator/pool4_empty.o
$(FILTERING)-objs += ../impersonator/route.o
$(FILTERING)-objs += filtering_and_updating_test.o


all:
	make -C ${KERNEL_DIR} M=$$PWD;
modules:
	make -C ${KERNEL_DIR} M=$$PWD $@;
clean:
	make -C ${KERNEL_DIR} M=$$PWD $@;
	rm -f  *.ko  *.o
test:
	sudo dmesg -C
	-sudo insmod $(FILTERING).ko && sudo rmmod $(FILTERING)
	sudo dmesg -c | less