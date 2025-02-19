/* Pango
 * disasm.c: Dump OpenType layout tables
 *
 * Copyright (C) 2000 Red Hat Software
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#include <glib.h>		/* For G_HAVE_ISO_VARARGS */
#include <stdarg.h>

#include "disasm.h"

#ifdef G_HAVE_ISO_VARARGS
#define DUMP(...) dump (stream, indent, __VA_ARGS__)
#elif defined (G_HAVE_GNUC_VARARGS)
#define DUMP(args...) dump (stream, indent, args)
#endif
#define DUMP_FINT(strct,fld) dump (stream, indent, "<" #fld ">%d</" #fld ">\n", (strct)->fld)
#define DUMP_FUINT(strct,fld) dump (stream, indent, "<" #fld ">%u</" #fld ">\n", (strct)->fld)
#define DUMP_FGLYPH(strct,fld) dump (stream, indent, "<" #fld ">%#4x</" #fld ">\n", (strct)->fld)
#define DUMP_FGLYPH(strct,fld) dump (stream, indent, "<" #fld ">%#4x</" #fld ">\n", (strct)->fld)
#define DUMP_USHORT_ARRAY(strct,fld,cnt) Dump_UShort_Array ((strct)->fld, cnt, #fld, stream, indent, is_gsub);

#define DEF_DUMP(type) static void Dump_ ## type (TTO_ ## type *type, FILE *stream, int indent, FT_Bool is_gsub)
#define RECURSE(name, type, val) do {  DUMP ("<" #name ">\n"); Dump_ ## type (val, stream, indent + 1, is_gsub); DUMP ("</" #name ">\n"); } while (0)
#define RECURSE_NUM(name, i, type, val) do {  DUMP ("<" #name "> <!-- %d -->\n", i); Dump_ ## type (val, stream, indent + 1, is_gsub); DUMP ("</" #name ">\n"); } while (0)
#define DUMP_VALUE_RECORD(val, frmt) do {  DUMP ("<ValueRecord>\n"); Dump_ValueRecord (val, stream, indent + 1, is_gsub, frmt); DUMP ("</ValueRecord>\n"); } while (0)

static void
do_indent (FILE *stream, int indent)
{
  int i;

  for (i = 0; i < indent * 3; i++)
    fputc (' ', stream);
}

static void 
dump (FILE *stream, int indent, const char *format, ...) 
{
  va_list list;
  
  do_indent (stream, indent);
  
  va_start (list, format);
  vfprintf (stream, format, list);
  va_end (list);
}

static void 
Dump_UShort_Array (FT_UShort *array, int count, const char *name, FILE *stream, int indent, FT_Bool is_gsub) 
{
  int i;
  
  do_indent (stream, indent);

  printf ("<%s>", name);
  for (i = 0; i < count; i++)
    printf ("%d%s", array[i], i == 0 ? "" : " ");
  printf ("</%s>\n", name);
}

static void 
Print_Tag (FT_ULong tag, FILE *stream)
{
  fprintf (stream, "%c%c%c%c", 
	   (unsigned char)(tag >> 24),
	   (unsigned char)((tag & 0xff0000) >> 16),
	   (unsigned char)((tag & 0xff00) >> 8),
	   (unsigned char)(tag & 0xff));
}

DEF_DUMP (LangSys)
{
  int i;

  DUMP_FUINT (LangSys, LookupOrderOffset);
  DUMP_FUINT (LangSys, ReqFeatureIndex);
  DUMP_FUINT (LangSys, FeatureCount);

  for (i=0; i < LangSys->FeatureCount; i++)
    DUMP("<FeatureIndex>%d</FeatureIndex>\n", LangSys->FeatureIndex[i]);
}

