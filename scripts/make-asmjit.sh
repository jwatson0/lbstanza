CURRENTDIR=$PWD
mkdir -p build/asmjit
cmake -S libs/asmjit -B build/asmjit
cd build/asmjit
make
cd $CURRENTDIR
mv build/asmjit/libasmjit.a bin/libasmjit.a
rm -r build/asmjit
