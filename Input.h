#include "Decimal.h"
#include "LCD.h"

#define MAX_VALUE 1000000L

int count_digits(long a) {
    int br = 0;
    while (a != 0) {
        br++;
        a /= 10;
    }
    return br;
}

long pow10 (int pow) {
    long powed = 1;
    for (int i = 0; i < pow; i++) {
        powed *= 10;
    }
    Serial.print("Powed : ");
    Serial.println(powed);
    return powed;
}

int get_sign_indx(long cur) {
    return (MAX_DISP_WIDTH - (count_digits(cur) + 2)); // 2 -> '.' and ' '
}

void print_vals(long cur, int fp_indx, long fp_scale, int indx, long scale) {
    Serial.print("fp_indx: ");
    Serial.println(fp_indx);
    Serial.print("fp_scale: ");
    Serial.println(fp_scale);
    Serial.print("indx: ");
    Serial.println(indx);
    Serial.print("scale: ");
    Serial.println(scale);
    Serial.print("cur  : ");
    Serial.println(cur);
    Serial.print("COUNT DIGITS: ");
    Serial.println(count_digits(cur));
    Serial.print("sign_indx: ");
    Serial.println(get_sign_indx(cur));
    Serial.println();
}

// scale is the value with we incrament the current value (cur)
long get_scale(char buffer[], int indx) {
    long scale = 1;
    for (int i = MAX_DISP_WIDTH; i >= indx; i--) {
        if (buffer[i] != '.') {
            scale *= 10;
        }
    }
    scale /= 10;
    return scale;
}

void format_char_array(char (&buffer)[MAX_DISP_WIDTH + 1], long cur, int fp_indx, long fp_scale, char sign) {
    int cur_right_fp = cur % fp_scale;
    int cur_left_fp = cur / fp_scale;
    for (int i = MAX_DISP_WIDTH; i > fp_indx; i--) {
        buffer[i] = '0' + (char) (cur_right_fp % 10);
        cur_right_fp /= 10;
    }

    buffer[fp_indx] = '.';

    int size_buf2 = count_digits(cur_left_fp);
    for (int i = fp_indx - 1; i >= 0; i--) {
        if (fp_indx - i - 1 < size_buf2) {
            buffer[i] = '0' + (char) (cur_left_fp % 10);
            cur_left_fp /= 10;
        } else if (fp_indx - i - 2 == size_buf2) {
            buffer[i] = sign;
        } else if (i == 0) {
            buffer[i] = '>';
        } else {
            buffer[i] = 32; /// ASCII code of ' ' space
        }
    }
    Serial.print("formated: ");
    for (int i = 0; i < MAX_DISP_WIDTH + 1; i++) {
        Serial.print(buffer[i]);
    }
    Serial.println();
}

long input(long cur, int width, bool with_fp, long &fp_scale) {
    int indx;
    char buffer[MAX_DISP_WIDTH + 1];
    if (!with_fp) {
        indx = width - 1; // in the beggining we have ">" sign
    } else {
        indx = MAX_DISP_WIDTH - 1;
    }
    int fp_indx = MAX_DISP_WIDTH + 1 - count_digits(fp_scale);
    long int scale;
    scale = get_scale(buffer, indx);
    char sign;
    if (cur < 0) {
        sign = '-';
        cur = -cur;
    } else {
        sign = '+';
    }

    if (with_fp) {
        print_vals(cur, fp_indx, fp_scale, indx, scale);
        format_char_array(buffer, cur, fp_indx, fp_scale, sign);
    } else {
        sprintf(buffer, ">%10ld", cur);
    }
    lcd.setCursor(0, 1);
    lcd.print(buffer);
    while (true) {
        Button butt = read_LCD_buttons();
        if (butt == LEFT) {
            if (indx > 1) {
                indx--;
                print_vals(cur, fp_indx, fp_scale, indx, scale);
                lcd.noCursor();
            }
        } else if (butt == RIGHT) {
            if (indx < width) {
                indx++;
                print_vals(cur, fp_indx, fp_scale, indx, scale);
                lcd.noCursor();
            }
        } else if (butt == UP) {
            scale = get_scale(buffer, indx);
            if (with_fp && indx == fp_indx && fp_indx > 1) {
                fp_indx--;
                indx--;
                fp_scale *= 10;
                print_vals(cur, fp_indx, fp_scale, indx, scale);
            } else if (with_fp && indx == get_scale(buffer, cur)) {
                if (sign == '-') {
                    sign = '+';
                } else {
                    sign = '-';
                }
            } else if (scale + cur > 0 && cur + scale < MAX_VALUE) {
                cur += scale;
                print_vals(cur, fp_indx, fp_scale, indx, scale);
            }
            if (with_fp) {
                print_vals(cur, fp_indx, fp_scale, indx, scale);
                format_char_array(buffer, cur, fp_indx, fp_scale, sign);
            } else {
                sprintf(buffer, ">%10ld", cur);
            }
            lcd.setCursor(0, 1);
            lcd.print(buffer);
        } else if (butt == DOWN) {
            scale = get_scale(buffer, indx);
            if (with_fp && indx == fp_indx && fp_indx < 16) {
                fp_indx++;
                indx++;
                fp_scale /= 10;
                print_vals(cur, fp_indx, fp_scale, indx, scale);
            } else if (with_fp && indx == get_scale(buffer, cur)) {
                if (sign == '-') {
                    sign = '+';
                } else {
                    sign = '-';
                }
            } else if (cur > scale) {
                cur -= scale;
                print_vals(cur, fp_indx, fp_scale, indx, scale);
            }
            if (with_fp) {
                print_vals(cur, fp_indx, fp_scale, indx, scale);
                format_char_array(buffer, cur, fp_indx, fp_scale, sign);
            } else {
                sprintf(buffer, ">%10ld", cur);
            }
            lcd.setCursor(0, 1);
            lcd.print(buffer);
        } else if (butt == SELECT) {
            lcd.noCursor();
            if (with_fp && sign == '-') {
                return -cur;
            }
            return cur;
        }
        lcd.setCursor(indx, 1);
        lcd.cursor();
    }
}

int input_int(long cur) {
    long br;
    return input(cur, 5, false, br);
}

long input_long(long cur) {
    long br;
    return input(cur, 10, false, br);
}

Decimal input_decimal(Decimal dec) {
    Serial.print("DEC VALUEEE");
    Serial.println(dec.value);
    Serial.print("DEC SCALEEE");
    Serial.println(dec.scale);
    if (dec.value > MAX_VALUE || dec.value < -MAX_VALUE) {
        dec.value = 100;
    }
    if (dec.scale !=  (pow10(count_digits(dec.scale) - 1)) || dec.scale < 0) { // uninitialized EEPROM
        dec.scale = 1;
    }
    Serial.print("value after: ");
    Serial.println(dec.value);
    Serial.print("scale after:");
    Serial.println(dec.scale);
    dec.value = input(dec.value, MAX_DISP_WIDTH + 1, true, dec.scale);
    return dec;
}
