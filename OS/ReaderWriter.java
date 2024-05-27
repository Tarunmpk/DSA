import java.util.Scanner;

public class ReaderWriter {

    private static int readerCount = 0;
    private static boolean isWriting = false;
    private static final Object lock = new Object();

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter the number of readers:");
        int readerCount = scanner.nextInt();

        System.out.println("Enter the number of writers:");
        int writerCount = scanner.nextInt();

        for (int i = 1; i <= readerCount; i++) {
            final int readerId = i;
            new Thread(() -> {
                try {
                    reader(readerId);
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                }
            }).start();
        }

        for (int i = 1; i <= writerCount; i++) {
            final int writerId = i;
            new Thread(() -> {
                try {
                    writer(writerId);
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                }
            }).start();
        }
    }

    public static void reader(int readerId) throws InterruptedException {
        synchronized (lock) {
            while (isWriting) {
                lock.wait();
            }
            readerCount++;
        }

        System.out.println("Reader " + readerId + " is reading.");
        Thread.sleep(1000); // Simulate reading
        System.out.println("Reader " + readerId + " has finished reading.");

        synchronized (lock) {
            readerCount--;
            if (readerCount == 0) {
                lock.notifyAll();
            }
        }
    }

    public static void writer(int writerId) throws InterruptedException {
        synchronized (lock) {
            while (readerCount > 0 || isWriting) {
                lock.wait();
            }
            isWriting = true;
        }

        System.out.println("Writer " + writerId + " is writing.");
        Thread.sleep(1000); // Simulate writing
        System.out.println("Writer " + writerId + " has finished writing.");

        synchronized (lock) {
            isWriting = false;
            lock.notifyAll();
        }
    }
}