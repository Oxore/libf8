Q=@

TARGET_TEST:=test
TARGET_LIB:=libf8.a
MUNIT:=munit

ifeq ($(wildcard $(MUNIT)/*),)
NOTEST=1
endif

SOURCES_TEST=$(wildcard tests/*.c)
OBJECTS_TEST=$(SOURCES_TEST:.c=.c.o)

INCLUDE+=$(MUNIT)
INCLUDE+=.
INCLUDE:=$(INCLUDE:%=-I%)

#COMMON+=-fsanitize=address

CFLAGS+=$(COMMON)
CFLAGS+=$(INCLUDE)
CFLAGS+=-Wall
CFLAGS+=-Wextra
CFLAGS+=-Wpedantic

LDFLAGS+=$(COMMON)

LDFLAGS_TEST+=$(LDFLAGS)
LDFLAGS_TEST+=-l:$(TARGET_LIB) -L.

#======================================================================

all:
all: $(TARGET_LIB)
ifndef NOTEST
all: do_test
all: $(TARGET_TEST)
endif

do_test: $(TARGET_TEST)
	./$<

$(TARGET_TEST): $(TARGET_LIB)
$(TARGET_TEST): $(TARGET_TEST).c.o $(MUNIT)/munit.c.o $(OBJECTS_TEST)
	@ echo "  LD      $@"
	$(Q) $(CC) -o $@ $^ $(LDFLAGS_TEST)

$(TARGET_LIB): f8.c.o
	@ echo "  AR      $@"
	$(Q) $(AR) rcs $@ $^

%.c.o: %.c
	@ echo "  CC      $@"
	$(Q) $(CC) -c $(CFLAGS) -o $@ $<

clean:
	$(Q) $(RM) -rfv $(TARGET_TEST) $(TARGET_LIB) f8.c.o test.c.o
	$(Q) $(RM) -rfv $(OBJECTS_TEST)
	$(Q) $(RM) -rfv $(MUNIT)/*.o

.PHONY: all clean do_test
