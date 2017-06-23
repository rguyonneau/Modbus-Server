#include <MemoryTest.h>
#include <ModbusServer.h>

#include <stdio.h>

#define SIZE 256

int main(){

  MemoryTest myMem;
  ModbusServer myServer(&myMem);

  unsigned int len = SIZE;
  //the request array will be used to set the modbus request
  // and to store the response as well
  unsigned char request[SIZE];

  //------- first we try to read 2 words

  request[0] = 0x04; // read input registers function
  request[1] = 0x00; // starting address
  request[2] = 0x00; //        "
  request[3] = 0x00; // quantity of registers
  request[4] = 0x02; //        "

  //processing the modbus request
  len = myServer.processPDU(request, SIZE);

  //we display the modbus response
  printf("1 - response (%d):", len);
  for(unsigned int i=0; i< len; i++){
      printf(" %x ", request[i]);
  }
  printf("\n");

  //------- it should be displayed:
  //   > 1 - response (6): 4 4 0 0 0 0

  //------- then we try to write 2 words
  
  request[0] = 0x10; // write multiple registers
  request[1] = 0x00; // starting address
  request[2] = 0x00; //        "
  request[3] = 0x00; // quantity of registers
  request[4] = 0x02; //        (N)
  request[5] = 0x04; // byte count (2*N)
  request[6] = 0xAB; // value of the first register
  request[7] = 0xCD; //         "
  request[8] = 0x12; // value of the second register
  request[9] = 0x34; //         "

  len = myServer.processPDU(request, SIZE);

  printf("2 - response (%d):", len);
  for(unsigned int i=0; i< len; i++){
      printf(" %x ", request[i]);
  }
  printf("\n");

  //------- it should be displayed:
  //   > 2 - response (5): 10 0 0 0 2
  
  //------- and finally we read again

  request[0] = 0x04; // read input registers function
  request[1] = 0x00; // starting address
  request[2] = 0x00; //        "
  request[3] = 0x00; // quantity of registers
  request[4] = 0x02; //        "

  len = myServer.processPDU(request, SIZE);

  printf("3 - response (%d):", len);
  for(unsigned int i=0; i< len; i++){
      printf(" %x ", request[i]);
  }
  printf("\n");

  //------- it should be displayed:
  //   > 3 - response (6): 4 4 ab cd 12 34

  return 0;
}