DEF_DUMP (Script)
{
  int i;

  RECURSE (DefaultLangSys, LangSys, &Script->DefaultLangSys);

  DUMP_FUINT (Script, LangSysCount);

  for (i=0; i < Script->LangSysCount; i++)
    {
      do_indent (stream, indent);
      fprintf (stream, "<LangSysTag>");
      Print_Tag (Script->LangSysRecord[i].LangSysTag, stream);
      fprintf (stream, "</LangSysTag>\n");
      RECURSE_NUM (LangSys, i, LangSys, &Script->LangSysRecord[i].LangSys);
    }
}

DEF_DUMP (ScriptList)
{
  int i;
  
  DUMP_FUINT (ScriptList, ScriptCount);

  for (i=0; i < ScriptList->ScriptCount; i++)
    { 
      do_indent (stream, indent);
      fprintf (stream, "<ScriptTag>");
      Print_Tag (ScriptList->ScriptRecord[i].ScriptTag, stream);
      fprintf (stream, "</ScriptTag>\n");
      RECURSE_NUM (Script, i, Script, &ScriptList->ScriptRecord[i].Script);
    }
}

DEF_DUMP (Feature)
{
  int i;
  
  DUMP_FUINT (Feature, FeatureParams);
  DUMP_FUINT (Feature, LookupListCount);

  for (i=0; i < Feature->LookupListCount; i++)
    DUMP("<LookupIndex>%d</LookupIndex>\n", Feature->LookupListIndex[i]);
}

DEF_DUMP (MarkRecord)
{
  DUMP_FUINT (MarkRecord, Class);
  DUMP("<Anchor>%d</Anchor>\n", MarkRecord->MarkAnchor.PosFormat );
}

DEF_DUMP (MarkArray)
{
  int i;

  DUMP_FUINT (MarkArray, MarkCount);

  for (i=0; i < MarkArray->MarkCount; i++)
    RECURSE_NUM (MarkRecord, i, MarkRecord, &MarkArray->MarkRecord[i]);
}

DEF_DUMP (FeatureList)
{
  int i;
  
  DUMP_FUINT (FeatureList, FeatureCount);

  for (i=0; i < FeatureList->FeatureCount; i++)
    { 
      do_indent (stream, indent);
      fprintf (stream, "<FeatureTag>");
      Print_Tag (FeatureList->FeatureRecord[i].FeatureTag, stream);
      fprintf (stream, "</FeatureTag> <!-- %d -->\n", i);
      RECURSE_NUM (Feature, i, Feature, &FeatureList->FeatureRecord[i].Feature);
    }
}

DEF_DUMP (Coverage)
{
  DUMP_FUINT (Coverage, CoverageFormat);

  if (Coverage->CoverageFormat == 1)
    {
      int i;
      DUMP_FUINT (&Coverage->cf.cf1, GlyphCount);

      for (i = 0; i < Coverage->cf.cf1.GlyphCount; i++)
	DUMP("<Glyph>%#4x</Glyph> <!-- %d -->\n",
	     Coverage->cf.cf1.GlyphArray[i], i);
    }
  else
    {
      int i;
      DUMP_FUINT (&Coverage->cf.cf2, RangeCount);
      
      for ( i = 0; i < Coverage->cf.cf2.RangeCount; i++ )
	  DUMP("<Glyph>%#4x - %#4x</Glyph> <!-- %d -->\n",
	       Coverage->cf.cf2.RangeRecord[i].Start,
	       Coverage->cf.cf2.RangeRecord[i].End);
    }
}

DEF_DUMP (ClassRangeRecord)
{
  DUMP_FGLYPH (ClassRangeRecord, Start);
  DUMP_FGLYPH (ClassRangeRecord, End);
  DUMP_FUINT (ClassRangeRecord, Class);
}
     
