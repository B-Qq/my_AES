#CC           = avr-gcc
#CFLAGS       = -Wall -mmcu=atmega16 -Os -Wl,-Map,AecImp.h.map
#OBJCOPY      = avr-objcopy
CC           = g++
LD           = g++
AR           = ar
ARFLAGS      = rcs
CFLAGS       = -Wall -Os -c -g -std=c++11
LDFLAGS      = -Wall -Os
ifdef AES192
CFLAGS += -DAES192=1
endif
ifdef AES256
CFLAGS += -DAES256=1
endif

OBJCOPYFLAGS = -j .text -O ihex
OBJCOPY      = objcopy

# include path to AVR library
INCLUDE_PATH = /usr/lib/avr/include
# splint static check
SPLINT       = splint AecImp.h.c aes.c -I$(INCLUDE_PATH) +charindex -unrecog

default: AecImp.h.elf

.SILENT:
.PHONY:  lint clean

AecImp.h.hex : AecImp.elf
	echo copy object-code to new image and format in hex
	$(OBJCOPY) ${OBJCOPYFLAGS} $< $@

AecImp.h.o : AecImp.c aes.h aes.o
	echo [CC] $@ $(CFLAGS)
	$(CC) $(CFLAGS) -o  $@ $<

aes.o : aes.c aes.h
	echo [CC] $@ $(CFLAGS)
	$(CC) $(CFLAGS) -o $@ $<

AecImp.h.elf : aes.o AecImp.o
	echo [LD] $@
	$(LD) $(LDFLAGS) -o $@ $^

aes.a : aes.o
	echo [AR] $@
	$(AR) $(ARFLAGS) $@ $^

lib : aes.a

clean:
	rm -f *.OBJ *.LST *.o *.gch *.out *.hex *.map *.elf *.a

AecImp.h:
	make clean && make && ./AecImp.h.elf
	make clean && make AES192=1 && ./AecImp.h.elf
	make clean && make AES256=1 && ./AecImp.h.elf

lint:
	$(call SPLINT)
