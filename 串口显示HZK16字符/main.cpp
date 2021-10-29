/*
这个是中文点阵HZK16字库的使用方法
将HZK16文件通过bin2c.exe软件转换为C文件
再讲此文件包含进头文件，注意要加PROGMEM关键字

主要使用memcpy_P函数将Flash中的字库文件加载进buffer


*/

#include <Arduino.h>
#include "hzk16s.c"

int i, j, k, flag;
char buffer[32];

int txt_index = 1;
uint8_t myword[] = { //升达经贸管理学院 ---GB2312码
    0xC9, 0xFD, 0xB4, 0xEF, 0xBE, 0xAD, 0xC3, 0xB3, 0xB9, 0xDC, 0xC0, 0xED, 0xD1, 0xA7, 0xD4, 0xBA, 0x00};

unsigned char key[8] = {
    0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};

void setup()
{
    Serial.begin(115200);

    for (txt_index = 0; txt_index < 8; txt_index++)
    {
        unsigned long offset = (94 * (unsigned int)(myword[txt_index * 2] - 0xa0 - 1) + (myword[txt_index * 2 + 1] - 0xa0 - 1)) * 32;
        memcpy_P(&buffer, &achzk16s[offset], 32);
        for (k = 0; k < 16; k++)
        {
            for (j = 0; j < 2; j++)
            {
                for (i = 0; i < 8; i++)
                {
                    flag = buffer[k * 2 + j] & key[i];
                    Serial.printf("%s", flag ? "■" : "□");
                }
            }
            Serial.printf("\n");
        }
        delay(1000);
    }
}

void loop()
{
}
