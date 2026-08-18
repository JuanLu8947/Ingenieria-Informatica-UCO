#!/bin/bash
#Version: 1.0
#Version: 1.1
#- Fijado error al comprobar test que lanzan excepciones y termian
#  con EXIT_FAILURE. A partir de ahora se comprueba la salida siempre.
#Version: 1.2
#- Mejorada el comprobar las diferencias con salidas extremadamente largas.
#  En vez de usar dos strings y comprobar si son diferentes, utilizamos
#  siempre el diff entre el fichero con la salida y lo experado.

set -e

if [ "x$1" == "x" ] || [ ! -x "$1" ]; then
	echo "uso: $0 <program> [test dir]"
        echo "Version: 1.2"
        exit 1
fi

TEST_DIR="./tests"
if [ "x$2" != "x" ] ; then
   TEST_DIR="${2}"
fi

prog="$1" 

PASS=0
TOTAL=0

for t in ${TEST_DIR}/?? ; do
        echo -n "test $t : "
        TMPFILE=/tmp/ed_test_$$_${RANDOM}
        touch ${TMPFILE}
	TOTAL=$(( $TOTAL + 1 ))
        set +e
        $prog $t >& ${TMPFILE}
	RETCODE="$?"
        set -e
        if [ $RETCODE -eq 0 ]; then
            set +e
            DIFF=$( diff -q $TMPFILE ${t}.a >& /dev/null)
            RETCODE="$?"
            set -e
            if [ $RETCODE -eq 0 ]; then
                PASS=$(( $PASS + 1 ))
                echo " Success!"
            else
                echo " Fail! Results are different."
                echo -e "\t Expected:"
                echo "[$(cat ${t}.a)]"
                echo -e "\t Your output in ${TMPFILE}:"
                echo "[$(cat ${TMPFILE})]"
                echo -e "\t Differences:"
                set +e
                echo "[$(diff $TMPFILE ${t}.a)]"
                set -e
            fi
        else
            echo " Fail! Runtime error with return code ${RETCODE}."
            echo " Output in ${TMPFILE}:"
            echo "[$(cat ${TMPFILE})]"
        fi
done

echo "You pass $PASS of $TOTAL tests."
if [ "$PASS" == "$TOTAL" ]; then
	exit 0
else
	exit 1
fi

