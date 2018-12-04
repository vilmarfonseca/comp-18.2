make clean
make
./etapa6 Exemplo.txt out.s
gcc -m64 out.s -o assembler.bin