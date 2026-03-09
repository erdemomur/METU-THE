import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;

public class Controller {
    private int currentCapacity[];
    private int maxCapacity[];
    private int neededElementForCompound[];
    private static int stoppedElementGeneratorCounter;
    private ReentrantLock lock;
    private Condition full;
    private Condition empty;

    public Controller(int numberOfElement, int[] maxCapacity, int[] neededElementForCompound, ReentrantLock lock) {
        this.maxCapacity = maxCapacity;
        this.neededElementForCompound = neededElementForCompound;
        this.lock = lock;
        this.full = lock.newCondition();
        this.empty = lock.newCondition();
        this.currentCapacity = new int[numberOfElement];
    }

    public void generateElement(int type) {
        lock.lock();
        try {
            while (currentCapacity[type] == maxCapacity[type]) {
                stoppedElementGeneratorCounter++;
                if (stoppedElementGeneratorCounter == maxCapacity.length) {
                    stoppedElementGeneratorCounter = 0;
                    full.signal();
                }
                Actions.stop_element_generator(type + 1);
                empty.await();
                Actions.start_element_generator(type + 1);
            }
            Actions.generate_element(type + 1);
            currentCapacity[type]++;
        } catch (InterruptedException e) {
        } finally {
            lock.unlock();
        }
    }

    public void generateCompound(int numberOfCompoundPerRound) {
        lock.lock();
        try {
            boolean tanksFull = true;
            boolean tanksEmpty = true;
            while (tanksFull || tanksEmpty) {
                for (int i = 0; i < maxCapacity.length; i++) {
                    if (currentCapacity[i] < maxCapacity[i]) {
                        tanksFull = false;
                        break;
                    }
                }
                if (!tanksFull) {
                    full.await();
                    tanksFull = true;
                    Actions.start_compound_generator();
                }
                for (int i = 0; i < numberOfCompoundPerRound; i++) {
                    Actions.generate_compound();
                    for (int j = 0; j < maxCapacity.length; j++) {
                        currentCapacity[j] -= neededElementForCompound[j];
                    }
                }
                tanksEmpty = true;
                Actions.stop_compound_generator();
                empty.signalAll();
            }
        } catch (InterruptedException e) {
        } finally {
            lock.unlock();
        }
    }
}
