.PHONY: clean testall run_test% dist tools

IDIR=include
CC ?= cc
USERFLAGS+=
override CFLAGS+=-I$(IDIR) -g -Wall -Wpedantic $(USERFLAGS) -std=c11 -Wno-format-extra-args
PEDANTIC_CFLAGS=-std=c11 -Werror -Wpedantic -Wall -Wextra -Wformat=2 -O -Wuninitialized -Winit-self -Wswitch-enum -Wdeclaration-after-statement -Wshadow -Wpointer-arith -Wcast-qual -Wcast-align -Wwrite-strings -Wconversion -Waggregate-return -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wredundant-decls -Wnested-externs -Wno-long-long
GOJASM ?= tools/gojasm

ODIR=obj
LDIR =lib
SRCDIR=src
TSTDIR=tests

LIBS=-lm

DEPS = $(wildcard $(IDIR)/*.h)
SRCS = $(wildcard $(SRCDIR)/*.c)
_OBJ = $(patsubst $(SRCDIR)/%,$(ODIR)/%,$(SRCS:.c=.o))
OBJ = $(filter-out $(ODIR)/main.o,$(_OBJ))

DEPS2 := $(OBJ:.o=.d)
-include $(DEPS2)

all: ijvm

$(ODIR)/%.o: $(SRCDIR)/%.c
	+@[ -d $(ODIR) ] || mkdir -p $(ODIR)
	$(CC) -MMD $(CFLAGS) -c -o $@ $<


ijvm: $(OBJ) $(ODIR)/main.o
	echo $(SRCS)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)


clean:
	-rm -f $(ODIR)/*.o *~ core.* $(INCDIR)/*~
	-rm -f $(ODIR)/*.d
	-rm -f ijvm
	-rm -f test1 test2 test3 test4 test5 testadvanced*
	-rm -f dist.tar.gz
	-rm -rf profdata/
	-rm -rf obj/ *.dSYM

tools:
	make -C tools/


files/%.ijvm: files/%.jas
	which $(GOJASM) # Check that GoJasm binary exists
	echo $(GOJASM) -o $@ $<

JAS_FILES = $(wildcard files/task*/*.jas files/advanced/*.jas)
IJVM_FILES = $(JAS_FILES:.jas=.ijvm)
ijvm_binaries: tools $(IJVM_FILES)


dist: clean
	tar -cvzf dist.tar.gz src/*.c src/*.h include/*.h Makefile README.md

test%: $(OBJ) $(TSTDIR)/test%.c
	$(CC) $(CFLAGS) $(LIBS) -o $@ $^

run_test%: test%
	./$<


testbasic: run_test1 run_test2 run_test3 run_test4 run_test5
testadvanced: run_testadvanced1 run_testadvanced2 run_testadvanced3 run_testadvanced4 run_testadvanced5 run_testadvanced6 run_testadvanced7 run_testadvancedstack
testall: testbasic testadvanced
build_tests: test1 test2 test3 test4 test5 testadvanced1 testadvanced2 testadvanced3 testadvanced4 testadvanced5 testadvanced6 testadvanced7 testadvancedstack

# Uses LLVM sanitizers
testasan: CC=clang
testasan: CFLAGS += -fsanitize=undefined,address
testasan: clean testall

testmemsan: CC=clang
testmemsan: CFLAGS += -fsanitize=undefined,memory
testmemsan: clean testall

testsanitizers: testasan testmemsan

pedantic: CFLAGS+=$(PEDANTIC_CFLAGS)
pedantic: clean ijvm


testleaks: build_tests
	valgrind --leak-check=full ./test1
	valgrind --leak-check=full ./test2
	valgrind --leak-check=full ./test3
	valgrind --leak-check=full ./test4
	valgrind --leak-check=full ./test5
	valgrind --leak-check=full ./testadvanced1
	valgrind --leak-check=full ./testadvanced2
	valgrind --leak-check=full ./testadvanced3
	valgrind --leak-check=full ./testadvanced4
	valgrind --leak-check=full ./testadvanced5
	valgrind --leak-check=full ./testadvanced6
	valgrind --leak-check=full ./testadvancedstack

coverage: CFLAGS+=-fprofile-instr-generate -fcoverage-mapping
coverage: CC=clang
coverage: clean ijvm build_tests
	LLVM_PROFILE_FILE="profdata/profile-%p.profraw" make testall
	llvm-profdata merge -sparse profdata/*.profraw -o profdata/testcoverage.profdata
	llvm-cov report ./ijvm -instr-profile=profdata/testcoverage.profdata
