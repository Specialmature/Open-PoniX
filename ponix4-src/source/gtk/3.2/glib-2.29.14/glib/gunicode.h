/* gunicode.h - Unicode manipulation functions
 *
 *  Copyright (C) 1999, 2000 Tom Tromey
 *  Copyright 2000, 2005 Red Hat, Inc.
 *
 * The Gnome Library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * The Gnome Library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with the Gnome Library; see the file COPYING.LIB.  If not,
 * write to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 *   Boston, MA 02111-1307, USA.
 */

#if defined(G_DISABLE_SINGLE_INCLUDES) && !defined (__GLIB_H_INSIDE__) && !defined (GLIB_COMPILATION)
#error "Only <glib.h> can be included directly."
#endif

#ifndef __G_UNICODE_H__
#define __G_UNICODE_H__

#include <glib/gerror.h>
#include <glib/gtypes.h>

G_BEGIN_DECLS

/**
 * gunichar:
 *
 * A type which can hold any UTF-32 or UCS-4 character code,
 * also known as a Unicode code point.
 *
 * If you want to produce the UTF-8 representation of a #gunichar,
 * use g_ucs4_to_utf8(). See also g_utf8_to_ucs4() for the reverse
 * process.
 *
 * To print/scan values of this type as integer, use
 * %G_GINT32_MODIFIER and/or %G_GUINT32_FORMAT.
 *
 * The notation to express a Unicode code point in running text is
 * as a hexadecimal number with four to six digits and uppercase
 * letters, prefixed by the string "U+". Leading zeros are omitted,
 * unless the code point would have fewer than four hexadecimal digits.
 * For example, "U+0041 LATIN CAPITAL LETTER A". To print a code point
 * in the U+-notation, use the format string "U+%04"G_GINT32_FORMAT"X".
 * To scan, use the format string "U+%06"G_GINT32_FORMAT"X".
 *
 * |[
 * gunichar c;
 * sscanf ("U+0041", "U+%06"G_GINT32_FORMAT"X", &amp;c)
 * g_print ("Read U+%04"G_GINT32_FORMAT"X", c);
 * ]|
 */
typedef guint32 gunichar;

/**
 * gunichar2:
 *
 * A type which can hold any UTF-16 code
 * point<footnote id="utf16_surrogate_pairs">UTF-16 also has so called
 * <firstterm>surrogate pairs</firstterm> to encode characters beyond
 * the BMP as pairs of 16bit numbers. Surrogate pairs cannot be stored
 * in a single gunichar2 field, but all GLib functions accepting gunichar2
 * arrays will correctly interpret surrogate pairs.</footnote>.
 *
 * To print/scan values of this type to/from text you need to convert
 * to/from UTF-8, using g_utf16_to_utf8()/g_utf8_to_utf16().
 *
 * To print/scan values of this type as integer, use
 * %G_GINT16_MODIFIER and/or %G_GUINT16_FORMAT.
 */
typedef guint16 gunichar2;

/**
 * GUnicodeType:
 * @G_UNICODE_CONTROL: General category "Other, Control" (Cc)
 * @G_UNICODE_FORMAT: General category "Other, Format" (Cf)
 * @G_UNICODE_UNASSIGNED: General category "Other, Not Assigned" (Cn)
 * @G_UNICODE_PRIVATE_USE: General category "Other, Private Use" (Co)
 * @G_UNICODE_SURROGATE: General category "Other, Surrogate" (Cs)
 * @G_UNICODE_LOWERCASE_LETTER: General category "Letter, Lowercase" (Ll)
 * @G_UNICODE_MODIFIER_LETTER: General category "Letter, Modifier" (Lm)
 * @G_UNICODE_OTHER_LETTER: General category "Letter, Other" (Lo)
 * @G_UNICODE_TITLECASE_LETTER: General category "Letter, Titlecase" (Lt)
 * @G_UNICODE_UPPERCASE_LETTER: General category "Letter, Uppercase" (Lu)
 * @G_UNICODE_SPACING_MARK: General category "Mark, Spacing" (Mc)
 * @G_UNICODE_ENCLOSING_MARK: General category "Mark, Enclosing" (Me)
 * @G_UNICODE_NON_SPACING_MARK: General category "Mark, Nonspacing" (Mn)
 * @G_UNICODE_DECIMAL_NUMBER: General category "Number, Decimal Digit" (Nd)
 * @G_UNICODE_LETTER_NUMBER: General category "Number, Letter" (Nl)
 * @G_UNICODE_OTHER_NUMBER: General category "Number, Other" (No)
 * @G_UNICODE_CONNECT_PUNCTUATION: General category "Punctuation, Connector" (Pc)
 * @G_UNICODE_DASH_PUNCTUATION: General category "Punctuation, Dash" (Pd)
 * @G_UNICODE_CLOSE_PUNCTUATION: General category "Punctuation, Close" (Pe)
 * @G_UNICODE_FINAL_PUNCTUATION: General category "Punctuation, Final quote" (Pf)
 * @G_UNICODE_INITIAL_PUNCTUATION: General category "Punctuation, Initial quote" (Pi)
 * @G_UNICODE_OTHER_PUNCTUATION: General category "Punctuation, Other" (Po)
 * @G_UNICODE_OPEN_PUNCTUATION: General category "Punctuation, Open" (Ps)
 * @G_UNICODE_CURRENCY_SYMBOL: General category "Symbol, Currency" (Sc)
 * @G_UNICODE_MODIFIER_SYMBOL: General category "Symbol, Modifier" (Sk)
 * @G_UNICODE_MATH_SYMBOL: General category "Symbol, Math" (Sm)
 * @G_UNICODE_OTHER_SYMBOL: General category "Symbol, Other" (So)
 * @G_UNICODE_LINE_SEPARATOR: General category "Separator, Line" (Zl)
 * @G_UNICODE_PARAGRAPH_SEPARATOR: General category "Separator, Paragraph" (Zp)
 * @G_UNICODE_SPACE_SEPARATOR: General category "Separator, Space" (Zs)
 *
 * These are the possible character classifications from the
 * Unicode specification.
 * See <ulink url="http://www.unicode.org/Public/UNIDATA/UnicodeData.html">http://www.unicode.org/Public/UNIDATA/UnicodeData.html</ulink>.
 */
