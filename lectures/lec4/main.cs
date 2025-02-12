using static System.Console;
class main{
    static int Main(){
        double x=0;
        double y=x;
        x=9;
        int n=3;
        double[] a = new double[n];
        for(int i=0; i<a.Length; ++i) a[i]=i+1;
        double[] b=a;
        b[0]=666;
        WriteLine($"a[0]={a[0]}");
        WriteLine($"y={y}");
        foreach(double ai in a) WriteLine(ai);
        vec v = new vec();     //default {0,0,0}
        //v.x=0; v.y=0; v.z=0;
        WriteLine($"{v.x}, {v.y}, {v.z}");
        v.x=1; v.y=1; v.z=1;
        WriteLine($"{v.x}, {v.y}, {v.z}");
        return 0;
    }
}