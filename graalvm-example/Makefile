module: main.so

CFLAGS = -std=gnu99 -fPIC -rdynamic

main.so: libhello.so main.c
	$(CC) -pie -o $@ $(CFLAGS) -I. main.c -L. -lhello -ldl

Hello.class: Hello.java upstream/graalvm-ce-1.0.0-rc12
	upstream/graalvm-ce-1.0.0-rc12/bin/javac -d . Hello.java

libhello.so: Hello.class upstream/graalvm-ce-1.0.0-rc12
	upstream/graalvm-ce-1.0.0-rc12/bin/native-image --no-server --shared -H:Name=libhello

upstream/graalvm-ce-1.0.0-rc12:
	mkdir -p upstream
	wget -c -O upstream/graalvm.tar.gz https://github.com/oracle/graal/releases/download/vm-1.0.0-rc12/graalvm-ce-1.0.0-rc12-linux-amd64.tar.gz
	cd upstream && tar xf graalvm.tar.gz

clean:
	rm -rf *.class libhello* main*.so graal*.h upstream
