compile :
	reset
	gcc -Wall -Wextra ./code/config/*.c ./code/controller/*.c ./code/database/*.c ./code/main.c ./code/view/*.c ./code/engineering/*.c `mysql_config --cflags --include --libs` -o ./client.out

run :
	make
	reset
	./client.out