DEF_DUMP (ClassDefinition)
{
  DUMP_FUINT( ClassDefinition, ClassFormat);
  DUMP_FUINT( ClassDefinition, loaded);

  if (ClassDefinition->ClassFormat == 1)
    {
      int i;
      TTO_ClassDefFormat1 *ClassDefFormat1 = &ClassDefinition->cd.cd1;
      DUMP("<ClassDefinition>\n");
      DUMP_FUINT (ClassDefFormat1, StartGlyph );
      DUMP_FUINT (ClassDefFormat1, GlyphCount );
      for (i = 0; i < ClassDefFormat1->GlyphCount; i++)
	DUMP(" <Class>%d</Class> <!-- %#4x -->", ClassDefFormat1->ClassValueArray[i],
	     ClassDefFormat1->StartGlyph+i );
    }
  else if (ClassDefinition->ClassFormat == 2)
    {
      int i;
      TTO_ClassDefFormat2 *ClassDefFormat2 = &ClassDefinition->cd.cd2;
      DUMP_FUINT (ClassDefFormat2, ClassRangeCount);
      
      for (i = 0; i < ClassDefFormat2->ClassRangeCount; i++)
	RECURSE_NUM (ClassRangeRecord, i, ClassRangeRecord, &ClassDefFormat2->ClassRangeRecord[i]);
    }
  else
    printf("invalid class def table!!!\n");
}

DEF_DUMP (SubstLookupRecord)
{
  DUMP_FUINT (SubstLookupRecord, SequenceIndex);
  DUMP_FUINT (SubstLookupRecord, LookupListIndex);
}

DEF_DUMP (ChainSubClassRule)
{
  int i;

  DUMP_USHORT_ARRAY (ChainSubClassRule, Backtrack, ChainSubClassRule->BacktrackGlyphCount);
  DUMP_USHORT_ARRAY (ChainSubClassRule, Input, ChainSubClassRule->InputGlyphCount - 1);
  DUMP_USHORT_ARRAY (ChainSubClassRule, Lookahead, ChainSubClassRule->LookaheadGlyphCount);
  
  for (i = 0; i < ChainSubClassRule->SubstCount; i++)
    RECURSE_NUM (SubstLookupRecord, i, SubstLookupRecord, &ChainSubClassRule->SubstLookupRecord[i]);

  indent--;
}

DEF_DUMP (ChainSubClassSet)
{
  int i;
  
  DUMP_FUINT( ChainSubClassSet, ChainSubClassRuleCount );
  for (i = 0; i < ChainSubClassSet->ChainSubClassRuleCount; i++)
    RECURSE_NUM (ChainSubClassRule, i, ChainSubClassRule, &ChainSubClassSet->ChainSubClassRule[i]);
}

static void
Dump_GSUB_Lookup_Single (TTO_SubTable *subtable, FILE *stream, int indent, FT_Bool is_gsub)
{
  TTO_SingleSubst *SingleSubst = &subtable->st.gsub.single;

  DUMP_FUINT (SingleSubst, SubstFormat);
  RECURSE (Coverage, Coverage, &SingleSubst->Coverage);

  if (SingleSubst->SubstFormat == 1)
    {
      DUMP_FINT (&SingleSubst->ssf.ssf1, DeltaGlyphID);
    }
  else
    {
      int i;
      
      DUMP_FINT (&SingleSubst->ssf.ssf2, GlyphCount);
      for (i=0; i < SingleSubst->ssf.ssf2.GlyphCount; i++)
	DUMP("<Substitute>%#4x</Substitute> <!-- %d -->\n", SingleSubst->ssf.ssf2.Substitute[i], i);
    }
}

DEF_DUMP (Ligature)
{
  int i;
  
  DUMP_FGLYPH (Ligature, LigGlyph);
  DUMP_FUINT (Ligature, ComponentCount);

  for (i=0; i < Ligature->ComponentCount - 1; i++)
    DUMP("<Component>%#4x</Component>\n", Ligature->Component[i]);
}

DEF_DUMP (LigatureSet)
{
  int i;
  
  DUMP_FUINT (LigatureSet, LigatureCount);

  for (i=0; i < LigatureSet->LigatureCount; i++)
    RECURSE_NUM (Ligature, i, Ligature, &LigatureSet->Ligature[i]);
}