typedef enum
{
  G_UNICODE_CONTROL,
  G_UNICODE_FORMAT,
  G_UNICODE_UNASSIGNED,
  G_UNICODE_PRIVATE_USE,
  G_UNICODE_SURROGATE,
  G_UNICODE_LOWERCASE_LETTER,
  G_UNICODE_MODIFIER_LETTER,
  G_UNICODE_OTHER_LETTER,
  G_UNICODE_TITLECASE_LETTER,
  G_UNICODE_UPPERCASE_LETTER,
  G_UNICODE_SPACING_MARK,
  G_UNICODE_ENCLOSING_MARK,
  G_UNICODE_NON_SPACING_MARK,
  G_UNICODE_DECIMAL_NUMBER,
  G_UNICODE_LETTER_NUMBER,
  G_UNICODE_OTHER_NUMBER,
  G_UNICODE_CONNECT_PUNCTUATION,
  G_UNICODE_DASH_PUNCTUATION,
  G_UNICODE_CLOSE_PUNCTUATION,
  G_UNICODE_FINAL_PUNCTUATION,
  G_UNICODE_INITIAL_PUNCTUATION,
  G_UNICODE_OTHER_PUNCTUATION,
  G_UNICODE_OPEN_PUNCTUATION,
  G_UNICODE_CURRENCY_SYMBOL,
  G_UNICODE_MODIFIER_SYMBOL,
  G_UNICODE_MATH_SYMBOL,
  G_UNICODE_OTHER_SYMBOL,
  G_UNICODE_LINE_SEPARATOR,
  G_UNICODE_PARAGRAPH_SEPARATOR,
  G_UNICODE_SPACE_SEPARATOR
} GUnicodeType;

/**
 * G_UNICODE_COMBINING_MARK:
 *
 * Older name for %G_UNICODE_SPACING_MARK.
 *
 * Deprecated: 2.30: Use %G_UNICODE_SPACING_MARK.
 */
#define G_UNICODE_COMBINING_MARK G_UNICODE_SPACING_MARK

/**
 * GUnicodeBreakType:
 * @G_UNICODE_BREAK_MANDATORY: Mandatory Break (BK)
 * @G_UNICODE_BREAK_CARRIAGE_RETURN: Carriage Return (CR)
 * @G_UNICODE_BREAK_LINE_FEED: Line Feed (LF)
 * @G_UNICODE_BREAK_COMBINING_MARK: Attached Characters and Combining Marks (CM)
 * @G_UNICODE_BREAK_SURROGATE: Surrogates (SG)
 * @G_UNICODE_BREAK_ZERO_WIDTH_SPACE: Zero Width Space (ZW)
 * @G_UNICODE_BREAK_INSEPARABLE: Inseparable (IN)
 * @G_UNICODE_BREAK_NON_BREAKING_GLUE: Non-breaking ("Glue") (GL)
 * @G_UNICODE_BREAK_CONTINGENT: Contingent Break Opportunity (CB)
 * @G_UNICODE_BREAK_SPACE: Space (SP)
 * @G_UNICODE_BREAK_AFTER: Break Opportunity After (BA)
 * @G_UNICODE_BREAK_BEFORE: Break Opportunity Before (BB)
 * @G_UNICODE_BREAK_BEFORE_AND_AFTER: Break Opportunity Before and After (B2)
 * @G_UNICODE_BREAK_HYPHEN: Hyphen (HY)
 * @G_UNICODE_BREAK_NON_STARTER: Nonstarter (NS)
 * @G_UNICODE_BREAK_OPEN_PUNCTUATION: Opening Punctuation (OP)
 * @G_UNICODE_BREAK_CLOSE_PUNCTUATION: Closing Punctuation (CL)
 * @G_UNICODE_BREAK_QUOTATION: Ambiguous Quotation (QU)
 * @G_UNICODE_BREAK_EXCLAMATION: Exclamation/Interrogation (EX)
 * @G_UNICODE_BREAK_IDEOGRAPHIC: Ideographic (ID)
 * @G_UNICODE_BREAK_NUMERIC: Numeric (NU)
 * @G_UNICODE_BREAK_INFIX_SEPARATOR: Infix Separator (Numeric) (IS)
 * @G_UNICODE_BREAK_SYMBOL: Symbols Allowing Break After (SY)
 * @G_UNICODE_BREAK_ALPHABETIC: Ordinary Alphabetic and Symbol Characters (AL)
 * @G_UNICODE_BREAK_PREFIX: Prefix (Numeric) (PR)
 * @G_UNICODE_BREAK_POSTFIX: Postfix (Numeric) (PO)
 * @G_UNICODE_BREAK_COMPLEX_CONTEXT: Complex Content Dependent (South East Asian) (SA)
 * @G_UNICODE_BREAK_AMBIGUOUS: Ambiguous (Alphabetic or Ideographic) (AI)
 * @G_UNICODE_BREAK_UNKNOWN: Unknown (XX)
 * @G_UNICODE_BREAK_NEXT_LINE: Next Line (NL)
 * @G_UNICODE_BREAK_WORD_JOINER: Word Joiner (WJ)
 * @G_UNICODE_BREAK_HANGUL_L_JAMO: Hangul L Jamo (JL)
 * @G_UNICODE_BREAK_HANGUL_V_JAMO: Hangul V Jamo (JV)
 * @G_UNICODE_BREAK_HANGUL_T_JAMO: Hangul T Jamo (JT)
 * @G_UNICODE_BREAK_HANGUL_LV_SYLLABLE: Hangul LV Syllable (H2)
 * @G_UNICODE_BREAK_HANGUL_LVT_SYLLABLE: Hangul LVT Syllable (H3)
 * @G_UNICODE_BREAK_CLOSE_PARANTHESIS: Closing Parenthesis (CP). Since 2.28
 *
 * These are the possible line break classifications.
 *
 * The five Hangul types were added in Unicode 4.1, so, has been
 * introduced in GLib 2.10. Note that new types may be added in the future.
 * Applications should be ready to handle unknown values.
 * They may be regarded as %G_UNICODE_BREAK_UNKNOWN.
 *
 * See <ulink url="http://www.unicode.org/unicode/reports/tr14/">http://www.unicode.org/unicode/reports/tr14/</ulink>.
 */
