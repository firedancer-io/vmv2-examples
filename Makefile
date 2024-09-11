PLATFORM_TOOLS:=~/.cache/solana/v1.43/platform-tools
LLVM_DIR:=$(PLATFORM_TOOLS)/llvm

CC:=$(LLVM_DIR)/bin/clang
LD:=$(LLVM_DIR)/bin/ld.lld

CFLAGS:=-Werror -O2 -fno-builtin -std=c17 -target sbf -fPIC
CFLAGS+=-isystem $(LLVM_DIR)/lib/clang/18/include
CFLAGS+=-isystem sdk/include

LDFLAGS:=-z notext -shared --Bdynamic sdk/sbf.ld
LDFLAGS+=--entry entrypoint -L $(LLVM_DIR)/lib -lc
LIBS:=$(PLATFORM_TOOLS)/rust/lib/rustlib/sbf-solana-solana/lib/libcompiler_builtins-*.rlib

.PHONY: all
all:

define _make-bin
$(MKPATH)$(1).o: $(MKPATH)$(1).c
	$(CC) $(CFLAGS) -o $$@ -c $$<

$(MKPATH)$(1).so: $(MKPATH)$(1).o
	$(LD) $(LDFLAGS) -o $$@ $$< $(LIBS)

all: $(MKPATH)$(1).so
endef
make-bin = $(eval $(call _make-bin,$(1)))

$(call make-bin,hash/hash_v1)
$(call make-bin,hash/hash_v2)

.PHONY: clean
clean:
	find . -type f -name '*.o' -delete
	find . -type f -name '*.so' -delete
