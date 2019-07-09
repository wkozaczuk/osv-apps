module: hello

GRAAL_VERSION=19.1.0

Hello.class: Hello.java upstream/graalvm-ce-$(GRAAL_VERSION)
	upstream/graalvm-ce-$(GRAAL_VERSION)/bin/javac -d . Hello.java

hello: Hello.class upstream/graalvm-ce-$(GRAAL_VERSION)/bin/native-image
	upstream/graalvm-ce-$(GRAAL_VERSION)/bin/native-image --no-server Hello

upstream/graalvm-ce-$(GRAAL_VERSION):
	mkdir -p upstream
	wget -c -O upstream/graalvm-ce-linux-amd64-$(GRAAL_VERSION).tar.gz https://github.com/oracle/graal/releases/download/vm-$(GRAAL_VERSION)/graalvm-ce-linux-amd64-$(GRAAL_VERSION).tar.gz
	cd upstream && tar xf graalvm-ce-linux-amd64-$(GRAAL_VERSION).tar.gz

upstream/graalvm-ce-$(GRAAL_VERSION)/bin/native-image: upstream/graalvm-ce-$(GRAAL_VERSION)
	cd upstream/graalvm-ce-$(GRAAL_VERSION) && ./bin/gu install native-image && touch ./bin/native-image

clean:
	rm -rf *.class hello upstream