typedef enum
{
  G_UNICODE_BREAK_MANDATORY,
  G_UNICODE_BREAK_CARRIAGE_RETURN,
  G_UNICODE_BREAK_LINE_FEED,
  G_UNICODE_BREAK_COMBINING_MARK,
  G_UNICODE_BREAK_SURROGATE,
  G_UNICODE_BREAK_ZERO_WIDTH_SPACE,
  G_UNICODE_BREAK_INSEPARABLE,
  G_UNICODE_BREAK_NON_BREAKING_GLUE,
  G_UNICODE_BREAK_CONTINGENT,
  G_UNICODE_BREAK_SPACE,
  G_UNICODE_BREAK_AFTER,
  G_UNICODE_BREAK_BEFORE,
  G_UNICODE_BREAK_BEFORE_AND_AFTER,
  G_UNICODE_BREAK_HYPHEN,
  G_UNICODE_BREAK_NON_STARTER,
  G_UNICODE_BREAK_OPEN_PUNCTUATION,
  G_UNICODE_BREAK_CLOSE_PUNCTUATION,
  G_UNICODE_BREAK_QUOTATION,
  G_UNICODE_BREAK_EXCLAMATION,
  G_UNICODE_BREAK_IDEOGRAPHIC,
  G_UNICODE_BREAK_NUMERIC,
  G_UNICODE_BREAK_INFIX_SEPARATOR,
  G_UNICODE_BREAK_SYMBOL,
  G_UNICODE_BREAK_ALPHABETIC,
  G_UNICODE_BREAK_PREFIX,
  G_UNICODE_BREAK_POSTFIX,
  G_UNICODE_BREAK_COMPLEX_CONTEXT,
  G_UNICODE_BREAK_AMBIGUOUS,
  G_UNICODE_BREAK_UNKNOWN,
  G_UNICODE_BREAK_NEXT_LINE,
  G_UNICODE_BREAK_WORD_JOINER,
  G_UNICODE_BREAK_HANGUL_L_JAMO,
  G_UNICODE_BREAK_HANGUL_V_JAMO,
  G_UNICODE_BREAK_HANGUL_T_JAMO,
  G_UNICODE_BREAK_HANGUL_LV_SYLLABLE,
  G_UNICODE_BREAK_HANGUL_LVT_SYLLABLE,
  G_UNICODE_BREAK_CLOSE_PARANTHESIS
} GUnicodeBreakType;

