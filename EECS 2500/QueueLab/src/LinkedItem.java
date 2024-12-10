public class LinkedItem<T> {
    private T value;                    // The value at the item.
    private LinkedItem<T> nextItem;     // Pointer to the next item.

    public LinkedItem() {
        value = null;
        nextItem = null;
    }

    public LinkedItem(T value, LinkedItem<T> nextItem) {
        this.value = value;
        this.nextItem = nextItem;
    }

    public T getValue() {
        return value;
    }

    public void setValue(T value) {
        this.value = value;
    }

    public LinkedItem<T> getNextItem() {
        return nextItem;
    }

    public void setNextItem(LinkedItem<T> nextItem) {
        this.nextItem = nextItem;
    }
}
