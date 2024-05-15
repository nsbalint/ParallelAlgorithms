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

        double[][] matrix = initializeMatrix(size);

        long startTime = System.currentTimeMillis();
        double[] result = gaussianElimination(matrix, threadCount);
        long endTime = System.currentTimeMillis();
        long executionTime = endTime - startTime;

        writeResultsToFile(outputFile, matrix, result, executionTime);

        System.out.println("Results written to " + outputFile);

        if (checkSolution(matrix, result)) {
            System.out.println("Solution verified: The result vector satisfies the original equations.");
        } else {
            System.out.println("Solution verification failed: The result vector does not satisfy the original equations.");
        }
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
        ExecutorService executor = Executors.newFixedThreadPool(threadCount);
        int size = matrix.length;

        // Forward elimination
        for (int i = 0; i < size - 1; i++) {
            for (int j = i + 1; j < size; j++) {
                executor.execute(new ForwardEliminationTask(matrix, i, j));
            }
        }

        executor.shutdown();
        try {
            executor.awaitTermination(Long.MAX_VALUE, TimeUnit.NANOSECONDS);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        double[] result = new double[size];
        for (int i = size - 1; i >= 0; i--) {
            double sum = matrix[i][size];
            for (int j = i + 1; j < size; j++) {
                sum -= matrix[i][j] * result[j];
            }
            result[i] = sum / matrix[i][i];
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

    private static boolean checkSolution(double[][] matrix, double[] result) {
    	   int size = matrix.length;
           double[] calculatedResult = new double[size];

           for (int i = 0; i < size; i++) {
               double sum = 0.0;
               for (int j = 0; j < size; j++) {
                   sum += matrix[i][j] * result[j];
               }
               calculatedResult[i] = sum;
           }

           for (int i = 0; i < size; i++) {
               if (Math.abs(calculatedResult[i] - matrix[i][size]) > 1e+2) {
                   return false; 
               }
           }

           return true;
    }

    private static class ForwardEliminationTask implements Runnable {
        private final double[][] matrix;
        private final int i;
        private final int j;

        public ForwardEliminationTask(double[][] matrix, int i, int j) {
            this.matrix = matrix;
            this.i = i;
            this.j = j;
        }

        public void run() {
            double factor = matrix[j][i] / matrix[i][i];
            for (int k = i; k < matrix[0].length; k++) {
                matrix[j][k] -= factor * matrix[i][k];
            }
        }
    }
}
