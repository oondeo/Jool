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


TRANSLATE = translate

obj-m += $(TRANSLATE).o

$(TRANSLATE)-objs += $(MIN_REQS)
$(TRANSLATE)-objs += ../../../src/mod/common/global-impl.o
$(TRANSLATE)-objs += ../../../src/mod/common/ipv6_hdr_iterator.o
$(TRANSLATE)-objs += ../../../src/mod/common/packet.o
$(TRANSLATE)-objs += ../../../src/mod/common/rfc6052.o
$(TRANSLATE)-objs += ../../../src/mod/common/translation_state.o
$(TRANSLATE)-objs += ../../../src/mod/common/db/config.o
$(TRANSLATE)-objs += ../../../src/mod/common/rfc7915/common.o
$(TRANSLATE)-objs += ../framework/skb_generator.o
$(TRANSLATE)-objs += ../framework/types.o
$(TRANSLATE)-objs += ../impersonator/icmp_wrapper.o
$(TRANSLATE)-objs += ../impersonator/siit.o
$(TRANSLATE)-objs += ../impersonator/stats.o
$(TRANSLATE)-objs += translate_packet_test.o


all:
	make -C ${KERNEL_DIR} M=$$PWD;
modules:
	make -C ${KERNEL_DIR} M=$$PWD $@;
clean:
	make -C ${KERNEL_DIR} M=$$PWD $@;
test:
	sudo dmesg -C
	-sudo insmod $(TRANSLATE).ko && sudo rmmod $(TRANSLATE)
	sudo dmesg -tc | less