static void
Dump_GSUB_Lookup_Ligature (TTO_SubTable *subtable, FILE *stream, int indent, FT_Bool is_gsub)
{
  int i;
  TTO_LigatureSubst *LigatureSubst = &subtable->st.gsub.ligature;

  DUMP_FUINT (LigatureSubst, SubstFormat);
  RECURSE (Coverage, Coverage, &LigatureSubst->Coverage);

  DUMP_FUINT (LigatureSubst, LigatureSetCount);

  for (i=0; i < LigatureSubst->LigatureSetCount; i++)
    RECURSE_NUM (LigatureSet, i, LigatureSet, &LigatureSubst->LigatureSet[i]);
}

DEF_DUMP (ContextSubstFormat1)
{
  DUMP("Not implemented!!!\n");
}

DEF_DUMP (ContextSubstFormat2)
{
  DUMP_FUINT (ContextSubstFormat2, MaxContextLength);
  RECURSE (Coverage, Coverage, &ContextSubstFormat2->Coverage);
  RECURSE (ClassDefinition, ClassDefinition, &ContextSubstFormat2->ClassDef);
}

DEF_DUMP (ContextSubstFormat3)
{
  DUMP("Not implemented!!!\n");
}

static void
Dump_GSUB_Lookup_Context (TTO_SubTable *subtable, FILE *stream, int indent, FT_Bool is_gsub)
{
  TTO_ContextSubst *ContextSubst = &subtable->st.gsub.context;

  DUMP_FUINT (ContextSubst, SubstFormat);
  switch( ContextSubst->SubstFormat )
    {
    case 1:
      Dump_ContextSubstFormat1 (&ContextSubst->csf.csf1, stream, indent+2, is_gsub);
      break;
    case 2:
      Dump_ContextSubstFormat2 (&ContextSubst->csf.csf2, stream, indent+2, is_gsub);
      break;
    case 3:
      Dump_ContextSubstFormat3 (&ContextSubst->csf.csf3, stream, indent+2, is_gsub);
      break;
    default:
      printf("invalid subformat!!!!!\n");
    }
}

DEF_DUMP (ChainContextSubstFormat1)
{
  DUMP("Not implemented!!!\n");
}

DEF_DUMP (ChainContextSubstFormat2)
{
  int i;
  
  RECURSE (Coverage, Coverage, &ChainContextSubstFormat2->Coverage);
  DUMP_FUINT (ChainContextSubstFormat2, MaxBacktrackLength);
  RECURSE (ClassDefinition, ClassDefinition, &ChainContextSubstFormat2->BacktrackClassDef);
  DUMP_FUINT (ChainContextSubstFormat2, MaxInputLength);
  RECURSE (ClassDefinition, ClassDefinition, &ChainContextSubstFormat2->InputClassDef);
  DUMP_FUINT (ChainContextSubstFormat2, MaxLookaheadLength);
  RECURSE (ClassDefinition, ClassDefinition, &ChainContextSubstFormat2->LookaheadClassDef);
  
  DUMP_FUINT (ChainContextSubstFormat2, ChainSubClassSetCount);
  for (i = 0; i < ChainContextSubstFormat2->ChainSubClassSetCount; i++)
    RECURSE (ChainSubClassSet, ChainSubClassSet, &ChainContextSubstFormat2->ChainSubClassSet[i]);
}

DEF_DUMP (ChainContextSubstFormat3)
{
  DUMP("Not implemented!!!\n");
}

