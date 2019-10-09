SRC = $(shell readlink -f ../..)

upstream/KeyDB/.git:
	mkdir -p upstream
	cd upstream && git clone --depth 1 https://github.com/JohnSully/KeyDB.git

upstream/KeyDB/src/keydb-server: upstream/KeyDB/.git
	cd upstream/KeyDB && make MALLOC=libc

module: upstream/KeyDB/src/keydb-server
	$(SRC)/scripts/manifest_from_host.sh upstream/KeyDB/src/keydb-server > usr.manifest

clean:
	rm -rf upstream
