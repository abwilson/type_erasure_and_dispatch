srcs.cpp	:= $(wildcard *.cpp)
srcs.c		:= $(wildcard *.c)
objs		:= $(srcs.cpp:%.cpp=%.o) $(srcs.c:%.c=%.o)
deps		:= $(srcs.cpp:%.cpp=%.d) $(srcs.c:%.c=%.d)
execs		:= $(srcs.cpp:%.cpp=%)   $(srcs.c:%.cpp=%)

opt_flag = -O2

CPPFLAGS = -DCONTIGUOUS_TIDS
CXXFLAGS = -g $(opt_flag) --std=c++14 -MMD -MP -MF $(<:%.cpp=%.d) -MT $@
CXX = clang++

.PHONY: all
all:

benches = \
    bigOrribleSwitchInline \
    cascadingIfs \
    voidStarFPtrs \
    tradPolymorphism \
    indexedBases \
    indexedLambdas \

$(benches): GatherStats.o MsgReader.o

execs = \
    generate_msgs \
    $(benches)

rapidjson = rapidjson/include

all: $(execs) bench_all

$(execs): %: %.o
	$(LINK.cc) $^ -o $@

.PHONY: clean
clean:
	- rm -f $(execs) $(objs) $(deps) $(test_data_files)

.PHONY: force_run
run: $(execs:%=%.run)
%.run: % force_run
	./$<

time: $(execs:%=%.time)
%.time: % force_run
	bash -c "time ./$<"

.PHONY: bench_all
bench_all: $(benches:%=%.bench.csv)

test_data_files = \
    msgs.4.dat \
    msgs.6.dat \
    msgs.10.dat \
    msgs.14.dat \
    msgs.17.dat \
    msgs.20.dat \
    msg.23.dat

test_data = msgs.20.dat
repeats = 100
.PHONY: force_bench
force_bench:
%.bench.csv: % $(test_data) force_bench
	./$< $(test_data) $(repeats) > $@

.PHONY: test_data
test_data: $(test_data_files)

$(test_data_files): generate_msgs

msgs.%.dat: generate_msgs
	./$< $* > $@

-include $(deps)
