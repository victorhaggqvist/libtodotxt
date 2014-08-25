echo "pre stuffs"
$LIBGIT2DIR="./libgit2"
echo "checking for libgit2"
if [ ! -d "$LIBGIT2DIR" ]; then
echo "getting libgit2"
git clone https://github.com/libgit2/libgit2.git
cd libgit2
git checkout v0.21.1
cd ..
fi

cd test
rm -rf gtest-1.7.0.zip gtest-1.7.0
wget --quiet -Ogtest.zip https://googletest.googlecode.com/files/gtest-1.7.0.zip
rm -rf gtest-1.7.0
unzip -qq gtest.zip
rm -rf gtest
mkdir gtest
mv gtest-1.7.0/* gtest