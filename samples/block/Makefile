LLVM=~/llvm60
MC=${LLVM}/bin/llvm-mc
CPU=gfx900
ARCH=amdgcn
LLD=${LLVM}/bin/ld.lld

all: c_matrix

c_matrix:
	${MC} -arch=${ARCH} -mcpu=${CPU} c_matrix.s -filetype=obj -o c_matrix.o
	${LLD} -shared c_matrix.o -o c_matrix.co

clean:
	rm *.co *.o