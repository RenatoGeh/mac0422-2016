Um resumo rápido do que eu fiz para criar a syscall. Segui os passos daquele pdf, mas precisei modificar algumas coisas que estavam dando errado.
Todos os arquivos que eu alterei estão no imagefile.img
Eu fiz o report no txt, porque eu não estava muito seguro de alterar as coisas no .tex .


Em /usr/src/servers/pm/, eu fiz as alterações:

/usr/src/servers/pm/table.c
adicionei 
	do_fork_batch ao comando 64

/usr/src/servers/pm/proto.h:
adicionei o protótipo
	/* misc.c */
	_PROTOTYPE( int do_fork_batch, (void) );

/usr/src/servers/pm/misc.c:
adicionei a função
	PUBLIC int do_fork_batch()
	{
		printf("\TODO fork here\n");
		return(OK);
	}


Depois disso, fiz esses dois makes para compilar o server:

	/usr/src/servers/make image
	/usr/src/servers/make install


Nos dois callnr.h, eu adicionei o define. 
	/usr/src/include/minix/callnr.h:
	/usr/include/minix/callnr.h:
		#define FORK_BATCH 64

(Na imagem do floppy tem um arquivo 'src', que eu nomeei errado, que se refere ao callnr.h do usr/src)


Criei o arquivo _fork_batch.c:
	/usr/src/lib/posix/_fork_batch.c

Adicionei ele também no Makefile.in
	_fork_batch.c\


Então, executei o make:
	/usr/src/lib/posix/make Makefile

E depois eu compilei a biblioteca:
	/usr/src/make libraries

Daí eu criei a imagem do sistema:
	/usr/src/tools/make hdboot
	/usr/src/tools/make install


No meu Minix, o install criou o arquivo 
	/boot/image/3.1.2ar1

Para dar boot nele, na tela de boot, eu executo:
	image=/boot/image/<name of boot-image>
	boot