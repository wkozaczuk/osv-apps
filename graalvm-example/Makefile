module: main.so

CFLAGS = -std=gnu99 -fpie -rdynamic

main.so: libhello.so main.c
	$(CC) -o $@ $(CFLAGS) -I. main.c -L. -lhello -ldl

Hello.class: Hello.java upstream/graalvm-ce-1.0.0-rc7
	upstream/graalvm-ce-1.0.0-rc7/bin/javac -d . Hello.java

libhello.so: Hello.class upstream/graalvm-ce-1.0.0-rc7
	upstream/graalvm-ce-1.0.0-rc7/bin/native-image --no-server -R:+GeneratePIC --shared -H:Kind=SHARED_LIBRARY -H:Name=libhello

upstream/graalvm-ce-1.0.0-rc7: 
	mkdir -p upstream
	wget -c -O upstream/graalvm.tar.gz https://github.com/oracle/graal/releases/download/vm-1.0.0-rc7/graalvm-ce-1.0.0-rc7-linux-amd64.tar.gz
	cd upstream && tar xf graalvm.tar.gz

clean:
	rm -rf *.class libhello* main*.so graal*.h upstream
