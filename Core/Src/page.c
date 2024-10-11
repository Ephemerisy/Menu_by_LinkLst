#include "page.h"
#include "stdio.h"

pageStructure *home_page = NULL;
pageStructure *page_now = NULL;

pageStructure *PAGE_CreatPage(char *const str, uint8_t num, pageStructure *p_last)
{
    pageStructure *p_page = (pageStructure *)malloc(sizeof(pageStructure));
    p_page->brunch_num = num;
    p_page->title = str;
    p_page->list = (pageStructure **)malloc(sizeof(pageStructure *) * num);
    p_page->last = p_last;
    p_page->text = NULL;
    p_page->image = NULL;
    return p_page;
}

void PAGE_WriteText(pageStructure *p_page, char *str)
{
    p_page->text = str;
}

void PAGE_WriteImage(pageStructure *p_page, const Image *img)
{
    p_page->image = img;
}

void PAGE_PrintPage(pageStructure *p_page)
{
    uint8_t i;
    static char temp[16];
    OLED_NewFrame();
    OLED_PrintString(0, 16 * 0, p_page->title, &font16x16, OLED_COLOR_NORMAL);
    for (i = 0; i < p_page->brunch_num - p_page->pointer_now; i++)
        OLED_PrintString(16, 16 * (i + 1), p_page->list[i + p_page->pointer_now]->title, &font16x16, OLED_COLOR_NORMAL);

    if (p_page->text != NULL)
        OLED_PrintString(0, 16 * i, p_page->text, &font16x16, OLED_COLOR_NORMAL);

    if (p_page->image != NULL)
        OLED_DrawImage((128 - (bilibiliImg.w)) / 2, 16, p_page->image, OLED_COLOR_NORMAL);

    if (p_page->image == NULL && p_page->text == NULL)
        OLED_PrintString(4, 16, ">", &font16x16, OLED_COLOR_NORMAL);

    if (p_page->brunch_num != 0)
    {
        OLED_DrawRectangle(127 - 16, 0, 16, 63, OLED_COLOR_NORMAL);
        OLED_DrawFilledRectangle(127 - 16, 0, 16, (uint8_t)((float)(p_page->pointer_now + 1) / (float)p_page->brunch_num * 63), OLED_COLOR_NORMAL);
    }
    OLED_ShowFrame();
}

void PAGE_ReadEncoder(pageStructure *p_page)
{
    p_page->pointer_now = __HAL_TIM_GET_COUNTER(&htim1) / 2;
    if (p_page->pointer_now >= p_page->brunch_num)
    {
        htim1.Instance->CNT = 0;
        p_page->pointer_now = 0;
    }
}
