import org.graalvm.nativeimage.IsolateThread;
import org.graalvm.nativeimage.c.function.CEntryPoint;

public class Hello {
    @CEntryPoint(name = "graal_main")
    public static void main(IsolateThread thread) {
        System.out.println("Hello, World from GraalVM on OSv!");
    }
}
