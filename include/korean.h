#include "text.h"

#ifndef GUARD_KOREAN_H
#define GUARD_KOREAN_H

bool8 IsKoreanGlyph(u16 glyph);
bool8 IsJaum(u8 glyph);
bool8 IsMoum(u8 glyph);
bool8 HasJong(u16 ch);

u8 GetCho(u8 index);
u8 GetJung(u8 index);
u8 GetJong(u8 index);

u8 DecomposeToCho(u16 korean);
u8 DecomposeToJung(u16 korean);
u8 DecomposeToJong(u16 korean);
u8 DecomposeToJongIndex(u16 korean);

u8 ConvertJongToCho(u8 jong);

u16 ConvertKoreanToUnicode(u16 korean);
u16 ConvertUnicodeToKorean(u16 code);
u16 ComposeKorean(u8 cho, u8 jung, u8 jong);
u16 ComposeKoreanToUnicode(u8 cho, u8 jung, u8 jong);

u8 ComposeJaum(u8 ch, u8 ch2);
u8 ComposeMoum(u8 ch, u8 ch2);

u8 SplitJung(u8 ch, u8 index);
u8 SplitJong(u8 ch, u8 index);

#endif
