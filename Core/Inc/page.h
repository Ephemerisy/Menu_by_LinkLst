#ifndef _PAGE_H_
#define _PAGE_H_

#include "oled.h"
#include "font.h"
#include "tim.h"
#include <stdlib.h>

typedef struct pageStructure
{
    uint16_t pointer_now;
    uint8_t brunch_num;
    char *title;
    char *text;
    const Image *image;
    struct pageStructure **list;
    struct pageStructure *last;
} pageStructure;

extern pageStructure *home_page;
extern pageStructure *page_now;

pageStructure *PAGE_CreatPage(char *const str, uint8_t num, pageStructure *p_last);
void PAGE_WriteText(pageStructure *p_page, char *str);
void PAGE_WriteImage(pageStructure *p_page, const Image *img);
void PAGE_PrintPage(pageStructure *p_page);
void PAGE_Rolling(pageStructure *p_page);
void PAGE_ReadEncoder(pageStructure *p_page);

#endif