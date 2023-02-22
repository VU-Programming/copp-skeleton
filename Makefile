.PHONY: clean testall run_test% dist tools

IDIR=include
CC = clang
USERFLAGS+=
override CFLAGS+=-I$(IDIR) -g -Wall -Wpedantic $(USERFLAGS) -std=c11 -Wformat-extra-args
PEDANTIC_CFLAGS=-std=c11 -Werror -Wpedantic -Wall -Wextra -Wformat=2 -O -Wuninitialized -Winit-self -Wswitch-enum -Wshadow -Wpointer-arith -Wcast-qual -Wcast-align -Wwrite-strings -Wconversion -Waggregate-return -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wredundant-decls -Wnested-externs -Wno-long-long
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

all: ijvm

-include $(DEPS2)

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
	-rm -f test1 test2 test3 test4 test5 testadvanced* testbonusheap
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


UNAME_S := $(shell uname -s)

dist: clean
ifeq ($(UNAME_S), Darwin)
	tar -cvzf dist.tar.gz src/*.c src/*.h include/*.h Makefile README.md
else
	tar --ignore-failed-read -cvzf dist.tar.gz src/*.c src/*.h include/*.h Makefile README.md
endif

tst1: test1binary
tst2: test2stack
tst3: test3flow
tst4: test4lvars
tst5: test5method
tstadv1: testadvanced1wide 
tstadv2: testadvanced2all_instr
tstadv3: testadvanced3tanenbaum
tstadv4: testadvanced4calculator
tstadv5: testadvanced5calc_fac 
tstadv6: testadvanced6mandelbrot
tstadv7: testadvanced7tallstack
run_tst1: run_test1binary
run_tst2: run_test2stack
run_tst3: run_test3flow
run_tst4: run_test4lvars
run_tst5: run_test5method
run_tstadv1: run_testadvanced1wide
run_tstadv2: run_testadvanced2all_instr
run_tstadv3: run_testadvanced3tanenbaum
run_tstadv4: run_testadvanced4calculator
run_tstadv5: run_testadvanced5calc_fac
run_tstadv6: run_testadvanced6mandelbrot
run_tstadv7: run_testadvanced7tallstack


test%: $(OBJ) $(TSTDIR)/test%.c
	$(CC) $(CFLAGS) $(LIBS) -o $@ $^

run_test%: test%
	./$<


testbasic: run_tst1 run_tst2 run_tst3 run_tst4 run_tst5
testadvanced: run_tstadv1 run_tstadv2 run_tstadv3 run_tstadv4 run_tstadv5 run_tstadv6 run_tstadv7
testall: testbasic testadvanced
build_tests: tst1 tst2 tst3 tst4 tst5 tstadv1 tstadv2 tstadv3 tstadv4 tstadv5 tstadv6 tstadv7

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
	valgrind --leak-check=full ./test1binary
	valgrind --leak-check=full ./test2stack
	valgrind --leak-check=full ./test3flow 
	valgrind --leak-check=full ./test4lvars
	valgrind --leak-check=full ./test5method
	valgrind --leak-check=full ./testadvanced1wide
	valgrind --leak-check=full ./testadvanced2all_instr
	valgrind --leak-check=full ./testadvanced3tanenbaum
	valgrind --leak-check=full ./testadvanced4calculator
	valgrind --leak-check=full ./testadvanced5calc_fac
	valgrind --leak-check=full ./testadvanced6mandelbrot
	valgrind --leak-check=full ./testadvanced7tallstack

coverage: CFLAGS+=-fprofile-instr-generate -fcoverage-mapping
coverage: CC=clang
coverage: clean ijvm build_tests
	LLVM_PROFILE_FILE="profdata/profile-%p.profraw" make testall
	llvm-profdata merge -sparse profdata/*.profraw -o profdata/testcoverage.profdata
	llvm-cov report ./ijvm -instr-profile=profdata/testcoverage.profdata
