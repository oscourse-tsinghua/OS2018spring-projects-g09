set -ex

cd ../riscvemu-2017-08-06
make
make install
cd ../test
rm -rf build
make run
