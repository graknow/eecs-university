public class LinkedQueueImplementation<T> implements QueueInterface<T> {
    private LinkedItem<T> front;
    private LinkedItem<T> back;
    
    private int size;

    public LinkedQueueImplementation() {
        front = null;
        back = null;

        size = 0;
    }

    // Adds an item to the back of the queue.
    @Override
    public void enqueue(T item) throws QueueOverflowException {
        LinkedItem<T> nextBack = new LinkedItem<T>(item, null);

        if(isFull()) {
            throw new QueueOverflowException("Queue is full.  Item not added!");
        }

        if(isEmpty()) {
            back = nextBack;
            front = nextBack;
        }
        else {
            back.setNextItem(nextBack);
            back = nextBack;
        }
        size++;
    }

    // Reads the item at the front of the queue and removes it.
    @Override
    public T dequeue() throws QueueUnderflowException {
        if(isEmpty()) {
            throw new QueueUnderflowException("Queue is empty.  Could not remove item!");
        }

        LinkedItem<T> returnItem = front;
        front = returnItem.getNextItem();

        size--;
        
        return returnItem.getValue();
    }

    @Override
    public int size() {
        return size;
    }

    @Override
    public boolean isEmpty() {
        return size == 0;
    }

    @Override
    public boolean isFull() {
        return false;
    }
    
}