#pragma once
#include <stdint.h>
#include <stdbool.h>
#define M_PI 3.14159265358979323846
int ft_isinf(double x){
	if (x == (-1.0 / 0.0))
		return ((!ft_isnan(x) && ft_isnan(x - x)) * -1);
	return (!ft_isnan(x) && ft_isnan(x - x));
}
int ft_isnan(double x){
	return (x != x);
}
double ft_fabs(double x){
	if (ft_isnan(x))
		return (-(0.0 / 0.0));
	if (x < 0.0)
		return (x * -1.0);
	return (x);
}
double ft_fmod(register double x, register double y){
	if (ft_isinf(x))
		return (-0.0 / 0.0);
	if (ft_isinf(y))
		return (x);
	return ((x) - ((long)(x / y)) * (y));
}
double ft_cos(double x){
	double result,term;
	uint32_t epsilon;
	if (ft_isinf(x))
		return (0.0 / 0.0);
	result = 1.0;
	term = 1.0;
	epsilon = 0;
	x = ft_fmod(x, 2.0 * M_PI);
	while (++epsilon, ft_fabs(term) > 1E-15){
		term = -term * x * x / (2.0 * epsilon - 1.0) / (2.0 * epsilon);
		result += term;
	}
	return (result);
}
double ft_sin(double x){
	double result, term;
	uint32_t epsilon;
	if (ft_isinf(x))
		return (0.0 / 0.0);
	x = ft_fmod(x, 2.0 * M_PI);
	epsilon = 3;
	term = x;
	result = x;
	while (ft_fabs(term) > 1E-15){
		term = -term * x * x / (epsilon * (epsilon - 1.0));
		result += term;
		epsilon += 2;
	}
	return (result);
}
double ft_tan(double x){
	return (ft_sin(x) / ft_cos(x));
}
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
int intToStr(int num, char str[]) {
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

        //if (precision > 0 && precision == i) {
        //    str[i++] = '.';
        //}
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
//Compare two strings
int strcmp(const char *str1, const char *str2) {
    while (*str1 != '\0' && *str2 != '\0') {
        if (*str1 != *str2) {
            return (*str1 > *str2) ? 1 : -1;
        }
        str1++;
        str2++;
    }

    if (*str1 == '\0' && *str2 == '\0') {
        return 0; // Strings are equal
    } else if (*str1 == '\0') {
        return -1; // str1 is shorter than str2
    } else {
        return 1; // str2 is shorter than str1
    }
}
int compareStrings(char a[], char b[]) {
    int i = 0;
    
    while (a[i] == b[i]) {
        if (a[i] == '\0')
            return 0; // Strings are equal
        i++;
    }
    
    return a[i] - b[i];
}
char intToHexDigit(uint8_t digit) {
    if (digit < 10) {
        return '0' + digit;
    } else {
        return 'A' + (digit - 10);
    }
}

// Function to reverse a string in place
void reverseString(char* str, uint8_t length) {
    uint8_t start = 0;
    uint8_t end = length - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

// Function to convert an integer to a hexadecimal string
void intToHexString(int32_t num, char* hexString) {
    bool isNegative = false;
    uint32_t unsignedNum;

    // Handle negative numbers
    if (num < 0) {
        isNegative = true;
        unsignedNum = (uint32_t)(-num);
    } else {
        unsignedNum = (uint32_t)num;
    }

    // Special case for zero
    if (unsignedNum == 0) {
        hexString[0] = '0';
        hexString[1] = '0';
        hexString[2] = '\0';
        return;
    }

    uint8_t index = 0;
    while (unsignedNum > 0) {
        uint8_t remainder = unsignedNum % 16;
        hexString[index++] = intToHexDigit(remainder);
        unsignedNum /= 16;
    }

    // Add the negative sign for negative numbers
    if (isNegative) {
        hexString[index++] = '-';
    }

    // Fill with '0' digits until we have at least two digits
    while (index < 2) {
        hexString[index++] = '0';
    }

    hexString[index] = '\0';

    // Reverse the string to get the correct hexadecimal representation
    reverseString(hexString, index);
}
