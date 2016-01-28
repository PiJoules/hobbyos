#!/bin/bash
export SKIPBINUTILSCROSS=1
export SKIPGCCCROSS=1
export SKIPDOWNLOAD=1
export SKIPGMP=1
export SKIPMPFR=1
export SKIPMPC=1
export SKIPNEWLIB1=1
export SKIPNEWLIB2=1
export SKIPBINUTILSCROSS2=1
export SKIPGCCCROSS2=1
export SKIPCPPLIB=1
export SKIPHOSTEDBINUTILS=1
export SKIPHOSTEDGCC=1
export SKIPPYTHON=1
. ./variablesetup.sh

mkdir -p $WORKINGDIR
mkdir -p $SOURCELOCATION
mkdir -p $DESTINATION
mkdir -p $SYSROOT

cd $WORKINGDIR
mkdir -p sysroot
mkdir -p sysroot/usr/include

# Print out if an error occured on the last command.
function error_exit {
	if [ "$?" != "0" ]; then
	    echo "Something went wrong! ( $1 )" 1>&2
		exit 1
	fi
}

# Download all sources
echo "downloading..."
if [ "$SKIPDOWNLOAD" == "0" ]; then
	if [ ! -f $DOWNLOADDIR/binutils-$BINUTILSVERSION.tar.gz ]; then
		cd $DOWNLOADDIR
		error_exit "$DOWNLOADDIR not found"
		wget ftp://ftp.gnu.org/gnu/binutils/binutils-$BINUTILSVERSION.tar.gz
		error_exit "downloading binutils"
	fi
	if [ ! -f $DOWNLOADDIR/gcc-$GCCVERSION.tar.gz ];then
		cd $DOWNLOADDIR
		error_exit "$DOWNLOADDIR not found"
		wget ftp://ftp.gnu.org/gnu/gcc/gcc-$GCCVERSION/gcc-$GCCVERSION.tar.gz
		error_exit "downloading gcc"
	fi
	if [ "$SKIPGMP" == "0" ]; then
		if [ ! -f $DOWNLOADDIR/gmp-$GMPVERSION.tar.gz ];then
			cd $DOWNLOADDIR
			error_exit "$DOWNLOADDIR not found"
			wget http://ftp.gnu.org/gnu/gmp/gmp-$GMPVERSION.tar.gz
			error_exit "downloading gmp"
		fi
	fi
	if [ "$SKIPMPFR" == "0" ]; then
		if [ ! -f $DOWNLOADDIR/mpfr-$MPFRVERSION.tar.gz ];then
			cd $DOWNLOADDIR
			error_exit "$DOWNLOADDIR not found"
			wget http://ftp.gnu.org/gnu/mpfr/mpfr-$MPFRVERSION.tar.gz
			error_exit "downloading mpfr"
		fi
	fi
	if [ "$SKIPMPC" == "0" ]; then
		if [ ! -f $DOWNLOADDIR/mpc-$MPCVERSION.tar.gz ];then
			cd $DOWNLOADDIR
			error_exit "$DOWNLOADDIR not found"
			wget http://ftp.gnu.org/gnu/mpc/mpc-$MPCVERSION.tar.gz
			error_exit "downloading mprf"
		fi
	fi
fi
echo "done downloading."

echo "extracting..."
if [ ! -d $SOURCELOCATION/gcc-$GCCVERSION ]; then
	mkdir $SOURCELOCATION
	cd $SOURCELOCATION
	exit_error
	tar -xzvf $DOWNLOADDIR/gcc-$GCCVERSION.tar.gz
	error_exit "unpacking gcc"
fi
if [ ! -d $SOURCELOCATION/binutils-$BINUTILSVERSION ]; then
	mkdir $SOURCELOCATION
	cd $SOURCELOCATION
	exit_error
	tar -xzvf $DOWNLOADDIR/binutils-$BINUTILSVERSION.tar.gz
	error_exit "unpacking binutils"
fi
if [ "$SKIPGMP" == "0" ]; then
	if [ ! -d $SOURCELOCATION/gmp-$GMPVERSION ];then
		mkdir $SOURCELOCATION
		cd $SOURCELOCATION
		exit_error
		tar -xzvf $DOWNLOADDIR/gmp-$GMPVERSION.tar.gz
		error_exit "unpacking gmp"
	fi
fi
if [ "$SKIPMPFR" == "0" ]; then
	if [ ! -d $SOURCELOCATION/mpfr-$MPFRVERSION ];then
		mkdir $SOURCELOCATION
		cd $SOURCELOCATION
		exit_error
		tar -xzvf $DOWNLOADDIR/mpfr-$MPFRVERSION.tar.gz
		error_exit "unpacking mpfr"
	fi
