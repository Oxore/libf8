Q=@

TARGET_TEST:=test
TARGET_LIB:=libf8.a
MUNIT:=munit

ifeq ($(wildcard $(MUNIT)/*),)
NOTEST=1
endif

INCLUDE+=$(MUNIT)
INCLUDE:=$(INCLUDE:%=-I%)

#COMMON+=-fsanitize=address

CFLAGS+=$(COMMON)
CFLAGS+=$(INCLUDE)
CFLAGS+=-Wall
CFLAGS+=-Wextra
CFLAGS+=-Wpedantic

LDFLAGS+=$(COMMON)

LDFLAGS_TEST+=$(LDFLAGS)

#======================================================================

all:
all: $(TARGET_LIB)
ifndef NOTEST
all: $(TARGET_TEST)
endif

$(TARGET_TEST): $(TARGET_TEST).c.o $(MUNIT)/munit.c.o $(TARGET_LIB)
	@ echo "  LD      $@"
	$(Q) $(CC) -o $@ $^ $(LDFLAGS_TEST)
	./test

$(TARGET_LIB): f8.c.o
	@ echo "  AR      $@"
	$(Q) $(AR) rcs $@ $^

%.c.o: %.c
	@ echo "  CC      $@"
	$(Q) $(CC) -c $(CFLAGS) -o $@ $<

clean:
	$(Q) $(RM) -rfv $(TARGET_TEST) $(TARGET_LIB) f8.c.o test.c.o
	$(Q) $(RM) -rfv $(MUNIT)/*.o

.PHONY: all clean do_test
