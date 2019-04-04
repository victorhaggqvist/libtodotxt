libtodotxt
==========

# Build

```sh
mkdir build
cd build
cmake .. && make
```

To build with tests

```sh
mkdir build
cd build
cmake -Dbuild_tests=ON .. && make test
./bin/libtodotxt_test
```

# Formatting cleifications

## Creation date

Date format

```
YYYY-MM-DD
```

Or well technically `[0-9]{4}-[0-9]{2}-[0-9]{2}` but the above may become critical in the future.

Has creation date

```
2011-03-02 Document +TodoTxt task format
(A) 2011-03-02 Call Mom
x (A) 2011-03-04 2011-03-02 Call Mom
```

Has NO creation date

```
2011-03-02NoSpaceHere Document +TodoTxt task format
x (A) 2011-03-02 Call Mom
And obviously this
```

## Key->value pairs

A key->value pair comes after the "todo text" like this

```
Do something key:value
```

- A valid key is anything that ia valid regex word character (\w)
- A valid value is anything that ia valid regex non-whitespace (\S)

## Contexts and projects

Both contexts and projects should be placed at the end fo the todo. They can be mixed how ever you like. Though the out put of contexts and projects will appear at the end of the string with projects first and contexts following. Placing contexts or projects elsewhere will mess stuff up.

Sample

```
Complete lib and stuff @hax +libtodotxt
```

Will assample to

```
Complete lib and stuff +libtodotxt @hax
```

# API info
### TodoItem

`TodoIte::IsDone()`
