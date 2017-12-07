MFLAGS = -g -I/usr/local/include -L/usr/local/lib -lgmp


mac:
	g++ -x c -o rsa-dec rsa-dec.c $(MFLAGS) 
	g++ -x c -o rsa-enc rsa-enc.c $(MFLAGS)
	g++ -x c -o rsa-keygen rsa-keygen.c $(MFLAGS)

clean:
	rm rsa-dec rsa-enc rsa-keygen *.o