static void
Dump_GSUB_Lookup_Chain (TTO_SubTable *subtable, FILE *stream, int indent, FT_Bool is_gsub)
{
  TTO_ChainContextSubst *chain = &subtable->st.gsub.chain;
  
  DUMP_FUINT (chain, SubstFormat);
  switch (chain->SubstFormat)
    {
    case 1:
      Dump_ChainContextSubstFormat1 (&chain->ccsf.ccsf1, stream, indent+2, is_gsub);
      break;
    case 2:
      Dump_ChainContextSubstFormat2 (&chain->ccsf.ccsf2, stream, indent+2, is_gsub);
      break;
    case 3:
      Dump_ChainContextSubstFormat3 (&chain->ccsf.ccsf3, stream, indent+2, is_gsub);
      break;
    default:
      printf("invalid subformat!!!!!\n");
    }
}

static void
Dump_Device (TTO_Device *Device, FILE *stream, int indent, FT_Bool is_gsub)
{
  int i;
  int bits = 0;
  int n_per;
  unsigned int mask;
  
  DUMP_FUINT (Device, StartSize);
  DUMP_FUINT (Device, EndSize);
  DUMP_FUINT (Device, DeltaFormat);
  switch (Device->DeltaFormat)
    {
    case 1:
      bits = 2;
      break;
    case 2:
      bits = 4;
      break;
    case 3:
      bits = 8;
      break;
    }

  n_per = 16 / bits;
  mask = (1 << bits) - 1;
  mask = mask << (16 - bits);

  DUMP ("<DeltaValue>");
  for (i = Device->StartSize; i <= Device->EndSize ; i++)
    {
      FT_UShort val = Device->DeltaValue[i / n_per];
      FT_Short signed_val = ((val << ((i % n_per) * bits)) & mask);
      dump (stream, indent, "%d", signed_val >> (16 - bits));
      if (i != Device->EndSize)
	DUMP (", ");
    }
  DUMP ("</DeltaValue>\n");
}
     
static void
Dump_ValueRecord (TTO_ValueRecord *ValueRecord, FILE *stream, int indent, FT_Bool is_gsub, FT_UShort value_format)
{
  if (value_format & HAVE_X_PLACEMENT)
    DUMP_FINT (ValueRecord, XPlacement);
  if (value_format & HAVE_Y_PLACEMENT)
    DUMP_FINT (ValueRecord, YPlacement);
  if (value_format & HAVE_X_ADVANCE)
    DUMP_FINT (ValueRecord, XAdvance);
  if (value_format & HAVE_Y_ADVANCE)
    DUMP_FINT (ValueRecord, XAdvance);
  if (value_format & HAVE_X_PLACEMENT_DEVICE)
    RECURSE (Device, Device, &ValueRecord->XPlacementDevice);
  if (value_format & HAVE_Y_PLACEMENT_DEVICE)
    RECURSE (Device, Device, &ValueRecord->YPlacementDevice);
  if (value_format & HAVE_X_ADVANCE_DEVICE)
    RECURSE (Device, Device, &ValueRecord->XAdvanceDevice);
  if (value_format & HAVE_Y_ADVANCE_DEVICE)
    RECURSE (Device, Device, &ValueRecord->YAdvanceDevice);
  if (value_format & HAVE_X_ID_PLACEMENT)
    DUMP_FUINT (ValueRecord, XIdPlacement);
  if (value_format & HAVE_Y_ID_PLACEMENT)
    DUMP_FUINT (ValueRecord, YIdPlacement);
  if (value_format & HAVE_X_ID_ADVANCE)
    DUMP_FUINT (ValueRecord, XIdAdvance);
  if (value_format & HAVE_Y_ID_ADVANCE)
    DUMP_FUINT (ValueRecord, XIdAdvance);
}

