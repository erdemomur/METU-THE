import java.util.concurrent.ThreadLocalRandom;
import java.util.concurrent.atomic.AtomicLong;
import java.lang.Thread;

public class Actions {
    private static AtomicLong counter = new AtomicLong(0);

    private static void action(int min_time, int max_time, String msg) {
        long action_no = counter.incrementAndGet();
        assert min_time <= max_time;

        if (max_time > 0) {
            try {
                int wait_time;
                if (min_time == max_time) {
                    wait_time = max_time;
                } else {
                    wait_time = ThreadLocalRandom.current().nextInt(min_time, max_time + 1);
                }
                Thread.sleep(wait_time);
            } catch (InterruptedException e) {
            }
        }
        System.out.println(
                msg + " (on Thread " + Thread.currentThread().getId() + ") (Action number: " + action_no + ")");

    }

    static void start_element_generator(int element_no) {
        action(10, 20, "Started E" + element_no + " Generator");
    }

    static void generate_element(int element_no) {
        action(10, 20, "Generated E" + element_no);
    }

    static void stop_element_generator(int element_no) {
        action(10, 20, "Stopped E" + element_no + " Generator");
    }

    static void start_compound_generator() {
        action(10, 20, "Started Compound Generator");
    }

    static void generate_compound() {
        action(10, 20, "Generated Compound");
    }

    static void stop_compound_generator() {
        action(10, 20, "Stopped Compound Generator");
    }

}
