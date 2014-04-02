#include <fstream>
#include "HCTree.hpp"
#include <stdio.h>

int main(int argc, char* argv[])
{

  if(argc != 3)
  {
    cerr<< "Incorrect usage"<<endl;
    cout<<"Format: ./compress infile outfile"<<endl;
    return 1;
  }

  vector<unsigned int> freqs(256);
  ifstream in;
  byte symbol;
  int numelements=0;
  
  in.open(argv[1],ios::binary);

  if(in.eof()||(!in.good()))
  {
    cout<<"File is empty. Program will exit."<<endl;
    return -1;
  }

  // get all the symbols and put counts in freqs vector
  while(1)
  {
    symbol=in.get();
    
    if((!in.good()) || in.eof())
    {
      break;                            
    }
    freqs[symbol]++; 
    numelements++;
  }

  in.close();
  
  //Build tree
  HCTree tree;
  if(numelements>0)
  {
    tree.build(freqs);
  }  

  ofstream out;
  out.open(argv[2],ios::binary);

  //Create header to rebuild tree in uncompress
  for(int i=0; i<freqs.size();i++)
  {
    out << " " << freqs.at(i);
  }
  
  out.flush();

  BitOutputStream bitout = BitOutputStream(out);
  in.open(argv[1],ios::binary);
  
  //Encode sumbols 
  while(in.good())
  {
    tree.encode((char)in.get(), bitout);
  }
  
  bitout.flush();
  
  in.close();
  out.close();
}