static void
Dump_GPOS_Lookup_Single (TTO_SubTable *subtable, FILE *stream, int indent, FT_Bool is_gsub)
{
  TTO_SinglePos *SinglePos = &subtable->st.gpos.single;

  DUMP_FUINT (SinglePos, PosFormat);
  RECURSE (Coverage, Coverage, &SinglePos->Coverage);

  DUMP_FUINT (SinglePos, ValueFormat);

  if (SinglePos->PosFormat == 1)
    {
      DUMP_VALUE_RECORD (&SinglePos->spf.spf1.Value, SinglePos->ValueFormat);
    }
  else
    {
      int i;
      
      DUMP_FUINT (&SinglePos->spf.spf2, ValueCount);
      for (i = 0; i < SinglePos->spf.spf2.ValueCount; i++)
	DUMP_VALUE_RECORD (&SinglePos->spf.spf2.Value[i], SinglePos->ValueFormat);
    }
}

static void
Dump_PairValueRecord (TTO_PairValueRecord *PairValueRecord, FILE *stream, int indent, FT_Bool is_gsub, FT_UShort ValueFormat1, FT_UShort ValueFormat2)
{
  DUMP_FUINT (PairValueRecord, SecondGlyph);
  DUMP_VALUE_RECORD (&PairValueRecord->Value1, ValueFormat1);
  DUMP_VALUE_RECORD (&PairValueRecord->Value2, ValueFormat2);
}

static void
Dump_PairSet (TTO_PairSet *PairSet, FILE *stream, int indent, FT_Bool is_gsub, FT_UShort ValueFormat1, FT_UShort ValueFormat2)
{
  int i;
  DUMP_FUINT (PairSet, PairValueCount);

  for (i = 0; i < PairSet->PairValueCount; i++)
    {
      DUMP ("<PairValueRecord>\n");
      Dump_PairValueRecord (&PairSet->PairValueRecord[i], stream, indent + 1, is_gsub, ValueFormat1, ValueFormat2);
      DUMP ("</PairValueRecord>\n");
    }
}

static void
Dump_GPOS_Lookup_Pair (TTO_SubTable *subtable, FILE *stream, int indent, FT_Bool is_gsub)
{
  TTO_PairPos *PairPos = &subtable->st.gpos.pair;

  DUMP_FUINT (PairPos, PosFormat);
  RECURSE (Coverage, Coverage, &PairPos->Coverage);

  DUMP_FUINT (PairPos, ValueFormat1);
  DUMP_FUINT (PairPos, ValueFormat2);

  if (PairPos->PosFormat == 1)
    {
      int i;

      DUMP_FUINT (&PairPos->ppf.ppf1, PairSetCount);
      for (i = 0; i < PairPos->ppf.ppf1.PairSetCount; i++)
	{
	  DUMP ("<PairSet>\n");
	  Dump_PairSet (&PairPos->ppf.ppf1.PairSet[i], stream, indent + 1, is_gsub, PairPos->ValueFormat1, PairPos->ValueFormat2);
	  DUMP ("</PairSet>\n");
	}
    }
  else
    {
    }
}

static void
Dump_GPOS_Lookup_Markbase (TTO_SubTable *subtable, FILE *stream, int indent, FT_Bool is_gsub)
{
  int i;
  TTO_MarkBasePos *markbase = &subtable->st.gpos.markbase;
  
  DUMP_FUINT (markbase, PosFormat);
  RECURSE (Coverage, Coverage, &markbase->MarkCoverage);
  RECURSE (Coverage, Coverage, &markbase->BaseCoverage);
  DUMP_FUINT (markbase, ClassCount);
  RECURSE (MarkArray, MarkArray, &markbase->MarkArray);
  
  DUMP ("<BaseArray>\n");
  indent++;
  
  DUMP_FUINT (&markbase->BaseArray, BaseCount);
  for (i = 0; i < markbase->BaseArray.BaseCount; i++)
    {
      int j;
      TTO_BaseRecord *r = &markbase->BaseArray.BaseRecord[i];
      DUMP ("<BaseRecord> <!-- %d -->\n",  i);
      for (j = 0; j < markbase->ClassCount; j++)
	DUMP ("  <Anchor>%d</Anchor>\n", r->BaseAnchor->PosFormat);
      DUMP ("<BaseRecord>\n");
    }
  
  indent--;
  DUMP ("</BaseArray>\n");
}

