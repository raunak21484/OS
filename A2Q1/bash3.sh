rm -r -f KernelBuild
mkdir KernelBuild
cp linux-5.19.9.tar.xz KernelBuild/linux-5.19.9.tar.xz
cd KernelBuild
tar -xvf linux-5.19.9.tar.xz
cd linux-5.19.9
make mrproper
cp ../configFile ./.config
make -j$(nproc)