#include "global.h"
#include "main.h"
#include "window.h"
#include "text.h"
#include "string_util.h"
#include "sound.h"

ALIGNED(4)
static const u8 sUnknown_08616124[] = {1, 2, 4};
static const u16 sFont6BrailleGlyphs[] = INCBIN_U16("graphics/fonts/font6.fwjpnfont");

static void DecompressGlyphFont6(u16);

// MEMO: 기존 영문 점자를 지원하기 위한 데이터
static const u8 sBrailleCharmap[][2] =
{
    { CHAR_A,      0x01 },
    { CHAR_B,      0x05 },
    { CHAR_C,      0x03 },
    { CHAR_D,      0x0B },
    { CHAR_E,      0x09 },
    { CHAR_F,      0x07 },
    { CHAR_G,      0x0F },
    { CHAR_H,      0x0D },
    { CHAR_I,      0x06 },
    { CHAR_J,      0x0E },
    { CHAR_K,      0x11 },
    { CHAR_L,      0x15 },
    { CHAR_M,      0x13 },
    { CHAR_N,      0x1B },
    { CHAR_O,      0x19 },
    { CHAR_P,      0x17 },
    { CHAR_Q,      0x1F },
    { CHAR_R,      0x1D },
    { CHAR_S,      0x16 },
    { CHAR_T,      0x1E },
    { CHAR_U,      0x31 },
    { CHAR_V,      0x35 },
    { CHAR_W,      0x2E },
    { CHAR_X,      0x33 },
    { CHAR_Y,      0x3B },
    { CHAR_Z,      0x39 },
    { CHAR_SPACE,  0x00 },
    { CHAR_COMMA,  0x04 },
    { CHAR_PERIOD, 0x2C },
};

