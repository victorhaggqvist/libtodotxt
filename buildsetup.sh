echo "pre stuffs"
rm -rf libgit2
git clone https://github.com/libgit2/libgit2.git
cd libgit2
git checkout v0.21.1
cd ..

cd test
rm -rf gtest-1.7.0 gtest-1.7.0.zip gtest
wget --quiet -Ogtest.zip https://googletest.googlecode.com/files/gtest-1.7.0.zip
unzip -qq gtest.zip
mkdir gtest
mv gtest-1.7.0/* gtest