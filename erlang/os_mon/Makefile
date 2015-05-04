OTP_VERSION=17.3
ERLS=$(wildcard src/*.erl)
BEAMS=$(ERLS:src/%.erl=ebin/%.beam)
C_SRCS=$(wildcard c_src/*.c)
DRIVERS=$(C_SRCS:c_src/%.c=priv/lib/%.so)
ROOTFS=../ROOTFS

all: $(BEAMS) $(DRIVERS)

priv/lib/%.so: c_src/%.c | priv/lib
	gcc -o "$@" -I$(ROOTFS)/usr/lib64/erlang/usr/include -Wall -Wextra -Werror -fPIC -shared "$<"

priv/lib:
	mkdir -p priv/lib

ebin/%.beam: src/%.erl
	../otp_src_$(OTP_VERSION)/bin/erlc -Iinclude -o ebin "$<"

clean:
	rm -rf ebin/*.beam priv/lib/*.so
