from subprocess import Popen, PIPE
from sys import argv
from datetime import datetime

prog_name   = argv[1]
compileLineOMP = "gcc " + prog_name + ".c" + " -lm -fopenmp -o" + prog_name

# Compile parallel program
p = Popen(compileLineOMP.split(), stdout=PIPE)
out, err = p.communicate()
p.wait()

# Run parallel program
rstart = datetime.now()
p = Popen("./"+prog_name, stdout=PIPE)
p.wait()
rend = datetime.now()
out, err = p.communicate()
print("out: ", out.decode())
print("time: ", rend - rstart)


# read file of parallel program
parfilelns = open(prog_name+".c", "r").readlines()
seqfile = open(prog_name+"_seq"+".c", 'w')

for ln in parfilelns:
    if "#pragma" in ln:
        pass
    else:
        seqfile.write(''.join(ln))

seqfile.close()

compileLineSeq = "gcc " + prog_name + "_seq" + ".c" + " -lm -fopenmp -o" + prog_name +"_seq"

# Compile seq program
p = Popen(compileLineSeq.split(), stdout=PIPE)
out, err = p.communicate()
p.wait()
 
# Run seq program
rstart = datetime.now()
p = Popen("./"+prog_name+"_seq", stdout=PIPE)
p.wait() 
rend = datetime.now()
out, err = p.communicate()
print("out: ", out.decode())
print("time: ", rend - rstart)



