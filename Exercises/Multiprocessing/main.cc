#include<iostream>
#include<thread>
#include<string>
#include<vector>


// struct data { public int a,b; public double sum;}

// void harm(object obj){
// 	var arg = (data)obj;
// 	arg.sum=0;
// 	for(int i=arg.a;i<arg.b;i++)arg.sum+=1.0/i;
// }

// int main(){
//     int nthreads = 1, nterms = (int)1e8; /* default values */
//     for(int i=0; i<argc; i++){
//         std::string arg =argv[i];
//         if(arg=="-treads" && i+1<argc) nthreads=std::stoi(argv[i+1]);
//         if(arg=="-terms" && i+1<argc) nterms=(int)std::stoi(argv[i+1]);
//     }

//        data[] params = new data[nthreads];
//     for(int i=0; i<nthreads; i++) {
//         params[i] = new data();
//         params[i].a = 1 + nterms/nthreads*i;
//         params[i].b = 1 + nterms/nthreads*(i+1);
//     }
//     params[params.Length-1].b=nterms+1; /* the enpoint might need adjustment */

//     var threads = new System.Threading.Thread[nthreads];
//     for(int i=0;i<nthreads;i++) {
//         threads[i] = new System.Threading.Thread(harm); /* create a thread */
//         threads[i].Start(params[i]); /* run it with params[i] as argument to "harm" */
//     }

//    foreach(var thread in threads) thread.Join();

//    double total=0; foreach(var p in params) total+=p.sum;

// }


struct datum {int start, stop; double sum;};

void harm(datum& d){
    d.sum = 0;
    for(long i=d.start+1; i<=d.stop; i++) d.sum += 1.0/i;            //1.0 => double pecition, 1.0F single precition
}

int main(int argc, char** argv){
    long nthreads=1, nterms=(long)1e9;
    for(int i=0; i<argc; i++){
        std::string arg =argv[i];
        if(arg=="-threads" && i+1<argc) nthreads=std::stoi(argv[i+1]);
        if(arg=="-terms" && i+1<argc) nterms=(long)std::stod(argv[i+1]);
    }
    std::cerr << "nthreads=" << nthreads << ", nterms=" << nterms << "\n";
    std::vector<std::thread> threads(nthreads);
    std::vector<datum> data(nthreads);

    for(int i=0; i<nthreads; i++){
        data[i].start = i*nterms/nthreads;
        data[i].stop = (i+1)*nterms/nthreads;
    }
    
    for(int i=0; i<nthreads; i++){
        threads[i]=std::thread(harm, std::ref(data[i]));
    }
    for(int i=0; i<nthreads; i++) threads[i].join();
    double sum=0;
    for(datum d : data) sum += d.sum;

    std::cout << "sum=" << sum << std::endl;


    return 0;
}