DEF_DUMP (Lookup)
{
  int i;
  const char *lookup_name = NULL;
  void (*lookup_func) (TTO_SubTable *subtable, FILE *stream, int indent, FT_Bool is_gsub) = NULL;

  if (is_gsub)
    {
      switch (Lookup->LookupType)
	{
	case  GSUB_LOOKUP_SINGLE:
	  lookup_name = "SINGLE";
	  lookup_func = Dump_GSUB_Lookup_Single;
	  break;
	case  GSUB_LOOKUP_MULTIPLE:
	  lookup_name = "MULTIPLE";
	  break;
	case  GSUB_LOOKUP_ALTERNATE:
	  lookup_name = "ALTERNATE";
	  break;
	case  GSUB_LOOKUP_LIGATURE:
	  lookup_name = "LIGATURE";
	  lookup_func = Dump_GSUB_Lookup_Ligature;
	  break;
	case  GSUB_LOOKUP_CONTEXT:
	  lookup_name = "CONTEXT";
	  lookup_func = Dump_GSUB_Lookup_Context;
	  break;
	case  GSUB_LOOKUP_CHAIN:
	  lookup_name = "CHAIN";
	  lookup_func = Dump_GSUB_Lookup_Chain;
	  break;
	}
    }
  else
    {
      switch (Lookup->LookupType)
	{
	case GPOS_LOOKUP_SINGLE:
	  lookup_name = "SINGLE";
	  lookup_func = Dump_GPOS_Lookup_Single;
	  break;
	case GPOS_LOOKUP_PAIR:
	  lookup_name = "PAIR";
	  lookup_func = Dump_GPOS_Lookup_Pair;
	  break;
	case GPOS_LOOKUP_CURSIVE:
	  lookup_name = "CURSIVE";
	  break;
	case GPOS_LOOKUP_MARKBASE:
	  lookup_name = "MARKBASE";
	  lookup_func = Dump_GPOS_Lookup_Markbase;
	  break;
	case GPOS_LOOKUP_MARKLIG:
	  lookup_name = "MARKLIG";
	  break;
	case GPOS_LOOKUP_MARKMARK:
	  lookup_name = "MARKMARK";
	  break;
	case GPOS_LOOKUP_CONTEXT:
	  lookup_name = "CONTEXT";
	  break;
	case GPOS_LOOKUP_CHAIN:
	  lookup_name = "CHAIN";
	  break;
	}
    }

  DUMP("<LookupType>%s</LookupType>\n", lookup_name);

  for (i=0; i < Lookup->SubTableCount; i++)
    {
      DUMP ("<Subtable>\n");
      if (lookup_func)
	(*lookup_func) (&Lookup->SubTable[i], stream, indent + 1, is_gsub);
      DUMP ("</Subtable>\n");
    }
}

DEF_DUMP (LookupList)
{
  int i;

  DUMP_FUINT (LookupList, LookupCount);

  for (i=0; i < LookupList->LookupCount; i++)
    RECURSE_NUM (Lookup, i, Lookup, &LookupList->Lookup[i]);
}

void
TT_Dump_GSUB_Table (TTO_GSUB gsub, FILE *stream)
{
  int indent = 0;
  FT_Bool is_gsub = 1;

  RECURSE (ScriptList, ScriptList, &gsub->ScriptList);
  RECURSE (FeatureList, FeatureList, &gsub->FeatureList);
  RECURSE (LookupList, LookupList, &gsub->LookupList);
}

void
TT_Dump_GPOS_Table (TTO_GPOS gpos, FILE *stream)
{
  int indent = 0;
  FT_Bool is_gsub = 0;

  RECURSE (ScriptList, ScriptList, &gpos->ScriptList);
  RECURSE (FeatureList, FeatureList, &gpos->FeatureList);
  RECURSE (LookupList, LookupList, &gpos->LookupList);
}
