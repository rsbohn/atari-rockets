# Makefile
CC := cl65
FUJINET := $(FUJINET_LIB)
ifeq ($(FUJINET),)
FUJINET := ./lib
endif
LIB_VERSION := 3.0.2

rockets.xex: main.o
	 ${CC} -o $@ \
	 -t atari \
	 --lib-path ${FUJINET} \
	 main.o fujinet-atari-${LIB_VERSION}.lib

main.o: main.c
	 ${CC} -c -t atari -I ${FUJINET} -o $@  $<

INSTALL:
	mv rockets.xex /opt/atari/

clean:
	-rm rockets.xex
	-rm main.o

