# Check the operating system
UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
    # Linux-specific commands
    CC = gcc
    AR = ar
    RCS = rcs
    CFLAGS = -c
    LDFLAGS = -L. -lcjson -static
    OUTPUT = prebuild_linux
else ifeq ($(UNAME), Darwin)
    # macOS-specific commands
    CC = gcc
    AR = ar
    RCS = rcs
    CFLAGS = -c
    LDFLAGS = -L. -lcjson -L/Library/Developer/CommandLineTools/usr/lib/swift_static/macosx/ -Bstatic
    OUTPUT = prebuild_macos
else
    $(error Unsupported operating system: $(UNAME))
endif

# Target rule for Linux and macOS
prebuild_tool:
	$(CC) prebuild_tool.c -o $(OUTPUT)

# Dependency rules

# Clean rule
clean:
	rm -f $(OUTPUT)