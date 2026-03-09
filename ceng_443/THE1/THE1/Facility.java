/* Usage of AI */
/* I used AI primarily for the initial stages of the assignment to 
clarify the requirements and determine an efficient file structure. 
The core logic and the majority of the code were written by myself. 
I only used Copilot's autocomplete feature for basic code 
snippets, such as simple loops. */

import java.util.concurrent.locks.ReentrantLock;

public class Facility {
    public static void main(String[] args) {
        int numberOfElement = Integer.parseInt(args[0]);
        int[] capacityOfTanks = new int[numberOfElement];
        for (int i = 0; i < numberOfElement; i++) {
            capacityOfTanks[i] = Integer.parseInt(args[i + 1]);
        }

        int[] neededElementForCompound = new int[numberOfElement];
        for (int i = numberOfElement + 1; i < numberOfElement * 2 + 1; i++) {
            neededElementForCompound[i - numberOfElement - 1] = Integer.parseInt(args[i]);
        }

        int numberOfCompoundPerRound = Integer.MAX_VALUE;
        for (int i = 0; i < numberOfElement; i++) {
            int temp = capacityOfTanks[i] / neededElementForCompound[i];
            if (temp < numberOfCompoundPerRound) {
                numberOfCompoundPerRound = temp;
            }
        }

        ReentrantLock lock = new ReentrantLock(true);
        Controller controller = new Controller(numberOfElement, capacityOfTanks, neededElementForCompound, lock);

        for (int i = 0; i < numberOfElement; i++) {
            ElementGenerator elementGenerator = new ElementGenerator(i, capacityOfTanks[i], controller);
            Thread t = new Thread(elementGenerator);
            t.start();
        }
        CompoundGenerator compoundGenerator = new CompoundGenerator(neededElementForCompound, capacityOfTanks,
                controller, numberOfCompoundPerRound);
        Thread t2 = new Thread(compoundGenerator);
        t2.start();
    }
}
