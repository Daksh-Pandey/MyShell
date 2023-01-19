make:
	gcc ls.c -o ls
	gcc cat.c -o cat
	gcc date.c -o date
	gcc mkdir.c -o mkdir
	gcc rm.c -o rm
	gcc shell.c -lpthread -o shell
	./shell

clean:
	rm ls cat date mkdir rm