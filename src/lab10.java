
 class QueueT {
	char n;
	int valueSet = 0;

	synchronized int get() {
		while (valueSet<3)
			try {
				wait();
				valueSet++;
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				// e.printStackTrace();
				System.out.println("InterruptedException caught");
			}
		System.out.println("Got: " + n);
		valueSet = 0;
		notify();
		return n;

	}

	synchronized void put(char n) {
		while (valueSet<3)
			try {
				wait();
				valueSet++;
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				// e.printStackTrace();
				System.out.println("InterruptedException caught");
			}
		this.n = n;
		valueSet = 0;
		System.out.println("Put: " + n);
		notify();
	}
}

 class Producer implements Runnable {
	QueueT q;
	String myCharArray = "Jain university";

	Producer(QueueT q) {
		this.q = q;
		new Thread(this, "Producer").start();
	}

	public void run() {
		int i = 0,j=0;
		while (j<3) {
			System.out.println(Thread.currentThread().getName() + "is running");
			try {
				Thread.sleep(1000);
				j++;
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			if (i >= myCharArray.length())
				i = 0;
			q.put(myCharArray.charAt(i++));
		}
	}
}

 class Consumer implements Runnable {
	QueueT q;
	Consumer(QueueT q){
		this.q=q;
		new Thread(this,"Consumer").start();
	}
	public void run(){
		int i=0;
		while(i<3){
			System.out.println(Thread.currentThread().getName() + "is running");
			try {
				Thread.sleep(1000);
				i++;
				break;
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			q.get();
		}
	}

}

public class lab10 {
	public static void main(String[] args) {
		QueueT qq = new QueueT();
		new Producer(qq);
		new Consumer(qq);

		System.out.println(Thread.currentThread().activeCount());

	}
}
