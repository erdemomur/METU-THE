public class CompoundGenerator implements Runnable {
    private int[] neededElementForCompound;
    private int[] capacityOfTanks;
    private Controller controller;
    private int numberOfCompoundPerRound;

    public CompoundGenerator(int[] neededElementForCompound, int[] capacityOfTanks, Controller controller,
            int numberOfCompoundPerRound) {
        this.neededElementForCompound = neededElementForCompound;
        this.capacityOfTanks = capacityOfTanks;
        this.controller = controller;
        this.numberOfCompoundPerRound = numberOfCompoundPerRound;
    }

    @Override
    public void run() {
        while (true) {
            controller.generateCompound(numberOfCompoundPerRound);
        }
    }
}
