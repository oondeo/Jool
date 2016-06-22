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


BIBDB = bibdb

obj-m += $(BIBDB).o

$(BIBDB)-objs += $(MIN_REQS)
$(BIBDB)-objs += ../../../mod/common/config.o
$(BIBDB)-objs += ../../../mod/common/rbtree.o
$(BIBDB)-objs += ../../../mod/stateful/bib/table.o
$(BIBDB)-objs += ../framework/bib.o
$(BIBDB)-objs += bibdb_test.o


all:
	make -C ${KERNEL_DIR} M=$$PWD;
modules:
	make -C ${KERNEL_DIR} M=$$PWD $@;
clean:
	make -C ${KERNEL_DIR} M=$$PWD $@;
	rm -f  *.ko  *.o
test:
	sudo dmesg -C
	-sudo insmod $(BIBDB).ko && sudo rmmod $(BIBDB)
	sudo dmesg -c | less