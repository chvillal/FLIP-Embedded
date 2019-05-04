all: test_send_recv

test_send_recv: test_send_recv.c
        gcc -o test_send_recv test_send_recv.c flip.c
		
clean:
        rm -f test_send_recv