/**
 * GUnicodeScript:
 * @G_UNICODE_SCRIPT_INVALID_CODE:
 *                               a value never returned from g_unichar_get_script()
 * @G_UNICODE_SCRIPT_COMMON:     a character used by multiple different scripts
 * @G_UNICODE_SCRIPT_INHERITED:  a mark glyph that takes its script from the
 * i                             base glyph to which it is attached
 * @G_UNICODE_SCRIPT_ARABIC:     Arabic
 * @G_UNICODE_SCRIPT_ARMENIAN:   Armenian
 * @G_UNICODE_SCRIPT_BENGALI:    Bengali
 * @G_UNICODE_SCRIPT_BOPOMOFO:   Bopomofo
 * @G_UNICODE_SCRIPT_CHEROKEE:   Cherokee
 * @G_UNICODE_SCRIPT_COPTIC:     Coptic
 * @G_UNICODE_SCRIPT_CYRILLIC:   Cyrillic
 * @G_UNICODE_SCRIPT_DESERET:    Deseret
 * @G_UNICODE_SCRIPT_DEVANAGARI: Devanagari
 * @G_UNICODE_SCRIPT_ETHIOPIC:   Ethiopic
 * @G_UNICODE_SCRIPT_GEORGIAN:   Georgian
 * @G_UNICODE_SCRIPT_GOTHIC:     Gothic
 * @G_UNICODE_SCRIPT_GREEK:      Greek
 * @G_UNICODE_SCRIPT_GUJARATI:   Gujarati
 * @G_UNICODE_SCRIPT_GURMUKHI:   Gurmukhi
 * @G_UNICODE_SCRIPT_HAN:        Han
 * @G_UNICODE_SCRIPT_HANGUL:     Hangul
 * @G_UNICODE_SCRIPT_HEBREW:     Hebrew
 * @G_UNICODE_SCRIPT_HIRAGANA:   Hiragana
 * @G_UNICODE_SCRIPT_KANNADA:    Kannada
 * @G_UNICODE_SCRIPT_KATAKANA:   Katakana
 * @G_UNICODE_SCRIPT_KHMER:      Khmer
 * @G_UNICODE_SCRIPT_LAO:        Lao
 * @G_UNICODE_SCRIPT_LATIN:      Latin
 * @G_UNICODE_SCRIPT_MALAYALAM:  Malayalam
 * @G_UNICODE_SCRIPT_MONGOLIAN:  Mongolian
 * @G_UNICODE_SCRIPT_MYANMAR:    Myanmar
 * @G_UNICODE_SCRIPT_OGHAM:      Ogham
 * @G_UNICODE_SCRIPT_OLD_ITALIC: Old Italic
 * @G_UNICODE_SCRIPT_ORIYA:      Oriya
 * @G_UNICODE_SCRIPT_RUNIC:      Runic
 * @G_UNICODE_SCRIPT_SINHALA:    Sinhala
 * @G_UNICODE_SCRIPT_SYRIAC:     Syriac
 * @G_UNICODE_SCRIPT_TAMIL:      Tamil
 * @G_UNICODE_SCRIPT_TELUGU:     Telugu
 * @G_UNICODE_SCRIPT_THAANA:     Thaana
 * @G_UNICODE_SCRIPT_THAI:       Thai
 * @G_UNICODE_SCRIPT_TIBETAN:    Tibetan
 * @G_UNICODE_SCRIPT_CANADIAN_ABORIGINAL:
 *                               Canadian Aboriginal
 * @G_UNICODE_SCRIPT_YI:         Yi
 * @G_UNICODE_SCRIPT_TAGALOG:    Tagalog
 * @G_UNICODE_SCRIPT_HANUNOO:    Hanunoo
 * @G_UNICODE_SCRIPT_BUHID:      Buhid
 * @G_UNICODE_SCRIPT_TAGBANWA:   Tagbanwa
 * @G_UNICODE_SCRIPT_BRAILLE:    Braille
 * @G_UNICODE_SCRIPT_CYPRIOT:    Cypriot
 * @G_UNICODE_SCRIPT_LIMBU:      Limbu
 * @G_UNICODE_SCRIPT_OSMANYA:    Osmanya
 * @G_UNICODE_SCRIPT_SHAVIAN:    Shavian
 * @G_UNICODE_SCRIPT_LINEAR_B:   Linear B
 * @G_UNICODE_SCRIPT_TAI_LE:     Tai Le
 * @G_UNICODE_SCRIPT_UGARITIC:   Ugaritic
 * @G_UNICODE_SCRIPT_NEW_TAI_LUE:
 *                               New Tai Lue
 * @G_UNICODE_SCRIPT_BUGINESE:   Buginese
 * @G_UNICODE_SCRIPT_GLAGOLITIC: Glagolitic
 * @G_UNICODE_SCRIPT_TIFINAGH:   Tifinagh
 * @G_UNICODE_SCRIPT_SYLOTI_NAGRI:
 *                               Syloti Nagri
 * @G_UNICODE_SCRIPT_OLD_PERSIAN:
 *                               Old Persian
 * @G_UNICODE_SCRIPT_KHAROSHTHI: Kharoshthi
 * @G_UNICODE_SCRIPT_UNKNOWN:    an unassigned code point
 * @G_UNICODE_SCRIPT_BALINESE:   Balinese
 * @G_UNICODE_SCRIPT_CUNEIFORM:  Cuneiform
 * @G_UNICODE_SCRIPT_PHOENICIAN: Phoenician
 * @G_UNICODE_SCRIPT_PHAGS_PA:   Phags-pa
 * @G_UNICODE_SCRIPT_NKO:        N'Ko
 * @G_UNICODE_SCRIPT_KAYAH_LI:   Kayah Li. Since 2.16.3
 * @G_UNICODE_SCRIPT_LEPCHA:     Lepcha. Since 2.16.3
 * @G_UNICODE_SCRIPT_REJANG:     Rejang. Since 2.16.3
 * @G_UNICODE_SCRIPT_SUNDANESE:  Sundanese. Since 2.16.3
 * @G_UNICODE_SCRIPT_SAURASHTRA: Saurashtra. Since 2.16.3
 * @G_UNICODE_SCRIPT_CHAM:       Cham. Since 2.16.3
 * @G_UNICODE_SCRIPT_OL_CHIKI:   Ol Chiki. Since 2.16.3
 * @G_UNICODE_SCRIPT_VAI:        Vai. Since 2.16.3
 * @G_UNICODE_SCRIPT_CARIAN:     Carian. Since 2.16.3
 * @G_UNICODE_SCRIPT_LYCIAN:     Lycian. Since 2.16.3
 * @G_UNICODE_SCRIPT_LYDIAN:     Lydian. Since 2.16.3
 * @G_UNICODE_SCRIPT_AVESTAN:    Avestan. Since 2.26
 * @G_UNICODE_SCRIPT_BAMUM:      Bamum. Since 2.26
 * @G_UNICODE_SCRIPT_EGYPTIAN_HIEROGLYPHS:
 *                               Egyptian Hieroglpyhs. Since 2.26
 * @G_UNICODE_SCRIPT_IMPERIAL_ARAMAIC:
 *                               Imperial Aramaic. Since 2.26
 * @G_UNICODE_SCRIPT_INSCRIPTIONAL_PAHLAVI:
 *                               Inscriptional Pahlavi. Since 2.26
 * @G_UNICODE_SCRIPT_INSCRIPTIONAL_PARTHIAN:
 *                               Inscriptional Parthian. Since 2.26
 * @G_UNICODE_SCRIPT_JAVANESE:   Javanese. Since 2.26
 * @G_UNICODE_SCRIPT_KAITHI:     Kaithi. Since 2.26
 * @G_UNICODE_SCRIPT_LISU:       Lisu. Since 2.26
 * @G_UNICODE_SCRIPT_MEETEI_MAYEK:
 *                               Meetei Mayek. Since 2.26
 * @G_UNICODE_SCRIPT_OLD_SOUTH_ARABIAN:
 *                               Old South Arabian. Since 2.26
 * @G_UNICODE_SCRIPT_OLD_TURKIC: Old Turkic. Since 2.28
 * @G_UNICODE_SCRIPT_SAMARITAN:  Samaritan. Since 2.26
 * @G_UNICODE_SCRIPT_TAI_THAM:   Tai Tham. Since 2.26
 * @G_UNICODE_SCRIPT_TAI_VIET:   Tai Viet. Since 2.26
 * @G_UNICODE_SCRIPT_BATAK:      Batak. Since 2.28
 * @G_UNICODE_SCRIPT_BRAHMI:     Brahmi. Since 2.28
 * @G_UNICODE_SCRIPT_MANDAIC:    Mandaic. Since 2.28
 *
 * The #GUnicodeScript enumeration identifies different writing
 * systems. The values correspond to the names as defined in the
 * Unicode standard. The enumeration has been added in GLib 2.14,
 * and is interchangeable with #PangoScript.
 *
 * Note that new types may be added in the future. Applications
 * should be ready to handle unknown values.
 * See <ulink
 * url="http://www.unicode.org/reports/tr24/">Unicode Standard Annex
 * #24: Script names</ulink>.
 */
