progname=mini
CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c11 -I.
BUILDS=builds

ifeq ($(MAKECMDGOALS),release)
	BUILD_DIR=$(BUILDS)/release
	CFLAGS+=-g0 -DNDEBUG
else
	BUILD_DIR=$(BUILDS)/debug
	CFLAGS+=-g3
endif

SOURCES:=main.c $(wildcard sources/*.c)
OBJS:=$(patsubst %.c,%.o,$(SOURCES))

debug: $(BUILD_DIR)/$(progname).exe

release: $(BUILD_DIR)/$(progname).exe

$(BUILD_DIR)/$(progname).exe: $(OBJS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(OBJS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	if not exist "$(BUILD_DIR)" mkdir "$(BUILD_DIR)"

clean:
	if exist "$(BUILDS)" rmdir /S /Q "$(BUILDS)"
	if exist "*.o" del /Q *.o
	if exist "sources\*.o" del /Q sources\*.o