u16 Font6Func(struct TextPrinter *textPrinter)
{
    u16 char_;
    struct TextPrinterSubStruct *subStruct;
    subStruct = (struct TextPrinterSubStruct *)(&textPrinter->subStructFields);

    switch (textPrinter->state)
    {
        case 0:
            if (JOY_HELD(A_BUTTON | B_BUTTON) && subStruct->hasPrintBeenSpedUp)
            {
                textPrinter->delayCounter = 0;
            }
            if (textPrinter->delayCounter && textPrinter->textSpeed)
            {
                textPrinter->delayCounter --;
                if (gTextFlags.canABSpeedUpPrint && JOY_NEW(A_BUTTON | B_BUTTON))
                {
                    subStruct->hasPrintBeenSpedUp = TRUE;
                    textPrinter->delayCounter = 0;
                }
                return 3;
            }
            if (gTextFlags.autoScroll)
            {
                textPrinter->delayCounter = 3;
            }
            else
            {
                textPrinter->delayCounter = textPrinter->textSpeed;
            }
            char_ = *textPrinter->printerTemplate.currentChar++;
            switch (char_)
            {
                case EOS:
                    return 1;
                case CHAR_NEWLINE:
                    textPrinter->printerTemplate.currentX = textPrinter->printerTemplate.x;
                    textPrinter->printerTemplate.currentY += gFonts[textPrinter->printerTemplate.fontId].maxLetterHeight + textPrinter->printerTemplate.lineSpacing;
                    return 2;
                case PLACEHOLDER_BEGIN:
                    textPrinter->printerTemplate.currentChar++;
                    return 2;
                case EXT_CTRL_CODE_BEGIN:
                    char_ = *textPrinter->printerTemplate.currentChar++;
                    switch (char_)
                    {
                        case EXT_CTRL_CODE_COLOR:
                            textPrinter->printerTemplate.fgColor = *textPrinter->printerTemplate.currentChar++;
                            GenerateFontHalfRowLookupTable(textPrinter->printerTemplate.fgColor, textPrinter->printerTemplate.bgColor, textPrinter->printerTemplate.shadowColor);
                            return 2;
                        case EXT_CTRL_CODE_HIGHLIGHT:
                            textPrinter->printerTemplate.bgColor = *textPrinter->printerTemplate.currentChar++;
                            GenerateFontHalfRowLookupTable(textPrinter->printerTemplate.fgColor, textPrinter->printerTemplate.bgColor, textPrinter->printerTemplate.shadowColor);
                            return 2;
                        case EXT_CTRL_CODE_SHADOW:
                            textPrinter->printerTemplate.shadowColor = *textPrinter->printerTemplate.currentChar++;
                            GenerateFontHalfRowLookupTable(textPrinter->printerTemplate.fgColor, textPrinter->printerTemplate.bgColor, textPrinter->printerTemplate.shadowColor);
                            return 2;
                        case EXT_CTRL_CODE_COLOR_HIGHLIGHT_SHADOW:
                            textPrinter->printerTemplate.fgColor = *textPrinter->printerTemplate.currentChar;
                            textPrinter->printerTemplate.bgColor = *++textPrinter->printerTemplate.currentChar;
                            textPrinter->printerTemplate.shadowColor = *++textPrinter->printerTemplate.currentChar;
                            textPrinter->printerTemplate.currentChar++;

                            GenerateFontHalfRowLookupTable(textPrinter->printerTemplate.fgColor, textPrinter->printerTemplate.bgColor, textPrinter->printerTemplate.shadowColor);
                            return 2;
                        case EXT_CTRL_CODE_PALETTE:
                            textPrinter->printerTemplate.currentChar++;
                            return 2;
                        case EXT_CTRL_CODE_SIZE:
                            subStruct->glyphId = *textPrinter->printerTemplate.currentChar;
                            textPrinter->printerTemplate.currentChar++;
                            return 2;
                        case EXT_CTRL_CODE_RESET_SIZE:
                            return 2;
                        case EXT_CTRL_CODE_PAUSE:
                            textPrinter->delayCounter = *textPrinter->printerTemplate.currentChar++;
                            textPrinter->state = 6;
                            return 2;
                        case EXT_CTRL_CODE_PAUSE_UNTIL_PRESS:
                            textPrinter->state = 1;
                            if (gTextFlags.autoScroll)
                            {
                                subStruct->autoScrollDelay = 0;
                            }
                            return 3;
                        case EXT_CTRL_CODE_WAIT_SE:
                            textPrinter->state = 5;
                            return 3;
                        case EXT_CTRL_CODE_PLAY_BGM:
                        case EXT_CTRL_CODE_PLAY_SE:
                            textPrinter->printerTemplate.currentChar += 2;
                            return 2;
                        case EXT_CTRL_CODE_ESCAPE:
                            char_ = *++textPrinter->printerTemplate.currentChar;
                            break;
                        case EXT_CTRL_CODE_SHIFT_TEXT:
                            textPrinter->printerTemplate.currentX = textPrinter->printerTemplate.x + *textPrinter->printerTemplate.currentChar++;
                            return 2;
                        case EXT_CTRL_CODE_SHIFT_DOWN:
                            textPrinter->printerTemplate.currentY = textPrinter->printerTemplate.y + *textPrinter->printerTemplate.currentChar++;
                            return 2;
                        case EXT_CTRL_CODE_FILL_WINDOW:
                            FillWindowPixelBuffer(textPrinter->printerTemplate.windowId, PIXEL_FILL(textPrinter->printerTemplate.bgColor));
                            return 2;
                    }
                    break;
                case CHAR_PROMPT_CLEAR:
                    textPrinter->state = 2;
                    TextPrinterInitDownArrowCounters(textPrinter);
                    return 3;
                case CHAR_PROMPT_SCROLL:
                    textPrinter->state = 3;
                    TextPrinterInitDownArrowCounters(textPrinter);
                    return 3;
                case CHAR_EXTRA_SYMBOL:
                    char_ = *textPrinter->printerTemplate.currentChar++ | 0x100;
                    break;
                case CHAR_KEYPAD_ICON:
                    textPrinter->printerTemplate.currentChar++;
                    return 0;
            }

            if (char_ == 0x37)
            {
                char_ = (char_ << 8) | *(textPrinter->printerTemplate.currentChar++);
                char_ -= 0x3700;
            }
            else
            {
                u8 i;
                for (i = 0; i < sizeof(sBrailleCharmap); i++)
                {
                    if (char_ == sBrailleCharmap[i][0])
                    {
                        char_ = sBrailleCharmap[i][1];
                        break;
                    }
                }
            }

            DecompressGlyphFont6(char_);

            CopyGlyphToWindow(textPrinter);
            textPrinter->printerTemplate.currentX += gCurrentGlyph.width + textPrinter->printerTemplate.letterSpacing;
            return 0;
        case 1:
            if (TextPrinterWait(textPrinter))
            {
                textPrinter->state = 0;
            }
            return 3;
        case 2:
            if (TextPrinterWaitWithDownArrow(textPrinter))
            {
                FillWindowPixelBuffer(textPrinter->printerTemplate.windowId, PIXEL_FILL(textPrinter->printerTemplate.bgColor));
                textPrinter->printerTemplate.currentX = textPrinter->printerTemplate.x;
                textPrinter->printerTemplate.currentY = textPrinter->printerTemplate.y;
                textPrinter->state = 0;
            }
            return 3;
        case 3:
            if (TextPrinterWaitWithDownArrow(textPrinter))
            {
                TextPrinterClearDownArrow(textPrinter);
                textPrinter->scrollDistance = gFonts[textPrinter->printerTemplate.fontId].maxLetterHeight + textPrinter->printerTemplate.lineSpacing;
                textPrinter->printerTemplate.currentX = textPrinter->printerTemplate.x;
                textPrinter->state = 4;
            }
            return 3;
        case 4:
            if (textPrinter->scrollDistance)
            {
                if (textPrinter->scrollDistance < sUnknown_08616124[gSaveBlock2Ptr->optionsTextSpeed])
                {
                    ScrollWindow(textPrinter->printerTemplate.windowId, 0, textPrinter->scrollDistance, PIXEL_FILL(textPrinter->printerTemplate.bgColor));
                    textPrinter->scrollDistance = 0;
                }
                else
                {
                    ScrollWindow(textPrinter->printerTemplate.windowId, 0, sUnknown_08616124[gSaveBlock2Ptr->optionsTextSpeed], PIXEL_FILL(textPrinter->printerTemplate.bgColor));
                    textPrinter->scrollDistance -= sUnknown_08616124[gSaveBlock2Ptr->optionsTextSpeed];
                }
                CopyWindowToVram(textPrinter->printerTemplate.windowId, 2);
            }
            else
            {
                textPrinter->state = 0;
            }
            return 3;
        case 5:
            if (!IsSEPlaying())
            {
                textPrinter->state = 0;
            }
            return 3;
        case 6:
            if (textPrinter->delayCounter)
            {
                textPrinter->delayCounter --;
            }
            else
            {
                textPrinter->state = 0;
            }
            return 3;
    }
    return 1;
}

static void DecompressGlyphFont6(u16 glyph)
{
    const u16 *glyphs;

    glyphs = sFont6BrailleGlyphs + 0x100 * (glyph / 8) + 0x10 * (glyph % 8);
    DecompressGlyphTile(glyphs, (u16 *)gCurrentGlyph.gfxBufferTop);
    DecompressGlyphTile(glyphs + 0x8, (u16 *)(gCurrentGlyph.gfxBufferTop + 8));
    DecompressGlyphTile(glyphs + 0x80, (u16 *)(gCurrentGlyph.gfxBufferBottom));
    DecompressGlyphTile(glyphs + 0x88, (u16 *)(gCurrentGlyph.gfxBufferBottom + 8));
    gCurrentGlyph.width = 0x10;
    gCurrentGlyph.height = 0x10;
}

u32 GetGlyphWidthFont6(u16 glyphId, bool32 isJapanese)
{
    return 0x10;
}
