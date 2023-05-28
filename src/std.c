#define SHIFT_KEY 41
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
char keyboardLine0[] = 
"!1234567890-=<\tqwertyuiop[]\n_asdfghjkl;'NN\\zxcvbnm,./    ";

char Upper(char src){
    return (char)((int)src - 32);
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
    str[i++] = '\n';
    str[i] = '\0';
    reverse(str, i);

    return i;
}