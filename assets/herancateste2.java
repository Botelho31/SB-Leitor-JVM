class ordem2{
    static { 
        System.out.println("5"); 
    }
    { 
        System.out.println("6"); 
    }
    ordem2() {
        System.out.println("7");
    } 
}

class ordem1 extends ordem2{
    static { 
        System.out.println("1"); 
    }
    { 
        System.out.println("2"); 
    }
    public ordem1() {
        System.out.println("3"); 
    }
    public static void main(String[] args) {
        System.out.println("4");
        ordem1 f = new ordem1();
    } 
}
