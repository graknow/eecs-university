public class Project3 {
    public static void main(String[] args) throws Exception {
        
        LinkedItem a = new LinkedItem(1);
        a.setNext(new LinkedItem(2));
        a.getNext().setNext(new LinkedItem(3));
        a.getNext().getNext().setNext(new LinkedItem(4));

        System.out.println(listSize(a));
        System.out.println(a.getValue());
        
    }

    public static int listSize(LinkedItem head) {
        int size = 0;
        head.value = 3;
        
        do {
        
        
        size++;
        
        
        head = head.getNext();
        
        
        } while(head != null);
        
        return size;
        }
}
