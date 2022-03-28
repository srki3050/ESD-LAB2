#include <at89c51ed2.h>       //also includes 8052.h and 8051.h
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#define CRYSTAL_FREQUENCY 48
#define DELAY_TIME ((CRYSTAL_FREQUENCY /60) * 500)
#define SCK P1_1
#define SDA P1_2
bool hexflag = false;
// Prototipe declaration
void weeprom (char page, char address, char datum);
char reeprom (char page, char address);
char read (char readcmd);
void outs (char datum);
void out (char datum);
char in (void);
void stop (void);

void delay(void){
    int i = 0;
    while(i++ < DELAY_TIME);
}
_sdcc_external_startup()
{
    AUXR |= 0x0C;
    return 0;
}
/* -------------------------------------------------- */
//          putchar function
/* -------------------------------------------------- */
int putchar (int c)
{
    // Note: Compare the asm generated for the next three lines
    //       They all accomplish the same thing, but is the asm the same?
    while (!TI);
    SBUF = c;           // load serial port with transmit value
    TI = 0;             // clear TI flag

    return c;
}

// getchar gets a char from RX. Blocking. Returns char.
int getchar (void)
{
    // Note: Compare the asm generated for the next three lines
    //       They all accomplish the same thing, but is the asm the same?
    while (!RI);
    RI = 0;                         // clear RI flag
    return SBUF;                    // return character from SBUF
}
uint8_t getinput()
{
    int number;
    uint8_t e,f;
    int a = getchar();
    if(a >= 'A' && a <= 'F')
        e = a - '7';
    else
        e = a - '0';
    putchar(a);
    int b = getchar();
    if(b >= 'A' && b <= 'F')
        f =  b- '7';
    else
        f = b - '0';
    putchar(b);
    number = (e*16) + f;
    if(number >= 0xFF)
        getinput();
    return number;
}
//**********************************************************************
//* Function Name: void stop (void)
//**********************************************************************
//* Function Description: send stop condition
//**********************************************************************
//* Input parameters: NONE
//**********************************************************************
//* Output parameters: NONE
//**********************************************************************
/// Notes: NONE
//**********************************************************************
void stop (void)
{
SDA = 0; // stop condition, data = 0
    delay();
SCK = 1; // clock = 1
    delay();
SDA = 1; // data = 1
}
//**********************************************************************
//* Function Name: char in (void)
//**********************************************************************
//* Function Description: receives a byte from memory
//**********************************************************************
//* Input parameters: NONE
//**********************************************************************
//* Output parameters:
//* - char with the byte received from memory
//**********************************************************************
/// Notes: NONE
//**********************************************************************
char in (void)
{
char i; // index
char aux = 0; // auxiliary storage
SDA = 1; // insure port pin = 1 for input
for (i = 0; i < 8; i++) // bit shifting cycle
{
SCK = 0; // clock = 0
        delay();
SCK = 1; // clock = 1
aux = aux << 1; // load bit position
if (SDA) // check SDA data from port pin
aux = aux | 0x01; // if port pin = 1, set LSB (bit position)
else
aux = aux & 0xFE; // else port pin = ,clear LSB (bit position)
}
SCK = 0; // clock = 0
return (aux); // return data received
}
//**********************************************************************
//* Function Name: void outs (char datum)
//**********************************************************************
//* Function Description: sends to memory the input parameter with a
//*                       start condition
//**********************************************************************
//* Input parameters:
//* - char datum: data byte to send to the memory
//**********************************************************************
//* Output parameters: NONE
//**********************************************************************
/// Notes: NONE
//**********************************************************************
void outs (char datum)
{
char i; // index
char aux; // auxiliary storage
SDA = 1; // set port pin SDA to insure data is HI
SCK = 1; // set port pin SCK to insure clock is HI
if(!hexflag)
        delay();
SDA = 0; // start condition, data = 0
    if(!hexflag)
        delay();
SCK = 0; // clock = 0
for (i = 0; i < 8; i++) // bit shifting cycle
{
aux = datum & 0x80; // check MSB bit
if (aux == 0) // MSB = 0
SDA = 0; // then SDA = 0
else
SDA = 1; // else MSB =1, then SDA = 1
SCK = 1; // clock = 1
    if(!hexflag)
        delay();
SCK = 0; // clock = 0
datum = datum << 1; // rotate for next bit
}
SDA = 1; // set port pin for ack
    if(!hexflag)
        delay();
SCK = 1; // clock ack
    if(!hexflag)
        delay();
SCK = 0; // clock = 0
}
//**********************************************************************
//* Function Name: void out (char datum)
//**********************************************************************
//* Function Description: sends to memory the input parameter without a
//*                       start condition
//**********************************************************************
//* Input parameters:
//* - char datum: data byte to send to the memory
//**********************************************************************
//* Output parameters: NONE
//**********************************************************************
/// Notes: NONE
//**********************************************************************
void out (char datum)
{
char i; // index
char aux; // auxiliary storage
for (i = 0; i < 8; i++) // bit shifting cycle
{
aux = datum & 0x80; // check MSB bit
if (aux == 0) // MSB = 0
SDA = 0; // then SDA = 0
else
SDA = 1; // else MSB = 1, the SDA = 1
SCK = 1; // clock = 1
        if(!hexflag)
            delay();
SCK = 0; // clock = 0
datum = datum << 1; // rotate for next bit
}
SDA = 1; // set port pin for ack
    if(!hexflag)
        delay();
SCK = 1; // clock ack
    if(!hexflag)
        delay();
SCK = 0; // clock = 0
}
//**********************************************************************
//* Function Name: void weeprom (char page, char address, char datum)
//**********************************************************************
//* Function Description: write routine for I2C EEPROM
//**********************************************************************
//* Input parameters:
//* - char page: number of 256 bytes block to use
//* - char address: position inside the 256 bytes block
//* - char datum: 1 byte data to write
//**********************************************************************
//* Output parameters: NONE
//**********************************************************************
/// Notes: NONE
//**********************************************************************
void weeprom (char page, char address, char datum)
{
char WRCMD; // auxiliary storage to build the write command
page = page << 1; // move A0, A1 & A2 to their positions
page = page & 0xFE; // clear r/w bit
WRCMD = page | 0xA0; // build the write command
outs (WRCMD); // send the write command with start condition
out (address); // send address
out (datum); // send data
stop (); // send stop condition
}
//**********************************************************************
//* Function Name: char read (char readcmd)
//**********************************************************************
//* Function Description: reads 1 byte from current memory position
//**********************************************************************
//* Input parameters:
//* - char readcmd: read command byte with A0, A1 & A2 embedded
//**********************************************************************
//* Output parameters:
//* - char with current address data
//**********************************************************************
/// Notes: NONE
//**********************************************************************
char read (char readcmd)
{
char RDCMD; // auxiliary storage to build the read command
char aux; // auxiliary storage
RDCMD = readcmd | 0x01; // set r/w bit
outs (RDCMD); // send read command with start condition
aux = in(); // read current position
stop (); // send stop condition
return (aux); // return current position data
}
//**********************************************************************
//* Function Name: char reeprom (char page, char address)
//**********************************************************************
//* Function Description: read routine for I2C EEPROM
//**********************************************************************
//* Input parameters:
//* - char page: number of 256 bytes block to use
//* - char address: position inside the 256 bytes block
//**********************************************************************
//* Output parameters:
//* - char with the data from memory
//**********************************************************************
/// Notes: NONE
//**********************************************************************
char reeprom (char page, char address)
{
char aux; // auxiliary storage
char WRCMD; // aux. storage for the write command (to send the add.)
aux = page; // preparing the write command
aux = aux << 1; // move A0, A1 & A2 to their positions
aux = aux & 0xFE; // clear r/w bit
WRCMD = aux | 0xA0; // build the write command
outs (WRCMD); // send the write command with start condition
out (address); // send address
aux = read (WRCMD); // send read command and receive data
return (aux); // return solicited data
}
void eereset(void){
    uint16_t datum = 0xFF8;
char i; // index
uint16_t aux; // auxiliary storage
SDA = 1; // set port pin SDA to insure data is HI
SCK = 1; // set port pin SCK to insure clock is HI
delay();
SDA = 0; // start condition, data = 0
delay();

SCK = 0; // clock = 0
for (i = 0; i <= 8; i++) // bit shifting cycle
{
aux = datum & 0x800; // check MSB bit
if (aux == 0) // MSB = 0
SDA = 0; // then SDA = 0
else
SDA = 1; // else MSB =1, then SDA = 1
            SCK = 1; // clock = 1
            delay();
            SCK = 0; // clock = 0
            datum = datum << 1; // rotate for next bit
}
SDA = 1; // set port pin for ack
delay();
SCK = 1; // clock ack
delay();
SDA = 0; // set port pin for ack
delay();
SCK = 0; // clock = 0

stop();
}
void main()
{
    while(1){
        printf_small("\r\n ENTER THE CHARACTER TO SELECT MODE");
        char input = getchar();
        switch(input){
            case 'W': printf_small("\r\nEnter the character to be written\n");
                      uint8_t data = getinput();
                      printf_small("\r\n%x",data);
                      printf_small("\r\nEnter the Address to be written\n");
                      uint8_t address = getinput();
                      printf_small("\r\n%x",address);
                      weeprom(0x00,address,data);
                      break;
            case 'R': printf_small("\r\nEnter the address to be Read\n");
                      uint8_t readcmd = getinput();
                      printf_small("\r\n Data on that address is %x",reeprom(0x00,readcmd));
                      break;
            case 'H': printf_small("\r\nPrint the Hexdump");
                      for(int i = 0;i < 256;i++){
                        if((i % 16) == 0){
                            if(i == 0){
                                printf_small("\r\n");
                                printf("%x: ",i);
                            }
                            else{
                                printf_small("\r\n");
                                printf("%x:",i);
                            }
                        }
                        hexflag = true;
                        printf("%x ",reeprom(0x00,i));
                        hexflag = false;
                       }
                       break;
            case 'S':  printf_small("\r\nSytem Reset");
                       eereset();
                       break;
        }
        putchar(input);
    }
}
