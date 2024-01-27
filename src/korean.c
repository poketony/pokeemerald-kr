#include "global.h"
#include "text.h"
#include "korean.h"
#include "korean_table.h"

static const u8 sSingleByteJongTable[] = 
{
    CHAR_0,
    CHAR_1,
    CHAR_3,
    CHAR_6,
    CHAR_7,
    CHAR_8,
};

bool8 IsKoreanGlyph(u16 glyph)
{
    return glyph >= 0x37 && glyph <= 0x41;
}

bool8 IsJaum(u8 glyph)
{
    return glyph >= 0x01 && glyph <= 0x13;
}

bool8 IsMoum(u8 glyph)
{
    return !IsJaum(glyph);
}

bool8 HasJong(u16 ch)
{
    u8 i, singleByteChar;

    if (IsKoreanGlyph((ch & 0xff00) >> 8))
    {
        return gConvertKoreanToUnicodeTable[ch - 0x3700] % 28;
    }
    else
    {
        singleByteChar = (u8)ch & 0x00ff;
        for (i = 0; i < sizeof(sSingleByteJongTable); i++)
        {
            if (singleByteChar == sSingleByteJongTable[i])
                return TRUE;
        }
        return FALSE;
    }
}

u8 GetCho(u8 index)
{
    return index - 1;
}

u8 GetJung(u8 index)
{
    return index - 0x14;
}

u8 GetJong(u8 index)
{
    u8 i = 0;
    s8 ch;

    while ((ch = gConvertJongToChoTable[i]) != -1)
    {
        if (ch == index)
            return i;
        i++;
    }

    return -1;
}

u8 DecomposeToCho(u16 korean)
{
    u16 code = gConvertKoreanToUnicodeTable[korean - 0x3700];
    return ((code / 28) / 21) + 0x01;
}

u8 DecomposeToJung(u16 korean)
{
    u16 code = gConvertKoreanToUnicodeTable[korean - 0x3700];
    return ((code / 28) % 21) + 0x14;
}

u8 DecomposeToJong(u16 korean)
{
    return gConvertJongToChoTable[gConvertKoreanToUnicodeTable[korean - 0x3700] % 28];
}

u8 DecomposeToJongIndex(u16 korean)
{
    return gConvertKoreanToUnicodeTable[korean - 0x3700] % 28;
}

u8 ConvertJongToCho(u8 jong)
{
    return gConvertJongToChoTable[jong];
}

u16 ConvertKoreanToUnicode(u16 korean)
{
    return gConvertKoreanToUnicodeTable[korean - 0x3700];
}

u16 ConvertUnicodeToKorean(u16 code)
{
    return gConvertUnicodeToKoreanTable[code];
}

u16 ComposeKorean(u8 cho, u8 jung, u8 jong)
{    
    return ConvertUnicodeToKorean(ComposeKoreanToUnicode(cho, jung, jong));
}

u16 ComposeKoreanToUnicode(u8 cho, u8 jung, u8 jong)
{    
    return (((cho * 21) + jung) * 28) + jong;
}

u8 ComposeJaum(u8 ch, u8 ch2)
{
    switch (ch)
    {
    // ㄱ
    case 0x01:
        // ㅅ
        if (ch2 == 0x0a)
            return 3;
        break;
    // ㄴ
    case 0x03:
        switch (ch2)
        {
        // ㅈ
        case 0x0d:
            return 5;
        // ㅎ
        case 0x13:
            return 6;
        }
        break;
    // ㄹ
    case 0x06:
        switch (ch2)
        {
        // ㄱ
        case 0x01:
            return 9;
        // ㅁ
        case 0x07:
            return 10;
        // ㅂ
        case 0x08:
            return 11;
        // ㅅ
        case 0x0a:
            return 12;
        // ㅌ
        case 0x11:
            return 13;
        // ㅍ
        case 0x12:
            return 14;
        // ㅎ
        case 0x13:
            return 15;
        }
        break;
    // ㅂ
    case 0x08:
        if (ch2 == 0x0a)
            return 18;
        break;
    }

    // 조합불가
    return 0;
}

u8 ComposeMoum(u8 ch, u8 ch2)
{
    switch (ch)
    {
    // ㅗ
    case 0x1c:
        switch (ch2)
        {
        // ㅏ
        case 0x14:
            return 0x1d;
        // ㅐ
        case 0x15:
            return 0x1e;
        // ㅣ
        case 0x28:
            return 0x1f;
        }
        break;

    // ㅜ
    case 0x21:
        switch (ch2)
        {
        // ㅓ
        case 0x18:
            return 0x22;
        // ㅔ
        case 0x19:
            return 0x23;
        // ㅣ
        case 0x28:
            return 0x24;
        }
        break;

    // ㅡ
    case 0x26:
        // ㅣ
        if (ch2 == 0x28)
            return 0x27;
        break;
    }

    // 조합불가
    return 0;
}

u8 SplitJung(u8 ch, u8 index)
{
    if (index == 0)
    {
        if (ch >= 9 && ch <= 11)
        {
            // ㅘ, ㅙ, ㅚ
            return 8;
        }
        else if (ch >= 14 && ch <= 16)
        {
            // ㅝ, ㅞ, ㅟ
            return 13;
        }
        else if (ch == 19)
        {
            // ㅢ
            return 18;
        }
    }
    else
    {
        switch (ch)
        {
        // ㅘ
        case 9:
            return 0;
        // ㅙ
        case 10:
            return 1;
        // ㅚ, ㅟ, ㅢ
        case 11:
        case 16:
        case 19:
            return 20;
        // ㅝ
        case 14:
            return 4;
        // ㅞ
        case 15:
            return 5;
        }
    }

    return 0;
}

u8 SplitJong(u8 ch, u8 index)
{
    if (index == 0)
    {
        if (ch == 3)
        {
            // ㄳ
            return 1;
        }
        else if (ch >= 5 && ch <= 6)
        {
            // ㄵ, ㄶ
            return 4;
        }
        else if (ch >= 9 && ch <= 15)
        {
            // ㄺ, ㄻ, ㄼ, ㄽ, ㄾ, ㄿ, ㅀ
            return 8;
        }
        else if (ch == 18)
        {
            // ㅄ
            return 17;
        }
    }
    else
    {
        switch (ch)
        {
        // ㄳ
        case 3:
            return 19;
        // ㄵ
        case 5:
            return 22;
        // ㄶ
        case 6:
            return 27;
        // ㄺ
        case 9:
            return 1;
        // ㄻ
        case 10:
            return 16;
        // ㄼ
        case 11:
            return 17;
        // ㄽ
        case 12:
            return 19;
        // ㄾ
        case 13:
            return 25;
        // ㄿ
        case 14:
            return 26;
        // ㅀ
        case 15:
            return 27;
        // ㅄ
        case 18:
            return 19;
        }
    }

    return 0;
}
