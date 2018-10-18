//
// Copyright (C) 2018 Waldek Kozaczuk
//
// This work is open source software, licensed under the terms of the
// BSD license as described in the LICENSE file in the top-level directory.
//
import org.graalvm.nativeimage.IsolateThread;
import org.graalvm.nativeimage.c.function.CEntryPoint;

public class Hello {
    @CEntryPoint(name = "graal_main")
    public static void main(IsolateThread thread) {
        System.out.println("Hello, World from GraalVM on OSv!");
    }
}
