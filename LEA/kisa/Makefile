CLANG=clang
LLVM_LINK=llvm-link
SAW=saw
LSS=lss
CFLAG=-emit-llvm
LLVM_VERIFIER=/home/bindon/cryptol/llvm-verifier/sym-api

OBJS = LEA_core.o LEA_wrap.o

all: verify

LEA_core.o: LEA_core.c
	@echo "[+] Compile $<"
	@$(CLANG) $(CFLAG) -o $@ -c $<

LEA_wrap.o: LEA_wrap.c
	@echo "[+] Compile $<"
	@$(CLANG) $(CFLAG) -I${LLVM_VERIFIER} -o $@ -c $<

LEA_imp.bc: $(OBJS)
	@echo "[+] Linking $@"
	@$(LLVM_LINK) -o $@ $^

LEA_imp.aig: LEA_imp.bc
	@echo "[+] Generate AIG File: $@"
	@time lss $<
	@echo ""

verify: LEA_imp.aig
	@echo "[*] Formal Verification"
	@saw LEA.saw

clean:
	@rm -f LEA_imp.aig LEA_imp.bc $(OBJS)

