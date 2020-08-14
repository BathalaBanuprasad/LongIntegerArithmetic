2_assn.out: 2_impl.o 2_client.o
		gcc 2_impl.o 2_client.o
2_impl.o: 2_impl.c 2_header.h
		gcc -c 2_impl.c
2_client.o: 2_client.c 2_header.h
		gcc -c 2_client.c
