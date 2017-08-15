#ifndef __CONSOLE_H
#define __CONSOLE_H

void console_init();
void console_injectc(char ch);
void console_putc(char ch);

void console_log(char *str);
void console_warning(char *str);
void console_error(char *str);

#endif /* __CONSOLE_H */
