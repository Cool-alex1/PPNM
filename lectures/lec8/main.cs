
class main{
public class datum {public int start, stop; public double sum;};

public static void harm(datum& d){
    d.sum = 0;
    for(long i=d.start+1; i<=d.stop; i++) d.sum += 1.0/i;            //1.0 => double pecition, 1.0F single precition
}

public static int Main(string[] argv){
    int argc = argv.Length;
    long nthreads=1, nterms=(int)1e8;
    for(int i=0; i<argc; i++){
        string arg = argv[i];
        if(arg=="-treads" && i+1<argc) nthreads=int.Parse(argv[i+1]);
        if(arg=="-terms" && i+1<argc) nterms=(int)double.Parse(argv[i+1]);
    }
    Error.WriteLine($"nthreads={nthreads}, nterms={nterms}");
    var treads = new System.Threading.Tread[nthreads];
    var data = new datum[nthreads];

    for(int i=0; i<nthreads; i++){
        data[i].start = i*nterms/nthreads;
        data[i].stop = (i+1)*nterms/nthreads;
    }
    
    for(int i=0; i<nthreads; i++){
        threads[i]= new tread(harm);
        threads[i].Start(data[i]);
    }
    for(int i=0; i<nthreads; i++) threads[i].join();
    double sum=0;
    for(datum d : data) sum += d.sum;

    std::cout << "sum=" << sum << std::endl;

    return 0;
}
}