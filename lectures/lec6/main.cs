using static System.Console;
using complex=System.Numerics.Complex;
class main{
    static void echo<T>(T arg){
        WriteLine($"echo: {arg}");
    }
    // static void addition<T>(T x, T y){
    //     WriteLine($"echo: {x+y}");
    // }
    static void fun_of_one(System.Func<double, double> f){ WriteLine($"f(2)={f(2)}");}
    static int Main(){
        System.Func<double, double> f = delegate(double x){return x*x;};
        f = x => x*x;
        f = System.Math.Sin;
        WriteLine($"f: {f(3)}");

        fun_of_one(f);
        fun_of_one(x => x*x);


        echo("string");
        echo(1);
        echo(1.3);
        complex I = complex.Sqrt(-1);
        echo(complex.Sqrt(-1));
        echo(complex.Pow(I,I));
        echo(complex.Sin(I));

        string s="original string";
        System.Action prints = delegate(){WriteLine($"prints: s={s}");};
        prints();
        s="new string";
        prints();

        return 0;
    }
}