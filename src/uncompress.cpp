#include <fstream>
#include "HCTree.hpp"

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
  int num;
  int numelements=0;

  in.open(argv[1],ios::binary);

  if(in.eof())
  {
    cout<<"File is empty. Program will exit."<<endl;
    return -1;
  }

  //Get freqs vector to Rebuild tree
  for(int i=0; i<freqs.size();i++)
  {
    in >> num;
    freqs[i]=num;
    numelements+=num;
  }

  HCTree tree;
  if(numelements != 0)
  {
    tree.build(freqs);
  }

  BitInputStream bitin = BitInputStream(in);
 
  ofstream out;
  out.open(argv[2],ios::binary);

  //Decode all symbols
  if(numelements != 0)
  {
    for(int i=0;i<numelements;i++)
    {
      out << tree.decode(bitin);
    }
  }
  in.close();
  out.close();
}
