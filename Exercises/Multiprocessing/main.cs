using static System.Console;
class main{

public class datum {public int start,stop; public double sum;};

public static void harm(object obj){
	datum d = (datum)obj;
	d.sum=0;
	for(int i=d.start+1;i<=d.stop;i++)d.sum+=1.0/i;
	}

public static int Main(string[] argv){
	int argc=argv.Length;
	int nthreads=1,nterms=(int)1e8;
	for(int i=0;i<argc;i++){
		string arg = argv[i];
		if(arg=="-threads" && i+1<argc) nthreads=int.Parse(argv[i+1]);
		if(arg=="-terms" && i+1<argc) nterms=(int)double.Parse(argv[i+1]);
		}
	Error.WriteLine($"nthreads={nthreads} nterms={nterms}");
	var threads = new System.Threading.Thread[nthreads];
	var data = new datum[nthreads];
	for(int i=0;i<nthreads;i++){
		data[i] = new datum();
		data[i].start = i*nterms/nthreads;
		data[i].stop = (i+1)*nterms/nthreads;
		}
	for(int i=0;i<nthreads;i++){
		threads[i]=new System.Threading.Thread(harm);
		threads[i].Start(data[i]);
		}
	foreach(var thread in threads) thread.Join();
	double sum=0;
	foreach(var d in data) sum+=d.sum;
	WriteLine($"sum={sum}");
return 0;
}//Main

}//class main