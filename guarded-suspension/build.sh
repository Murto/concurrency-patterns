DIR=`dirname $0`
mkdir -p $DIR/build
cd $DIR/build
cmake ..
make