typedef enum
{                         /* ISO 15924 code */
  G_UNICODE_SCRIPT_INVALID_CODE = -1,
  G_UNICODE_SCRIPT_COMMON       = 0,   /* Zyyy */
  G_UNICODE_SCRIPT_INHERITED,          /* Qaai */
  G_UNICODE_SCRIPT_ARABIC,             /* Arab */
  G_UNICODE_SCRIPT_ARMENIAN,           /* Armn */
  G_UNICODE_SCRIPT_BENGALI,            /* Beng */
  G_UNICODE_SCRIPT_BOPOMOFO,           /* Bopo */
  G_UNICODE_SCRIPT_CHEROKEE,           /* Cher */
  G_UNICODE_SCRIPT_COPTIC,             /* Qaac */
  G_UNICODE_SCRIPT_CYRILLIC,           /* Cyrl (Cyrs) */
  G_UNICODE_SCRIPT_DESERET,            /* Dsrt */
  G_UNICODE_SCRIPT_DEVANAGARI,         /* Deva */
  G_UNICODE_SCRIPT_ETHIOPIC,           /* Ethi */
  G_UNICODE_SCRIPT_GEORGIAN,           /* Geor (Geon, Geoa) */
  G_UNICODE_SCRIPT_GOTHIC,             /* Goth */
  G_UNICODE_SCRIPT_GREEK,              /* Grek */
  G_UNICODE_SCRIPT_GUJARATI,           /* Gujr */
  G_UNICODE_SCRIPT_GURMUKHI,           /* Guru */
  G_UNICODE_SCRIPT_HAN,                /* Hani */
  G_UNICODE_SCRIPT_HANGUL,             /* Hang */
  G_UNICODE_SCRIPT_HEBREW,             /* Hebr */
  G_UNICODE_SCRIPT_HIRAGANA,           /* Hira */
  G_UNICODE_SCRIPT_KANNADA,            /* Knda */
  G_UNICODE_SCRIPT_KATAKANA,           /* Kana */
  G_UNICODE_SCRIPT_KHMER,              /* Khmr */
  G_UNICODE_SCRIPT_LAO,                /* Laoo */
  G_UNICODE_SCRIPT_LATIN,              /* Latn (Latf, Latg) */
  G_UNICODE_SCRIPT_MALAYALAM,          /* Mlym */
  G_UNICODE_SCRIPT_MONGOLIAN,          /* Mong */
  G_UNICODE_SCRIPT_MYANMAR,            /* Mymr */
  G_UNICODE_SCRIPT_OGHAM,              /* Ogam */
  G_UNICODE_SCRIPT_OLD_ITALIC,         /* Ital */
  G_UNICODE_SCRIPT_ORIYA,              /* Orya */
  G_UNICODE_SCRIPT_RUNIC,              /* Runr */
  G_UNICODE_SCRIPT_SINHALA,            /* Sinh */
  G_UNICODE_SCRIPT_SYRIAC,             /* Syrc (Syrj, Syrn, Syre) */
  G_UNICODE_SCRIPT_TAMIL,              /* Taml */
  G_UNICODE_SCRIPT_TELUGU,             /* Telu */
  G_UNICODE_SCRIPT_THAANA,             /* Thaa */
  G_UNICODE_SCRIPT_THAI,               /* Thai */
  G_UNICODE_SCRIPT_TIBETAN,            /* Tibt */
  G_UNICODE_SCRIPT_CANADIAN_ABORIGINAL, /* Cans */
  G_UNICODE_SCRIPT_YI,                 /* Yiii */
  G_UNICODE_SCRIPT_TAGALOG,            /* Tglg */
  G_UNICODE_SCRIPT_HANUNOO,            /* Hano */
  G_UNICODE_SCRIPT_BUHID,              /* Buhd */
  G_UNICODE_SCRIPT_TAGBANWA,           /* Tagb */

  /* Unicode-4.0 additions */
  G_UNICODE_SCRIPT_BRAILLE,            /* Brai */
  G_UNICODE_SCRIPT_CYPRIOT,            /* Cprt */
  G_UNICODE_SCRIPT_LIMBU,              /* Limb */
  G_UNICODE_SCRIPT_OSMANYA,            /* Osma */
  G_UNICODE_SCRIPT_SHAVIAN,            /* Shaw */
  G_UNICODE_SCRIPT_LINEAR_B,           /* Linb */
  G_UNICODE_SCRIPT_TAI_LE,             /* Tale */
  G_UNICODE_SCRIPT_UGARITIC,           /* Ugar */

  /* Unicode-4.1 additions */
  G_UNICODE_SCRIPT_NEW_TAI_LUE,        /* Talu */
  G_UNICODE_SCRIPT_BUGINESE,           /* Bugi */
  G_UNICODE_SCRIPT_GLAGOLITIC,         /* Glag */
  G_UNICODE_SCRIPT_TIFINAGH,           /* Tfng */
  G_UNICODE_SCRIPT_SYLOTI_NAGRI,       /* Sylo */
  G_UNICODE_SCRIPT_OLD_PERSIAN,        /* Xpeo */
  G_UNICODE_SCRIPT_KHAROSHTHI,         /* Khar */

  /* Unicode-5.0 additions */
  G_UNICODE_SCRIPT_UNKNOWN,            /* Zzzz */
  G_UNICODE_SCRIPT_BALINESE,           /* Bali */
  G_UNICODE_SCRIPT_CUNEIFORM,          /* Xsux */
  G_UNICODE_SCRIPT_PHOENICIAN,         /* Phnx */
  G_UNICODE_SCRIPT_PHAGS_PA,           /* Phag */
  G_UNICODE_SCRIPT_NKO,                /* Nkoo */

  /* Unicode-5.1 additions */
  G_UNICODE_SCRIPT_KAYAH_LI,           /* Kali */
  G_UNICODE_SCRIPT_LEPCHA,             /* Lepc */
  G_UNICODE_SCRIPT_REJANG,             /* Rjng */
  G_UNICODE_SCRIPT_SUNDANESE,          /* Sund */
  G_UNICODE_SCRIPT_SAURASHTRA,         /* Saur */
  G_UNICODE_SCRIPT_CHAM,               /* Cham */
  G_UNICODE_SCRIPT_OL_CHIKI,           /* Olck */
  G_UNICODE_SCRIPT_VAI,                /* Vaii */
  G_UNICODE_SCRIPT_CARIAN,             /* Cari */
  G_UNICODE_SCRIPT_LYCIAN,             /* Lyci */
  G_UNICODE_SCRIPT_LYDIAN,             /* Lydi */

  /* Unicode-5.2 additions */
  G_UNICODE_SCRIPT_AVESTAN,                /* Avst */
  G_UNICODE_SCRIPT_BAMUM,                  /* Bamu */
  G_UNICODE_SCRIPT_EGYPTIAN_HIEROGLYPHS,   /* Egyp */
  G_UNICODE_SCRIPT_IMPERIAL_ARAMAIC,       /* Armi */
  G_UNICODE_SCRIPT_INSCRIPTIONAL_PAHLAVI,  /* Phli */
  G_UNICODE_SCRIPT_INSCRIPTIONAL_PARTHIAN, /* Prti */
  G_UNICODE_SCRIPT_JAVANESE,               /* Java */
  G_UNICODE_SCRIPT_KAITHI,                 /* Kthi */
  G_UNICODE_SCRIPT_LISU,                   /* Lisu */
  G_UNICODE_SCRIPT_MEETEI_MAYEK,           /* Mtei */
  G_UNICODE_SCRIPT_OLD_SOUTH_ARABIAN,      /* Sarb */
  G_UNICODE_SCRIPT_OLD_TURKIC,             /* Orkh */
  G_UNICODE_SCRIPT_SAMARITAN,              /* Samr */
  G_UNICODE_SCRIPT_TAI_THAM,               /* Lana */
  G_UNICODE_SCRIPT_TAI_VIET,               /* Tavt */

  /* Unicode-6.0 additions */
  G_UNICODE_SCRIPT_BATAK,                  /* Batk */
  G_UNICODE_SCRIPT_BRAHMI,                 /* Brah */
  G_UNICODE_SCRIPT_MANDAIC                 /* Mand */
} GUnicodeScript;