fi
if [ "$SKIPMPC" == "0" ]; then
	if [ ! -d $SOURCELOCATION/mpc-$MPCVERSION ];then
		mkdir $SOURCELOCATION
		cd $SOURCELOCATION
		exit_error
		tar -xzvf $DOWNLOADDIR/mpc-$MPCVERSION.tar.gz
		error_exit "unpacking mpfc"
	fi
fi
echo "done extracting."

echo "building prerequisites"

echo "DONE building prerequisite"
#echo $PATH
echo "moving on to cross-compiler"
echo " "
export PATH="$DESTINATION/gcc-$GCCVERSION/bin:$PATH"
#echo $PATH


## START OF i686-elf

echo "building binutils cross..."
sleep 1

if [ "$SKIPBINUTILSCROSS" == "0" ]; then
	cd $SOURCELOCATION 
	mkdir build-binutils-cross
	cd build-binutils-cross
	../binutils-$BINUTILSVERSION/configure --target=$TARGET --prefix="$DESTINATION/gcc-cross-$GCCVERSION" --with-sysroot --disable-nls --disable-werror
	error_exit "binutils config"
	make
	error_exit "binutils make"
	make install
	error_exit "binutils make install"
fi
echo "done building binutils cross."

export PATH="$DESTINATION/gcc-cross-$GCCVERSION/bin:$PATH"

if [ "$SKIPGCCCROSS" == "0" ]; then
	cd $SOURCELOCATION 
	echo "building gcc cross..."
	sleep 1 
	mkdir build-gcc-cross
	cd build-gcc-cross
	../gcc-$GCCVERSION/configure --target=$TARGET --prefix="$DESTINATION/gcc-cross-$GCCVERSION" --disable-nls --enable-languages=c,c++ --without-headers
	error_exit "config gcc"
	make all-gcc
	error_exit "cross gcc make all-gcc"
	
	make all-target-libgcc
	error_exit "cross gcc make all-target-libgcc"
	
	make install-gcc
	error_exit "cross gcc make install-gcc"
	
	make install-target-libgcc
	error_exit "cross gcc make install-target-libgcc"
	
	echo "done building gcc cross"
fi

## END OF i686-elf
## START OF i686-myos
# Steps:
# - It is assume that you have configured binutils, gcc, and newlib to allow for i686-myos (this should be done alreayd and not automated)
# 1. Build newlib using the bad hack and i686-target
# 2. Build binutils using i686-myos target and --with-sysroot=$SYSROOT
# 3. Same for gcc (build only gcc and libgcc, DO NOT BUILD libstdc++-v3)
# 4. Rebuild newlib but without the hack
# 5. Build libstdc++-v3

