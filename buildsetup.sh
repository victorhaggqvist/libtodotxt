echo "pre stuffs"

echo "checking for libgit2"
if [ ! -d "./libgit2" ]; then
  echo "getting libgit2"
  git clone https://github.com/libgit2/libgit2.git
  cd libgit2
  git checkout v0.21.1
  cd ..
else
  echo "libgit2 exists"
fi

echo "checking for gtest"
if [ ! -d "./test/gtest" ]; then
  cd test
  echo "getting gtest"
  wget --quiet -Ogtest.zip https://googletest.googlecode.com/files/gtest-1.7.0.zip
  #rm -rf gtest-1.7.0
  unzip -qq gtest.zip
  mkdir gtest
  mv gtest-1.7.0/* gtest
else
  echo "gtest exists"
fi