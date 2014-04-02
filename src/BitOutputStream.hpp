#ifndef BITOUTPUTSTREAM_HPP
#define BITOUTPUTSTREAM_HPP
#include <iostream>


class BitOutputStream
{
  private:

  char buffer; //Buffer to hold byte value

  int numbits; // number of bits written

  public:

    std::ostream & out;

   BitOutputStream(std:: ostream & os) : out(os)
  {
    buffer = numbits = 0;
  }

  /** Flush  method will flush the buffer when buffer has been fully written
   */
   void flush();

  /** Writes next bit to the buffer and will call flush when we 
   *  reach the end of the buffer
   */
   void bitwrite(int i);

};

#endif // BITOUTPUTSTREAM_HPP
