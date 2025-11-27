#ifndef LCD_H
#define LCD_H

void lcd_init();
void lcd_clear();
void lcd_set_cursor(int col, int row);
void lcd_print(const char *s);

#endif
