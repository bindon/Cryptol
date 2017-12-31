CLANG=clang
LLVM_LINK=llvm-link
SAW=saw
LSS=lss
CFLAG=-emit-llvm
LLVM_VERIFIER=/home/bindon/cryptol/llvm-verifier/sym-api

OBJS = ARIA_core.o ARIA_wrap.o

all: verify

ARIA_core.o: ARIA_core.c
	@echo "[+] Compile $<"
	@$(CLANG) $(CFLAG) -o $@ -c $<

ARIA_wrap.o: ARIA_wrap.c
	@echo "[+] Compile $<"
	@$(CLANG) $(CFLAG) -I${LLVM_VERIFIER} -o $@ -c $<

ARIA_imp.bc: $(OBJS)
	@echo "[+] Linking $@"
	@$(LLVM_LINK) -o $@ $^

ARIA_imp.aig: ARIA_imp.bc
	@echo "[+] Generate AIG File: $@"
	@time lss $<
	@echo ""

verify: ARIA_imp.aig
	@echo "[*] Formal Verification"
	@saw ARIA.saw

clean:
	@rm -f ARIA_imp.aig ARIA_imp.bc $(OBJS)

