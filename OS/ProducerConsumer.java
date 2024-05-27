import java.util.LinkedList;
import java.util.Queue;
import java.util.Scanner;

public class ProducerConsumer {

    // Buffer size
    private static final int BUFFER_SIZE = 5;
    // Shared buffer using a queue
    private static Queue<Integer> buffer = new LinkedList<>();
    // Lock object for synchronization
    private static final Object lock = new Object();
    // Counter to track the number of items in the buffer
    private static int count = 0;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // Input: Number of items to produce
        System.out.println("Enter the number of items to produce:");
        int itemCount = scanner.nextInt();

        // Creating and starting the producer thread
        Thread producerThread = new Thread(() -> {
            for (int i = 1; i <= itemCount; i++) {
                produce(i); // Produce item
            }
        });

        // Creating and starting the consumer thread
        Thread consumerThread = new Thread(() -> {
            for (int i = 1; i <= itemCount; i++) {
                consume(); // Consume item
            }
        });

        producerThread.start(); // Start the producer thread
        consumerThread.start(); // Start the consumer thread
    }

    // Method to produce items
    public static void produce(int item) {
        synchronized (lock) { // Synchronize on the lock object
            while (count == BUFFER_SIZE) { // Wait if the buffer is full
                try {
                    lock.wait(); // Wait for space to become available
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                }
            }

            buffer.add(item); // Add the item to the buffer
            count++; // Increment the count of items in the buffer
            System.out.println("Produced: " + item); // Print produced item

            lock.notifyAll(); // Notify all waiting threads
        }
    }

    // Method to consume items
    public static void consume() {
        synchronized (lock) { // Synchronize on the lock object
            while (count == 0) { // Wait if the buffer is empty
                try {
                    lock.wait(); // Wait for items to become available
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                }
            }

            int item = buffer.remove(); // Remove the item from the buffer
            count--; // Decrement the count of items in the buffer
            System.out.println("Consumed: " + item); // Print consumed item

            lock.notifyAll(); // Notify all waiting threads
        }
    }
}
