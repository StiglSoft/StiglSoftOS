
void reverse(char str[], int length) {
    int start = 0;
    int end = length - 1;

    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;

        start++;
        end--;
    }
}


char Upper(char src){
    return (char)((int)src - 32);
}

int atoi(const char *str){
    int result = 0, i = 0;

    if(*str == '-') // skip sign
        i++;

    for(; str[i]; i++) // do the conversion
        result = result * 10 + str[i] - '0';

    if(*str == '-') // make the number negative
        result /= -1;

    return result;
}
int abs(int src){
    if(src < 0)
        return -src;
    return src;
}
int intToStr(int num, char str[], int precision) {
    int i = 0;
    int isNegative = 0;
    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return i;
    }

    if (num < 0) {
        isNegative = 1;
        num = -num;
    }

    while (num != 0) {
        int rem = num % 10;
        str[i++] = rem + '0';
        num = num / 10;

        if (precision > 0 && precision == i) {
            str[i++] = '.';
        }
    }
    
    if (isNegative)
        str[i++] = '-';
    //str[i++] = '\n';
    str[i] = '\0';
    reverse(str, i);

    return i;
}
char* strcat(char* destination, const char* source) {
    // Find the end of the destination string
    char* ptr = destination;
    while (*ptr != '\0') {
        ptr++;
    }

    // Copy characters from the source to the destination
    while (*source != '\0') {
        *ptr = *source;
        ptr++;
        source++;
    }

    // Terminate the destination string
    *ptr = '\0';

    return destination;
}

// Function to copy a string
char* strcpy(char* destination, const char* source) {
    // Copy characters from the source to the destination
    while (*source != '\0') {
        *destination = *source;
        destination++;
        source++;
    }

    // Terminate the destination string
    *destination = '\0';

    return destination;
}