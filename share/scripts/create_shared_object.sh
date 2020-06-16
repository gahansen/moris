#!/bin/sh
#
echo ""
echo "=============================================================="
echo ""
echo " Script to build shared object for input files"
echo ""
echo " Input: 1. name of working directory of source file and share object"
echo "        2. name of moris build directory under "'$MORISROOT'
echo "        3. name of input file (without cpp suffix)"
echo "        4. optional: keyword dbg to keep link to input file"
echo ""
echo " Output: .so file"
echo ""
echo " Example: "
echo ""
echo " To create the shared objective file use:"
echo ""
echo " $MORISROOT/share/scripts/create_shared_object.sh . build myinput"
echo ""
echo " To run moris with this input file use:"
echo ""
echo " $MORISROOT/build/main/moris myinput.so "
echo ""
echo "=============================================================="
echo ""

if [ ! $MORISROOT ];then
    echo " Error: MORISROOT environment variable not set"
    echo ""
    exit
fi 

if [ ! -d $MORISROOT ];then
    echo " Error: $MORISROOT does not exist"
    echo ""
    exit
fi 

if [ "$1" ];then
    workdir=$1
    
    if [ ! -d "$workdir" ];then
       echo " Error: $workdir does not exist"
       echo ""
       exit
    fi
else
    echo " Error: no working directory provided"
    echo ""
    exit
fi

if [ "$2" ];then
    builddir=$2

    if [ ! -d "$MORISROOT/$builddir" ];then
       echo " Error: $workdir does not exist"
       echo ""
       exit
    fi
else
    echo " Error: no moris build directory provided"
    echo ""
    exit
fi
 
if [ "$3" ];then
    cppfile=$3

    if [ ! -f "$cppfile.cpp" ];then
       echo " Error: $cppfile.cpp does not exist"
       echo ""
       exit
    fi
else
    echo " Error: no source file provided"
    echo ""
    exit
fi

dbgflag=0

if [ "$4" ];then
    if [ "$4" = 'dbg' ];then
        dbgflag=1
    fi
fi

if [ ! -d "$MORISROOT/tmp" ];then
    mkdir "$MORISROOT/tmp"
fi

TMPDIR="$MORISROOT/tmp"

cd "$workdir"

workdir=`pwd`

rm -f $cppfile.so

mv "$MORISROOT/projects/mains/input_file.cpp" "$TMPDIR/."

ln -s "$workdir/$cppfile.cpp" "$MORISROOT/projects/mains/input_file.cpp"

touch "$MORISROOT/projects/mains/input_file.cpp"

cd "$MORISROOT/$builddir"

make shared_object_file

cd "$workdir"

mv "$MORISROOT/$builddir/lib/input_file.so" $cppfile.so

if [ "$dbgflag" = '0' ];then
    rm "$MORISROOT/projects/mains/input_file.cpp"

    tmpfilehead=`head -1 "$TMPDIR/input_file.cpp"`

    if [ "$tmpfilehead" = '//dummy file - placeholder for dynamically linked object file' ];then
        echo ""
        echo " restoring input_file.cpp from $TMPDIR"
        echo ""
        mv "$TMPDIR/input_file.cpp" "$MORISROOT/projects/mains/."
    else
        echo ""
        echo " restoring input_file.cpp from git repository"
        echo ""
    
        cd "$MORISROOT/$builddir"
        git checkout -- "$MORISROOT/projects/mains/input_file.cpp"
    fi
else
    echo ""
    echo " keep soft link from $cppfile.cpp to input_file.cpp"
    echo ""
fi