guint32 g_unicode_script_to_iso15924 (GUnicodeScript script);
GUnicodeScript g_unicode_script_from_iso15924 (guint32 iso15924);

/* Returns TRUE if current locale uses UTF-8 charset.  If CHARSET is
 * not null, sets *CHARSET to the name of the current locale's
 * charset.  This value is statically allocated, and should be copied
 * in case the locale's charset will be changed later using setlocale()
 * or in some other way.
 */
gboolean g_get_charset (const char **charset);

/* These are all analogs of the <ctype.h> functions.
 */
gboolean g_unichar_isalnum   (gunichar c) G_GNUC_CONST;
gboolean g_unichar_isalpha   (gunichar c) G_GNUC_CONST;
gboolean g_unichar_iscntrl   (gunichar c) G_GNUC_CONST;
gboolean g_unichar_isdigit   (gunichar c) G_GNUC_CONST;
gboolean g_unichar_isgraph   (gunichar c) G_GNUC_CONST;
gboolean g_unichar_islower   (gunichar c) G_GNUC_CONST;
gboolean g_unichar_isprint   (gunichar c) G_GNUC_CONST;
gboolean g_unichar_ispunct   (gunichar c) G_GNUC_CONST;
gboolean g_unichar_isspace   (gunichar c) G_GNUC_CONST;
gboolean g_unichar_isupper   (gunichar c) G_GNUC_CONST;
gboolean g_unichar_isxdigit  (gunichar c) G_GNUC_CONST;
gboolean g_unichar_istitle   (gunichar c) G_GNUC_CONST;
gboolean g_unichar_isdefined (gunichar c) G_GNUC_CONST;
gboolean g_unichar_iswide    (gunichar c) G_GNUC_CONST;
gboolean g_unichar_iswide_cjk(gunichar c) G_GNUC_CONST;
gboolean g_unichar_iszerowidth(gunichar c) G_GNUC_CONST;
gboolean g_unichar_ismark    (gunichar c) G_GNUC_CONST;

