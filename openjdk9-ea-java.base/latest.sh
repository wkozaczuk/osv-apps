#!/bin/bash

wget -qO- https://jdk9.java.net/download/ | grep "document.getElementById(\"lin64JDKrpm\").href = \"http" | grep -o "http://.*tar.gz" | grep -o "ea+[0-9]\+_linux" | grep -o "[0-9]\+"
