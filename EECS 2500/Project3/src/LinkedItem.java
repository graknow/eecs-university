public class LinkedItem {
    int value = 0;
    LinkedItem nextItem = null;

    public LinkedItem(int a) {
        value = a;
    }

    public int getValue() {
        return value;
    }

    public LinkedItem getNext() {
        return nextItem;
    }

    public void setNext(LinkedItem L) {
        nextItem = L;
    }
}