/* More <ctype.h> functions.  These convert between the three cases.
 * See the Unicode book to understand title case.  */
gunichar g_unichar_toupper (gunichar c) G_GNUC_CONST;
gunichar g_unichar_tolower (gunichar c) G_GNUC_CONST;
gunichar g_unichar_totitle (gunichar c) G_GNUC_CONST;

/* If C is a digit (according to `g_unichar_isdigit'), then return its
   numeric value.  Otherwise return -1.  */
gint g_unichar_digit_value (gunichar c) G_GNUC_CONST;

gint g_unichar_xdigit_value (gunichar c) G_GNUC_CONST;

/* Return the Unicode character type of a given character.  */
GUnicodeType g_unichar_type (gunichar c) G_GNUC_CONST;

/* Return the line break property for a given character */
GUnicodeBreakType g_unichar_break_type (gunichar c) G_GNUC_CONST;

/* Returns the combining class for a given character */
gint g_unichar_combining_class (gunichar uc) G_GNUC_CONST;

gboolean g_unichar_get_mirror_char (gunichar ch,
                                    gunichar *mirrored_ch);

GUnicodeScript g_unichar_get_script (gunichar ch) G_GNUC_CONST;

/* Validate a Unicode character */
gboolean g_unichar_validate (gunichar ch) G_GNUC_CONST;

/* Pairwise canonical compose/decompose */
gboolean g_unichar_compose (gunichar  a,
                            gunichar  b,
                            gunichar *ch);
gboolean g_unichar_decompose (gunichar  ch,
                              gunichar *a,
                              gunichar *b);

gsize g_unichar_fully_decompose (gunichar  ch,
                                 gboolean  compat,
                                 gunichar *result,
                                 gsize     result_len);

/* Compute canonical ordering of a string in-place.  This rearranges
   decomposed characters in the string according to their combining
   classes.  See the Unicode manual for more information.  */
void g_unicode_canonical_ordering (gunichar *string,
                                   gsize     len);


#ifndef G_DISABLE_DEPRECATED
/* Deprecated.  Use g_unichar_fully_decompose() */
gunichar *g_unicode_canonical_decomposition (gunichar  ch,
                                             gsize    *result_len) G_GNUC_MALLOC;
#endif

/* Array of skip-bytes-per-initial character.
 */
GLIB_VAR const gchar * const g_utf8_skip;

/**
 * g_utf8_next_char:
 * @p: Pointer to the start of a valid UTF-8 character
 *
 * Skips to the next character in a UTF-8 string. The string must be
 * valid; this macro is as fast as possible, and has no error-checking.
 * You would use this macro to iterate over a string character by
 * character. The macro returns the start of the next UTF-8 character.
 * Before using this macro, use g_utf8_validate() to validate strings
 * that may contain invalid UTF-8.
 */
#define g_utf8_next_char(p) (char *)((p) + g_utf8_skip[*(const guchar *)(p)])

gunichar g_utf8_get_char           (const gchar  *p) G_GNUC_PURE;
gunichar g_utf8_get_char_validated (const  gchar *p,
                                    gssize        max_len) G_GNUC_PURE;

gchar*   g_utf8_offset_to_pointer (const gchar *str,
                                   glong        offset) G_GNUC_PURE;
glong    g_utf8_pointer_to_offset (const gchar *str,
                                   const gchar *pos) G_GNUC_PURE;
gchar*   g_utf8_prev_char         (const gchar *p) G_GNUC_PURE;
gchar*   g_utf8_find_next_char    (const gchar *p,
                                   const gchar *end) G_GNUC_PURE;
gchar*   g_utf8_find_prev_char    (const gchar *str,
                                   const gchar *p) G_GNUC_PURE;

