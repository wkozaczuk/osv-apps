module: main.so

CFLAGS = -std=gnu99 -fpie -rdynamic

main.so: libhello.so main.c
	$(CC) -o $@ $(CFLAGS) -I. main.c -L. -lhello -ldl

libhello.so: Hello.class
	mkdir -p upstream
	#wget -c -O upstream/graalvm.tar.gz https://github.com/oracle/graal/releases/download/vm-1.0.0-rc7/graalvm-ce-1.0.0-rc7-linux-amd64.tar.gz
	#tar xf upstream/graalvm.tar.gz
	graalvm-ce-1.0.0-rc7/bin/native-image --no-server -R:+GeneratePIC --shared -H:Kind=SHARED_LIBRARY -H:Name=libhello
	#-H:+GeneratePIC creates smalled so and does not seem to work

%.class: %.java
	graalvm-ce-1.0.0-rc7/bin/javac -d . $^

clean:
	rm -f *.class libhello* main*.so graal*.h
