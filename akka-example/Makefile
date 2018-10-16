#
# Copyright (C) 2018 Waldek Kozaczuk
#
# This work is open source software, licensed under the terms of the
# BSD license as described in the LICENSE file in the top-level directory.
#

.PHONY: module

module: akka-example.jar

akka-example.jar: src/main/scala/demo/FileService.scala
	mvn package
	cp target/akka-example-1.0-SNAPSHOT-jar-with-dependencies.jar akka-example.jar

clean:
	mvn clean
	rm akka-example.jar