# Step 1
echo "building newlib using cross-gcc..."
if [ "$SKIPNEWLIB1" == "0" ]; then
	cp -RT libc/include sysroot/usr/include
	cp -RT kernel/include sysroot/usr/include

	cd $SOURCELOCATION

	# newlib setup
	CURRDIR=$(pwd)
	 
	# make symlinks (a bad hack) to make newlib work
	cd $DESTINATION/gcc-cross-$GCCVERSION/bin/ # this is where the bootstrapped generic cross compiler toolchain (i686-elf-xxx) is installed in,
	                # change this based on your development environment.
	ln i686-elf-ar i686-myos-ar
	ln i686-elf-as i686-myos-as
	ln i686-elf-gcc i686-myos-gcc
	ln i686-elf-gcc i686-myos-cc
	ln i686-elf-ranlib i686-myos-ranlib
	 
	# return
	cd $CURRDIR

	mkdir build-newlib-cross
	cd build-newlib-cross
	../newlib-$NEWLIBVERSION/configure --prefix=/usr --target=i686-myos
	error_exit "newlib configure"
	make all
	error_exit "newlib make all"
	make DESTDIR=$SYSROOT install
	error_exit "newlib make DESTDIR=$SYSROOT install"
	cp -ar $SYSROOT/usr/i686-myos/* $SYSROOT/usr
	error_exit "unable to copy from $SYSROOT/usr/i686-myos/* to $SYSROOT/usr"
fi
echo "done building newlib."

# Step 2
echo "building hosted cross binutils..."
if [ "$SKIPBINUTILSCROSS2" == "0" ]; then
	cd $SOURCELOCATION
	mkdir build-binutils-cross2
	cd build-binutils-cross2
	../binutils-$BINUTILSVERSION/configure --target=i686-myos --prefix="$DESTINATION/gcc-cross-$GCCVERSION" --with-sysroot=$SYSROOT --disable-werror
	error_exit "cross2 binutils config"
	make
	error_exit "cross2 binutils make"
	make install
	error_exit "cross2 binutils make install"
fi
echo "done building hosted cross binutils."

# Step 3
echo "building hosted cross gcc..."
if [ "$SKIPGCCCROSS2" == "0" ]; then
	cd $SOURCELOCATION
	mkdir build-gcc-cross2
	cd build-gcc-cross2
	../gcc-$GCCVERSION/configure --target=i686-myos --prefix="$DESTINATION/gcc-cross-$GCCVERSION" --with-sysroot=$SYSROOT --enable-languages=c,c++
	error_exit "cross2 gcc config"
	make all-gcc all-target-libgcc
	error_exit "cross2 gcc make all-gcc all-target-libgcc"
	make install-gcc install-target-libgcc
	error_exit "cross2 gcc make install-gcc install-target-libgcc"
fi
echo "done building hosted cross gcc."

# Step 4
# Some of the references that ar eincluded in headers are
# not included in libc.a. Figure out how to fix this or
# try another version of newlib.
echo "building newlib using cross-gcc..."
if [ "$SKIPNEWLIB2" == "0" ]; then
	cd $SOURCELOCATION
	mkdir build-newlib-cross
	cd build-newlib-cross
	../newlib-$NEWLIBVERSION/configure --prefix=/usr --target=i686-myos
	error_exit "newlib configure"
	make all
	error_exit "newlib make all"
	make DESTDIR=$SYSROOT install
	error_exit "newlib make DESTDIR=$SYSROOT install"
	cp -ar $SYSROOT/usr/i686-myos/* $SYSROOT/usr/
	error_exit "unable to copy from $SYSROOT/usr/i686-myos/* to $SYSROOT/usr"
fi
echo "done building newlib."

# Step 5
echo "building c++ library..."
if [ "$SKIPCPPLIB" == "0" ]; then
	cd $SOURCELOCATION/build-gcc-cross2
	make all-target-libstdc++-v3
	error_exit "cross2 gcc make all-target-libstdc++-v3"
	make install-target-libstdc++-v3
	error_exit "cross2 gcc make install-target-libstdc++-v3"
fi
echo "done building c++ library."

echo "building python..."
if [ "$SKIPPYTHON" == "0" ]; then
	# This assumes the patches are already apllied
	# and the Python 2.5 source exists
	cd $SOURCELOCATION/Python-2.5
	unset CC CXX AR RANLIB
	make distclean
	./configure && make python Parser/pgen
	error_exit "python ./configure & make python Parser/pgen"
	mv python hostpython
	mv Parser/pgen Parser/hostpgen
	make distclean
	error_exit "python make distclean"
	export CC=i686-myos-gcc
	export CXX=i686-myos-g++
	export AR=i686-myos-ar
	export RANLIB=i686-myos-ranlib
	echo "configuring again..."
	sleep 1
	./configure --build=x86_64-linux-gnu --host=i686-myos --prefix=/usr/python-cross
	error_exit "python ./configure --host=i686-myos --prefix=/usr/python-cross"
	make python Parser/pgen  # I changed A LOT of stuff to get this to work
	error_exit "python again make python Parser/pgen"

	make HOSTPYTHON=./hostpython HOSTPGEN=./Parser/hostpgen BLDSHARED="i686-myos-gcc -shared" CROSS_COMPILE=yes
	error_exit "python make with all the hosts"

fi
echo "done building python."


echo "building hosted binutils..."
if [ "$SKIPHOSTEDBINUTILS" == "0" ]; then
	cd $SOURCELOCATION
	mkdir build-hosted-binutils
	cd build-hosted-binutils

	../binutils-$BINUTILSVERSION/configure --build=x86_64-linux-gnu --host=i686-myos --prefix=/usr --disable-nls --disable-werror
	error_exit "hosted binutils configure"
	make
	error_exit "hosted binutils make"
	make DESTDIR=$SYSROOT install
	error_exit "host binutils make install"
fi
echo "done building hosted binutils."


echo "building hosted gcc..."
if [ "$SKIPHOSTEDGCC" == "0" ]; then
	cd $SOURCELOCATION
	mkdir build-hosted-gcc
	cd build-hosted-gcc
	../gcc-$GCCVERSION/configure --build=x86_64-linux-gnu --target=i686-myos --prefix=/usr --enable-languages=c,c++
	make all-gcc
	error_exit "hosted gcc make all-gcc"
	make all-target-libgcc
	error_exit "hosted gcc make all-target-libgcc"
	make DESTDIR=$SYSROOT install-gcc
	error_exit "hosted gcc make install-gcc"
	make DESTDIR=$SYSROOT install-target-libgcc
	error_exit "hosted gcc make install-target-libgcc"


	cd $SOURCELOCATION/build-hosted-gcc
	make all-target-libstdc++-v3
	error_exit "hosted gcc make all-target-libstdc++-v3"
	make DESTDIR=$SYSROOT install-target-libstdc++-v3
	error_exit "hosted gcc make install-target-libstdc++-v3"

	# May need to copy files from $SYSROOT/usr/local to /usr if not specifying --prefix
fi
echo "done building hosted gcc."
