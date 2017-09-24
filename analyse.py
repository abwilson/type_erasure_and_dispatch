import csv
import sys
import numpy

files = sys.argv[1:]

data = {}

for f in files:
    with open(f) as file:
        name = f.split(".")[0]
        d = {
            "times": [],
            "cycles": []
            }
        data[name] = d
        times = d["times"]
        cycles = d["cycles"]

        lines = csv.reader(file)
        next(lines)

        for line in lines:
            # print line
            bench, msgs, t, _1, c, _2, _3 = line
            times.append(float(t))
            cycles.append(float(c))

        msgs = int(msgs)

        def perMsg(v):
            return (v / msgs) * 1000000

        print "%s,%f,%f,%f,%f" % (name, perMsg(numpy.mean(times)), perMsg(numpy.std(times)), numpy.mean(cycles) / msgs, numpy.std(cycles) / msgs)
