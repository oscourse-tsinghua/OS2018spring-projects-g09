set -ex

cd ../riscvemu-2017-08-06
make -j4
make install
cd ../hv6
#rm -rf o.riscv64
make -j4
make run
