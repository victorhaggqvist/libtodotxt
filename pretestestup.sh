#!/bin/bash
TODOFILE="$(pwd)/bin/todo.txt"
echo 'test line' > ${TODOFILE}
echo 'x done test line' >> ${TODOFILE}
