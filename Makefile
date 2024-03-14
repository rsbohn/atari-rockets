# Makefile
CC := cl65
FUJINET := $(FUJINET_LIB)
ifeq ($(FUJINET),)
FUJINET := ./lib
endif

rockets.xex: main.o
	 ${CC} -o $@ \
	 -t atari \
	 --lib-path ${FUJINET} \
	 main.o fujinet-atari-2.2.1.lib

main.o: main.c
	 ${CC} -c -t atari -I ${FUJINET} -o $@  $<

INSTALL:
	mv rockets.xex /opt/atari/

clean:
	-rm rockets.xex
	-rm main.o

