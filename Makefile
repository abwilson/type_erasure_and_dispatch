srcs.cpp	:= $(wildcard *.cpp)
srcs.c		:= $(wildcard *.c)
objs		:= $(srcs.cpp:%.cpp=%.o) $(srcs.c:%.c=%.o)
deps		:= $(srcs.cpp:%.cpp=%.d) $(srcs.c:%.c=%.d)
execs		:= $(srcs.cpp:%.cpp=%)   $(srcs.c:%.cpp=%)

valgrind_home = /opt/valgrind-svn
valgrind = $(valgrind_home)/bin/valgrind

benchmark_params = RING_SIZE

l3_macros = L3_ITERATIONS L3_QSIZE $(benchmark_params)

macros = $(foreach m,$(l3_macros),$($m:%=-D$m=$($m)))

opt_flag = -O3

#defines = $(foreach p,$(benchmark_params),$(if $($p),-D$p=$($p)))
# -pthread

CPPFLAGS = -I../include -I $(valgrind_home)/include $(macros)
CXXFLAGS =  -g $(opt_flag) --std=c++14 -MMD -MP -MF $(<:%.cpp=%.d) -MT $@
CXX = clang++

all:

benches = \
    bigOrribleSwitchInline \
    tradPolymorphism \
    indexedBases \
    indexedLambdas

$(benches): GatherStats.o

execs = \
    generate_msgs \
    $(benches)


rapidjson = rapidjson/include

all: $(execs) bench_all

$(execs): %: %.o
	$(LINK.cc) $^ -o $@

clean:
	- rm -f $(execs) $(objs) $(deps) $(test_data_files)

.PHONY: force_run

run: $(execs:%=%.run)
%.run: % force_run
	./$<

time: $(execs:%=%.time)
%.time: % force_run
	bash -c "time ./$<"

%.valgrind: %
	$(valgrind) --tool=callgrind --instr-atstart=no ./$<

-include $(deps)

.PHONY: bench_all
bench_all: $(benches:%=%.bench)

test_data = msgs1M

test_data_files = msgs100 msgs10K msgs1K msgs10 msgs100K msgs10M msgs1M

%.bench: % $(test_data)
	./$< $(test_data)

test_data: $(test_data_files)

$(test_data_files): generate_msgs

msgs100:
	./$< 100 > $@

msgs10K:
	./$< 10000 > $@

msgs1K:
	./$< 1000 > $@

msgs10:
	./$< 10 > $@

msgs100K:
	./$< 100000 > $@

msgs10M:
	./$< 10000000 > $@

msgs1M:
	./$< 1000000 > $@

