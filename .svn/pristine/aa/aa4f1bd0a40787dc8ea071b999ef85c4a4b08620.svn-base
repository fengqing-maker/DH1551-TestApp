
#include "str_English.h"
#if(MULTI_MENU_LANG)
#include "str_French.h"
#include "str_Italian.h"
#include "str_Portuguese.h"
#include "str_Spanish.h"
#include "str_German.h"
#include "str_Turkish.h"
#include "str_Polish.h"
#include "str_Russia.h"
#include "str_Arabic.h"
#include "str_Thai.h"
#include "str_Persian.h"
#ifdef HINDI_LANGUAGE_SUPPORT
#include "str_Hindi.h"
#endif
#ifdef TELUGU_LANGUAGE_SUPPORT
#include "str_Telugu.h"
#endif
#ifdef BENGALI_LANGUAGE_SUPPORT
#include "str_Bengali.h"
#endif
#endif

const unsigned char *strings_infor[]=
{
    english_strs_array,
#if(MULTI_MENU_LANG)
    french_strs_array,
    italian_strs_array,
    portuguese_strs_array,
    spanish_strs_array,
    german_strs_array,
    turkish_strs_array,
    polish_strs_array,
    russia_strs_array,
    arabic_strs_array,
    persian_strs_array,
#ifdef HINDI_LANGUAGE_SUPPORT
    hindi_strs_array,
#endif
#ifdef TELUGU_LANGUAGE_SUPPORT	
    telugu_strs_array,
#endif
#ifdef BENGALI_LANGUAGE_SUPPORT	
    bengali_strs_array,
#endif	
//    Thai_strs_array,
#endif
};

const LANG_TABLE g_lang_rsc_map_table[] __attribute__((section(".flash")))=
{
    {ENGLISH_ENV,     LIB_STRING_ENGLISH, LIB_CHAR_ASCII,        LIB_FONT_DEFAULT},
    {FRANCE_ENV,     LIB_STRING_FRENCH,     LIB_CHAR_ASCII,        LIB_FONT_DEFAULT},
    {GERMANY_ENV,     LIB_STRING_GERMAN,     LIB_CHAR_ASCII,        LIB_FONT_DEFAULT},
    {ITALY_ENV,     LIB_STRING_ITALY,     LIB_CHAR_ASCII,        LIB_FONT_DEFAULT},
    {PORTUGUESE_ENV,LIB_STRING_PORTUGUESE, LIB_CHAR_ASCII,        LIB_FONT_DEFAULT},
    {RUSSIAN_ENV,    LIB_STRING_RUSSIAN, LIB_CHAR_ASCII,        LIB_FONT_DEFAULT},
    {SPANISH_ENV,   LIB_STRING_SPANISH, LIB_CHAR_ASCII,     LIB_FONT_DEFAULT},
    {TURKISH_ENV,   LIB_STRING_TURKISH, LIB_CHAR_ASCII,     LIB_FONT_DEFAULT},
    {POLISH_ENV,    LIB_STRING_POLISH,  LIB_CHAR_ASCII,     LIB_FONT_DEFAULT},
    {ARABIC_ENV,    LIB_STRING_ARABIC,  LIB_CHAR_ASCII,     LIB_FONT_DEFAULT},
    {PERSIAN_ENV,    LIB_STRING_PERSIAN,  LIB_CHAR_ASCII,     LIB_FONT_DEFAULT},
#ifdef HINDI_LANGUAGE_SUPPORT
	{HINDI_ENV,		LIB_STRING_HINDI,	LIB_CHAR_ASCII,		LIB_FONT_DEFAULT},
#endif
#ifdef TELUGU_LANGUAGE_SUPPORT
	{TELUGU_ENV,	LIB_STRING_TELUGU,	LIB_CHAR_ASCII,		LIB_FONT_DEFAULT},
#endif	
#ifdef BENGALI_LANGUAGE_SUPPORT
	{BENGALI_ENV,	LIB_STRING_BENGALI,	LIB_CHAR_ASCII,		LIB_FONT_DEFAULT},
#endif	
};

#define    SIZE_LANG_TABLE    sizeof(g_lang_rsc_map_table)/sizeof(LANG_TABLE)

