public class ElementGenerator implements Runnable {
    private int type;
    private int maxCapacity;
    private int currentCapacity;
    private Controller controller;

    public ElementGenerator(int type, int maxCapacity, Controller controller) {
        this.type = type;
        this.maxCapacity = maxCapacity;
        this.controller = controller;
    }

    @Override
    public void run() {
        Actions.start_element_generator(type + 1);
        while (true) {
            controller.generateElement(type);
        }
    }
}
