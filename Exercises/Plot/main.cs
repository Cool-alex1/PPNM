class main{

public static int Main(){
    for(double x=-3; x<3; x+=1.0/8){
        System.Console.WriteLine($"{x} {sfuns.erf(x)}");
    }
    System.Console.WriteLine();
    System.Console.WriteLine();


    double dx = 1.0/16;
    for(double x=-5+dx/2; x<5.2; x+=1.0/8){
        System.Console.WriteLine($"{x} {sfuns.sgamma(x+1)}");
    }
    System.Console.WriteLine();
    System.Console.WriteLine();


    System.Console.WriteLine($"{0} {1}");
    System.Console.WriteLine($"{1} {1}");
    System.Console.WriteLine($"{2} {2}");
    System.Console.WriteLine($"{3} {6}");
    System.Console.WriteLine($"{4} {24}");
    System.Console.WriteLine();
    System.Console.WriteLine();


    for(double x=-0.1; x<5.2; x+=1.0/8){
        System.Console.WriteLine($"{x} {sfuns.aprFac(x)}");
    }
    System.Console.WriteLine();
    System.Console.WriteLine();


    for(double x=0.1; x<10; x+=1.0/8){
        System.Console.WriteLine($"{x} {sfuns.lngamma(x)}");
    }
    System.Console.WriteLine();
    System.Console.WriteLine();


    return 0;
}


}