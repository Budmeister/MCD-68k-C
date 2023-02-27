#include <stdio.h>

// Tests: s-record.s19

char hexChars[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

int isNumber(unsigned char byte){
    return byte >= '0' && byte <= '9';
}

int isLetter(unsigned char byte){
    return byte >= 'A' && byte <= 'F';
}

int isHex(unsigned char byte){
    return isNumber(byte) || isLetter(byte);
}

unsigned char asciiNibbleToHex(unsigned char byte){
    if(isNumber(byte))
        return byte - '0';
    if(isLetter(byte))
        return byte - 'A' + 10;
    return 0;
}

unsigned char asciiToHex(unsigned char high, unsigned char low){
    unsigned char retval = (asciiNibbleToHex(high) << 4) | asciiNibbleToHex(low);
    return retval;
}

void printBits(unsigned char byte){
    printf("%d%d%d%d%d%d%d%d", 
        (byte >> 7) & 0x1,
        (byte >> 6) & 0x1,
        (byte >> 5) & 0x1,
        (byte >> 4) & 0x1,
        (byte >> 3) & 0x1,
        (byte >> 2) & 0x1,
        (byte >> 1) & 0x1,
        (byte >> 0) & 0x1
    );
}

#define NO_ACTION       0
#define GET_RECORD_TYPE 1
#define GET_BYTE_COUNT  2
#define GET_ADDRESS     3
#define GET_DATA        4

int main(){
    // S
    int lineNum = 0;
    int recordType;
    // Full Bytes
    unsigned char currentChar;          // The ascii character read from the console
    unsigned char currentHighNibble;    // The ascii character representing the high nibble to be converted to hex
    unsigned char currentLowNibble;     // The ascii character representing the low  nibble to be converted to hex
    unsigned char currentByte;          // The hex conversion 
    int highNibbleNext = 1;
    // Byte count
    int byteCount = 0;
    // Address
    int address = 0;
    int addressSize = 0;
    int addressInd = 0;
    int mask;
    // Checksum
    unsigned char checksum = 0;

    // Control
    int nextStep = NO_ACTION;

    int i;

    printf("Starting...\n");

    do{
        currentChar = fgetc(stdin);
        // printf("Received character: %d\n", currentChar);
        if(currentChar == 'S'){
            // printf("'S' Received\n");
            if(!highNibbleNext)
                printf("'S' received in the middle of another byte. Partial byte: %c\n", currentHighNibble);
            printf("\n-- Line %d --\n", lineNum++);
            checksum = 0;
            highNibbleNext = 1;
            nextStep = GET_RECORD_TYPE;
            // recordType = fgetc(stdin) - '0';
        }else if(isHex(currentChar)){
            // printf("Hex character received: %c\n", currentChar);
            if(nextStep == GET_RECORD_TYPE){
                recordType = asciiNibbleToHex(currentChar);
                printf("Record type: %d\n", recordType);
                if(recordType == 0 || recordType == 1 || recordType == 9)
                    addressSize = 2;
                else if(recordType == 2 || recordType == 8)
                    addressSize = 3;
                else if(recordType == 3 || recordType == 7)
                    addressSize = 4;
                else{
                    printf("Invalid record type. Resetting to 1.\n");
                    recordType = 1;
                    addressSize = 2;
                }
                addressInd = addressSize - 1;
                nextStep = GET_BYTE_COUNT;
            }else if(highNibbleNext){
                // printf("Loading high nibble\n");
                currentHighNibble = currentChar;
                highNibbleNext = 0;
            }else{
                // printf("Loading low nibble\n");
                currentLowNibble = currentChar;
                currentByte = asciiToHex(currentHighNibble, currentLowNibble);
                if(nextStep == GET_BYTE_COUNT){
                    byteCount = currentByte;
                    checksum += byteCount;
                    printf("Byte Count: %d\n", byteCount);
                    nextStep = GET_ADDRESS;
                }else if(nextStep == GET_ADDRESS){
                    mask = 0x000000ff << (addressInd * 8);
                    address = address & ~mask;
                    address = address | (((int) currentByte) << (addressInd * 8));
                    checksum+=currentByte;
                    addressInd--;
                    byteCount--;
                    if(addressInd == -1){
                        printf("Address: 0x");
                        for(i = addressSize - 1; i >= 0; i--)
                            printf("%c%c", hexChars[(address >> 8 * i + 4) & 0x0f], hexChars[(currentByte >> 8 * i) & 0x0f]);
                        printf("\n");
                        nextStep = GET_DATA;
                        printf("Data:\n");
                    }
                }else if(nextStep == GET_DATA){
                    if(--byteCount == 0){
                        // Do Checksum
                        // printf("%d %d %d\n", checksum, currentByte, (unsigned char) (checksum + currentByte + 1));
                        printf("Record checksum: 0x%c%c, ", hexChars[(currentByte >> 4) & 0x0f], hexChars[currentByte & 0x0f]);
                        if((unsigned char) (checksum + currentByte + 1) == 0)
                            printf("Valid!\n");
                        else
                            printf("Invalid - calculated: 0x%c%c\n", hexChars[((~checksum) >> 4) & 0x0f], hexChars[(~checksum) & 0x0f]);
                        printf("Finished reading data\n");
                        nextStep = NO_ACTION;
                    }else{
                        printBits(currentByte);
                        printf("  0x%c%c\n", hexChars[(currentByte >> 4) & 0x0f], hexChars[currentByte & 0x0f]);
                        checksum+=currentByte;
                    }
                }
                highNibbleNext = 1;
            }
        }
    }while(currentChar != 255);
    return 0;
}
