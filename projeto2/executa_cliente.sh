#!/bin/bash
for ((i=0;i<50;i++)) do
	./talker.o 143.106.16.205 l >> talker_listadisciplinas.out
	echo "$i iteracao de l"
done
for ((i=0;i<50;i++)) do
	./talker.o 143.106.16.205 i >> talker_infodisciplinas.out
	echo "$i iteraçao de i"
done
for ((i=0;i<50;i++)) do
	./talker.o 143.106.16.205 w MC548 "teste"  >> talker_escrevercomentariodisciplina.out
	echo "$i iteraçao de w MC548 teste"
done
for ((i=0;i<50;i++)) do
	./talker.o 143.106.16.205 c MC548 >> talker_lercomentariodisciplina.out
	echo "$i iteraçao de c MC548"
done
for ((i=0;i<50;i++)) do
	./talker.o 143.106.16.205 i MC548 >> talker_infoumadisciplina.out
	echo "$i iteraçao de i MC548"
done
for ((i=0;i<50;i++)) do
	./talker.o 143.106.16.205 p MC548 >> talker_programaumadisciplina.out
	echo "$i iteraçao de p MC548"
done
