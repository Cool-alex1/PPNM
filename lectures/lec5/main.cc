#include<iostream>
#include<fstream>
#include<string>

int main(int argc, char* argv[]){  //char** argv er det samme som char* argv[] (char* er strings)
    std::string infile=" ", outfile=" ";
    for(int i=0; i<argc; ++i){
        std::string arg=argv[i];
        std::cout << "arg[" << i << "] = " << arg <<"\n";

        if(arg=="--input" && i+1<argc) infile = argv[i+1];
        if(arg=="--output" && i+1<argc) infile = argv[i+1];
    }

    std::cerr << "infile=" << infile << ", outfile=" << outfile << "\n";
    if(infile==" " || outfile==" ") return 0;

    std::ifstream instream(infile);
    std::ofstream outstream(outfile, std::ios::app);

    std::string word;
    while(instream >> word) outstream << word;

    instream.close();
    outstream.close();
}   