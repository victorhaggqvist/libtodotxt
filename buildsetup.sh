echo "pre stuffs"
$LIBGIT2DIR="./libgit2"
$GTESTDIR="./gtest"
echo "checking for libgit2"
if [ ! -d "$LIBGIT2DIR" ]; then
echo "getting libgit2"
git clone https://github.com/libgit2/libgit2.git
cd libgit2
git checkout v0.21.1
cd ..
else
echo "libgit2 exists"
fi

cd test
echo "checking for gtest"
if [ ! -d "$GTEST2DIR" ]; then
echo "getting gtest"
wget --quiet -Ogtest.zip https://googletest.googlecode.com/files/gtest-1.7.0.zip
unzip -qq gtest.zip
mkdir gtest
mv gtest-1.7.0/* gtest
else
echo "gtest exists"
fi