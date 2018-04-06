LLVM=~/llvm60
MC=${LLVM}/bin/llvm-mc
CPU=gfx900
ARCH=amdgcn
LLD=${LLVM}/bin/ld.lld
HIPCC=/opt/rocm/bin/hipcc

all: for

for:
	${MC} -arch=${ARCH} -mcpu=${CPU} for.s -filetype=obj -o for.o
	${LLD} -shared for.o -o for.co
	${HIPCC} for.cpp -o for

clean:
	rm *.co *.o for
