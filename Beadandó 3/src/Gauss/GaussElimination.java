package Gauss;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Arrays;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

public class GaussElimination {

    public static void main(String[] args) {
        if (args.length != 3) {
            System.out.println("Usage: java GaussElimination <matrix size> <output file> <thread count>");
            return;
        }

        int size = Integer.parseInt(args[0]);
        String outputFile = args[1];
        int threadCount = Integer.parseInt(args[2]);

        // Initialize matrix with random numbers
        double[][] matrix = initializeMatrix(size);

        // Measure time for Gaussian Elimination
        long startTime = System.currentTimeMillis();

        // Perform Gaussian Elimination
        double[] result = gaussianElimination(matrix, threadCount);

        long endTime = System.currentTimeMillis();
        long executionTime = endTime - startTime;

        // Write results to output file
        writeResultsToFile(outputFile, matrix, result, executionTime);

        System.out.println("Results written to " + outputFile);
    }

    private static double[][] initializeMatrix(int size) {
        double[][] matrix = new double[size][size + 1];
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size + 1; j++) {
                matrix[i][j] = Math.random() * 100; 
            }
        }
        return matrix;
    }

    private static double[] gaussianElimination(double[][] matrix, int threadCount) {
        int size = matrix.length;
        ExecutorService executor = Executors.newFixedThreadPool(threadCount);

        // Forward elimination
        for (int i = 0; i < size - 1; i++) {
            for (int j = i + 1; j < size; j++) {
                executor.execute(new ForwardEliminationTask(matrix, i, j, size));
            }
        }

        executor.shutdown();
        try {
            executor.awaitTermination(Long.MAX_VALUE, TimeUnit.NANOSECONDS);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        // Back substitution
        double[] result = new double[size];
        for (int i = size - 1; i >= 0; i--) {
            double sum = 0.0;
            for (int j = i + 1; j < size; j++) {
                sum += matrix[i][j] * result[j];
            }
            result[i] = (matrix[i][size] - sum) / matrix[i][i];
        }

        return result;
    }

    private static void writeResultsToFile(String outputFile, double[][] matrix, double[] result, long executionTime) {
        try (FileWriter writer = new FileWriter(outputFile)) {
            writer.write("Matrix after Gaussian Elimination:\n");
            writer.write(matrixToString(matrix) + "\n\n");
            writer.write("Result vector:\n");
            writer.write(Arrays.toString(result) + "\n\n");
            writer.write("Execution time: " + executionTime + " milliseconds\n");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static String matrixToString(double[][] matrix) {
        StringBuilder sb = new StringBuilder();
        for (double[] row : matrix) {
            for (double element : row) {
                sb.append(String.format("%.2f ", element));
            }
            sb.append("\n");
        }
        return sb.toString();
    }

    private static class ForwardEliminationTask implements Runnable {
        private final double[][] matrix;
        private final int i;
        private final int j;
        private final int size;

        public ForwardEliminationTask(double[][] matrix, int i, int j, int size) {
            this.matrix = matrix;
            this.i = i;
            this.j = j;
            this.size = size;
        }

        public void run() {
            double ratio = matrix[j][i] / matrix[i][i];
            for (int k = i; k < size + 1; k++) {
                matrix[j][k] -= ratio * matrix[i][k];
            }
        }
    }
}
