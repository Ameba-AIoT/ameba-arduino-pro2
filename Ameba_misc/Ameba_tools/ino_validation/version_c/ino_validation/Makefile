# Check the operating system
UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
    # Linux-specific commands
    CC = gcc
    AR = ar
    RCS = rcs
    CFLAGS = -c
    LDFLAGS = -L. -lcjson -static
    OUTPUT = ino_validation_linux
else ifeq ($(UNAME), Darwin)
    # macOS-specific commands
    CC = gcc
    AR = ar
    RCS = rcs
    CFLAGS = -c
    ARCH_FLAGS = -arch x86_64 -arch arm64
    LDFLAGS = -L. -lcjson -L/Library/Developer/CommandLineTools/usr/lib/swift_static/macosx/ -Bstatic
    OUTPUT = ino_validation_macos
else
    $(error Unsupported operating system: $(UNAME))
endif

# Target rule for Linux and macOS
ino_validation: cJSON.o libcjson.a
	$(CC) $(ARCH_FLAGS) ino_validation.c -o $(OUTPUT) $(LDFLAGS)

# Dependency rules
cJSON.o: cJSON.c
	$(CC) $(CFLAGS) $(ARCH_FLAGS) cJSON.c

libcjson.a: cJSON.o
	$(AR) $(RCS) libcjson.a cJSON.o

# Clean rule
clean:
	rm -f cJSON.o libcjson.a $(OUTPUT)
