import java.util.Scanner;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class DiningPhilosophers {

    // Lock array representing the forks
    private static Lock[] forks;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // Input: Number of philosophers
        System.out.println("Enter the number of philosophers:");
        int philosopherCount = scanner.nextInt();

        // Initialize forks (one more than the number of philosophers for simplicity)
        forks = new Lock[philosopherCount];
        for (int i = 0; i < philosopherCount; i++) {
            forks[i] = new ReentrantLock();
        }

        // Create and start philosopher threads
        for (int i = 0; i < philosopherCount; i++) {
            final int philosopherId = i;
            new Thread(() -> {
                try {
                    philosopher(philosopherId);
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                }
            }).start();
        }
    }

    // Philosopher method
    public static void philosopher(int philosopherId) throws InterruptedException {
        while (true) {
            think(philosopherId); // Philosopher is thinking
            pickUpForks(philosopherId); // Philosopher picks up forks
            eat(philosopherId); // Philosopher is eating
            putDownForks(philosopherId); // Philosopher puts down forks
        }
    }

    // Simulate thinking
    private static void think(int philosopherId) throws InterruptedException {
        System.out.println("Philosopher " + philosopherId + " is thinking.");
        Thread.sleep((long) (Math.random() * 1000)); // Random thinking time
    }

    // Pick up forks
    private static void pickUpForks(int philosopherId) {
        int leftFork = philosopherId;
        int rightFork = (philosopherId + 1) % forks.length;

        // Ensure a consistent order of locking to prevent deadlock
        if (philosopherId % 2 == 0) {
            forks[leftFork].lock();
            forks[rightFork].lock();
        } else {
            forks[rightFork].lock();
            forks[leftFork].lock();
        }

        System.out.println("Philosopher " + philosopherId + " picked up forks.");
    }

    // Simulate eating
    private static void eat(int philosopherId) throws InterruptedException {
        System.out.println("Philosopher " + philosopherId + " is eating.");
        Thread.sleep((long) (Math.random() * 1000)); // Random eating time
    }

    // Put down forks
    private static void putDownForks(int philosopherId) {
        int leftFork = philosopherId;
        int rightFork = (philosopherId + 1) % forks.length;

        forks[leftFork].unlock();
        forks[rightFork].unlock();

        System.out.println("Philosopher " + philosopherId + " put down forks.");
    }
}