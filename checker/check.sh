#!/bin/bash
make
ls | grep bonus > /dev/null
if [ "$?" -eq "0" ]; then
	export LD_LIBRARY_PATH=. ; ./eval.sh bonus
else
	export LD_LIBRARY_PATH=. ; ./eval.sh
fi
