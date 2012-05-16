#!/bin/bash
for ((i=0;i<50;i++)) do
	./talker.o 143.106.16.205 p MC548 >> talker_programaumadisciplina.out
	echo "$i iteraçao de p MC548"
done