glong    g_utf8_strlen            (const gchar *p,
                                   gssize       max) G_GNUC_PURE;

gchar   *g_utf8_substring         (const gchar *p,
                                   glong        start_pos,
                                   glong        end_pos) G_GNUC_MALLOC;

gchar   *g_utf8_strncpy           (gchar       *dest,
                                   const gchar *src,
                                   gsize        n);

/* Find the UTF-8 character corresponding to ch, in string p. These
   functions are equivalants to strchr and strrchr */
gchar* g_utf8_strchr  (const gchar *p,
                       gssize       len,
                       gunichar     c);
gchar* g_utf8_strrchr (const gchar *p,
                       gssize       len,
                       gunichar     c);
gchar* g_utf8_strreverse (const gchar *str,
                          gssize len);

gunichar2 *g_utf8_to_utf16     (const gchar      *str,
                                glong             len,
                                glong            *items_read,
                                glong            *items_written,
                                GError          **error) G_GNUC_MALLOC;
gunichar * g_utf8_to_ucs4      (const gchar      *str,
                                glong             len,
                                glong            *items_read,
                                glong            *items_written,
                                GError          **error) G_GNUC_MALLOC;
gunichar * g_utf8_to_ucs4_fast (const gchar      *str,
                                glong             len,
                                glong            *items_written) G_GNUC_MALLOC;
gunichar * g_utf16_to_ucs4     (const gunichar2  *str,
                                glong             len,
                                glong            *items_read,
                                glong            *items_written,
                                GError          **error) G_GNUC_MALLOC;
gchar*     g_utf16_to_utf8     (const gunichar2  *str,
                                glong             len,
                                glong            *items_read,
                                glong            *items_written,
                                GError          **error) G_GNUC_MALLOC;
gunichar2 *g_ucs4_to_utf16     (const gunichar   *str,
                                glong             len,
                                glong            *items_read,
                                glong            *items_written,
                                GError          **error) G_GNUC_MALLOC;
gchar*     g_ucs4_to_utf8      (const gunichar   *str,
                                glong             len,
                                glong            *items_read,
                                glong            *items_written,
                                GError          **error) G_GNUC_MALLOC;

gint      g_unichar_to_utf8 (gunichar    c,
                             gchar      *outbuf);

gboolean g_utf8_validate (const gchar  *str,
                          gssize        max_len,
                          const gchar **end);

gchar *g_utf8_strup   (const gchar *str,
                       gssize       len) G_GNUC_MALLOC;
gchar *g_utf8_strdown (const gchar *str,
                       gssize       len) G_GNUC_MALLOC;
gchar *g_utf8_casefold (const gchar *str,
                        gssize       len) G_GNUC_MALLOC;

/**
 * GNormalizeMode:
 * @G_NORMALIZE_DEFAULT: standardize differences that do not affect the
 *     text content, such as the above-mentioned accent representation
 * @G_NORMALIZE_NFD: another name for %G_NORMALIZE_DEFAULT
 * @G_NORMALIZE_DEFAULT_COMPOSE: like %G_NORMALIZE_DEFAULT, but with
 *     composed forms rather than a maximally decomposed form
 * @G_NORMALIZE_NFC: another name for %G_NORMALIZE_DEFAULT_COMPOSE
 * @G_NORMALIZE_ALL: beyond %G_NORMALIZE_DEFAULT also standardize the
 *     "compatibility" characters in Unicode, such as SUPERSCRIPT THREE
 *     to the standard forms (in this case DIGIT THREE). Formatting
 *     information may be lost but for most text operations such
 *     characters should be considered the same
 * @G_NORMALIZE_NFKD: another name for %G_NORMALIZE_ALL
 * @G_NORMALIZE_ALL_COMPOSE: like %G_NORMALIZE_ALL, but with composed
 *     forms rather than a maximally decomposed form
 * @G_NORMALIZE_NFKC: another name for %G_NORMALIZE_ALL_COMPOSE
 *
 * Defines how a Unicode string is transformed in a canonical
 * form, standardizing such issues as whether a character with
 * an accent is represented as a base character and combining
 * accent or as a single precomposed character. Unicode strings
 * should generally be normalized before comparing them.
 */
typedef enum {
  G_NORMALIZE_DEFAULT,
  G_NORMALIZE_NFD = G_NORMALIZE_DEFAULT,
  G_NORMALIZE_DEFAULT_COMPOSE,
  G_NORMALIZE_NFC = G_NORMALIZE_DEFAULT_COMPOSE,
  G_NORMALIZE_ALL,
  G_NORMALIZE_NFKD = G_NORMALIZE_ALL,
  G_NORMALIZE_ALL_COMPOSE,
  G_NORMALIZE_NFKC = G_NORMALIZE_ALL_COMPOSE
} GNormalizeMode;

gchar *g_utf8_normalize (const gchar   *str,
                         gssize         len,
                         GNormalizeMode mode) G_GNUC_MALLOC;

gint   g_utf8_collate     (const gchar *str1,
                           const gchar *str2) G_GNUC_PURE;
gchar *g_utf8_collate_key (const gchar *str,
                           gssize       len) G_GNUC_MALLOC;
gchar *g_utf8_collate_key_for_filename (const gchar *str,
                                        gssize       len) G_GNUC_MALLOC;


/* private */

gchar *_g_utf8_make_valid (const gchar *name);

G_END_DECLS

#endif /* __G_UNICODE_H__ */
