#ifndef BITINPUTSTREAM_HPP
#define BITINPUTSTREAM_HPP
#include <iostream>

class BitInputStream
{
  private:

  char buffer; // Buffer to hold byte value

  int numbits; // number of bits read

  public:

  std::istream & in;

   BitInputStream(std:: istream & is) : in(is)
  {
    buffer = 0;
    numbits = 8;
  }
  /** Fill method will fill the buffer when buffer has been read
   */
  void fill();

  /** Reads next bit in the buffer and will call fill when we 
   *  reach the end of the buffer
   */
  int bitread();

};

#endif // BITINPUTSTREAM_HPP
