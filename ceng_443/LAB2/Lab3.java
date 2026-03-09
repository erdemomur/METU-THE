import java.util.stream.*;
import java.io.File;
import java.io.IOException;
import java.nio.file.*;

public class Lab3 {
    public static void main(String args[]) {
        Lab3 lab3 = new Lab3();
        String fileName = args[0];
        int questionNo = Integer.parseInt(args[1]);
        switch (questionNo) {
            case 1:
                lab3.q1(fileName);
                break;
            case 2:
                lab3.q2(fileName);
                break;
            case 3:
                lab3.q3(fileName);
                break;
            case 4:
                lab3.q4(fileName);
                break;
            case 5:
                lab3.q5(fileName);
                break;
            case 6:
                lab3.q6(fileName);
                break;
        }

    }

    String items[] = { "bread", "milk", "egg", "potatoes", "tomatoes" };

    double parseDoubleOrZero(String s) {
        return s.equals("") ? 0.0 : Double.parseDouble(s);
    }

    int parseIntOrZero(String s) {
        return s.equals("") ? 0 : Integer.parseInt(s);
    }

    class Purchase {
        String name;
        int age;
        String date;
        double prices[];
        int quantities[];

        Purchase(String line) {
            String[] fields = line.split(",", -1);
            this.name = fields[0];
            this.age = Integer.parseInt(fields[1]);
            this.date = fields[2];
            this.prices = new double[] { parseDoubleOrZero(fields[3]), parseDoubleOrZero(fields[5]),
                    parseDoubleOrZero(fields[7]), parseDoubleOrZero(fields[9]),
                    parseDoubleOrZero(fields[11]) };
            this.quantities = new int[] { parseIntOrZero(fields[4]), parseIntOrZero(fields[6]),
                    parseIntOrZero(fields[8]), parseIntOrZero(fields[10]),
                    parseIntOrZero(fields[12]) };
        }
    };

    void q1(String fileName) {
        try (Stream<String> lines = Files.lines(Paths.get(fileName))) {
            int output = lines.skip(1)
                    .map(line -> new Purchase(line))
                    .filter(p -> p.name.startsWith("A"))
                    .flatMapToInt(p -> IntStream.of(p.quantities))
                    .sum();
            System.out.println(output);
        } catch (IOException e) {
        }
    }

    void q2(String fileName) {
        try (Stream<String> lines = Files.lines(Paths.get(fileName))) {
            double output = lines.skip(1)
                    .map(line -> new Purchase(line))
                    .flatMapToDouble(p -> DoubleStream.of(p.prices))
                    .max().getAsDouble();
            System.out.println(output);
        } catch (IOException e) {
        }
    }

    void q3(String fileName) {
        try (Stream<String> lines = Files.lines(Paths.get(fileName))) {
            Purchase output = lines.skip(1)
                    .map(line -> new Purchase(line))
                    .max((p1, p2) -> {
                        double total1 = 0;
                        double total2 = 0;
                        for (int i = 0; i < 5; i++) {
                            total1 += p1.prices[i] * p1.quantities[i];
                            total2 += p2.prices[i] * p2.quantities[i];
                        }
                        return Double.compare(total1, total2);
                    }).get();
            System.out.println(output.date);
        } catch (IOException e) {
        }
    }

    void q4(String fileName) {
        try (Stream<String> lines = Files.lines(Paths.get(fileName))) {
            int[] itemsPopularity = lines.skip(1)
                    .map(line -> new Purchase(line))
                    .filter(p -> p.date.charAt(6) == '2')
                    .collect(
                            () -> new int[5],
                            (acc, p) -> {
                                for (int i = 0; i < 5; i++) {
                                    acc[i] += (p.quantities[i] > 0) ? 1 : 0;
                                }
                            },
                            (a1, a2) -> {
                                for (int i = 0; i < 5; i++) {
                                    a1[i] += a2[i];
                                }
                            });
            int max = 0;
            int maxIndex = 0;
            for (int i = 0; i < itemsPopularity.length; i++) {
                if (itemsPopularity[i] > max) {
                    max = itemsPopularity[i];
                    maxIndex = i;
                }
            }
            System.out.println(items[maxIndex]);

        } catch (IOException e) {
        }
    }

    void q5(String fileName) {
        try (Stream<String> lines = Files.lines(Paths.get(fileName))) {
            int[] itemsPopularity = lines.skip(1)
                    .map(line -> new Purchase(line))
                    .filter(p -> p.date.charAt(6) == '2')
                    .collect(
                            () -> new int[5],
                            (acc, p) -> {
                                for (int i = 0; i < 5; i++) {
                                    acc[i] += p.quantities[i];
                                }
                            },
                            (a1, a2) -> {
                                for (int i = 0; i < 5; i++) {
                                    a1[i] += a2[i];
                                }
                            });
            int min = Integer.MAX_VALUE;
            int minIndex = 0;

            for (int i = 0; i < itemsPopularity.length; i++) {
                if (itemsPopularity[i] < min) {
                    min = itemsPopularity[i];
                    minIndex = i;
                }
            }
            System.out.println(items[minIndex]);
        } catch (IOException e) {
        }
    }

    void q6(String fileName) {
        try (Stream<String> lines = Files.lines(Paths.get(fileName))) {
            double[] averagePerProduct = lines.skip(1)
                    .map(line -> new Purchase(line))
                    .collect(
                            () -> new double[10],
                            (acc, p) -> {
                                for (int i = 0; i < 5; i++) {
                                    if (p.quantities[i] > 0) {
                                        acc[i] = acc[i] + 1;
                                        acc[i + 5] = acc[i + 5] + p.age;
                                    }
                                }
                            },
                            (a1, a2) -> {
                            });
            double min = Double.MAX_VALUE;
            int minIndex = 0;

            for (int i = 5; i < averagePerProduct.length; i++) {
                if (averagePerProduct[i] < min) {
                    min = averagePerProduct[i];
                    minIndex = i;
                }
            }
            System.out.println(items[minIndex]);
        } catch (IOException e) {
        }
    }
}