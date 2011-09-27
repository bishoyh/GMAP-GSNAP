/* $Id: stage3.h,v 1.81 2005/07/13 19:26:04 twu Exp $ */
#ifndef STAGE3_INCLUDED
#define STAGE3_INCLUDED
#include "bool.h"
#include "chrnum.h"
#include "genomicpos.h"
#include "list.h"
#include "sequence.h"
#include "genome.h"
#include "matchpair.h"
#include "stage2.h"
#include "pairpool.h"
#include "dynprog.h"
#include "iit-read.h"

#define EXTRAQUERYGAP 10

#define T Stage3_T
typedef struct T *T;

extern bool
Stage3_watsonp (T this);
extern int
Stage3_cdna_direction (T this);
extern int
Stage3_straintype (T this);
extern int
Stage3_goodness (T this);
extern int
Stage3_matches (T this);
extern int
Stage3_mismatches (T this);
extern int
Stage3_indels (T this);
extern double
Stage3_coverage (T this);
extern Matchpairend_T
Stage3_matchpairend (T this);
extern int
Stage3_querystart (T this);
extern int
Stage3_queryend (T this);
extern int
Stage3_translation_start (T this);
extern int
Stage3_translation_end (T this);
extern int
Stage3_domain (T this);
extern int
Stage3_largemargin (int *chimerapos, T this, Sequence_T queryseq);

extern double
Stage3_fracidentity (T this);
extern Genomicpos_T
Stage3_genomicpos (T this, int querypos, bool headp);
extern int *
Stage3_matchscores (T this, int querylength);
extern void
Stage3_pathscores (int *pathscores, T this, int querylength);
extern int
Stage3_chimeric_goodness (int *matches1, int *matches2, T part1, T part2, int breakpoint, int querylength);

extern int
Stage3_cmp (const void *a, const void *b);
extern bool
Stage3_overlap (T x, T y);

extern void
Stage3_free (T *old);

extern void
Stage3_genomicbounds (Genomicpos_T *genomicstart, Genomicpos_T *genomiclength, T this);
extern Stage3_T
Stage3_truncate_fulllength (Stage3_T old, bool translatep);
extern Stage3_T
Stage3_translate_genomic (T this, bool fulllengthp, bool truncatep);
extern void
Stage3_translate_cdna (T this, T reference, bool literalrefp);
extern void
Stage3_fix_cdna_direction (T this, T reference);
extern void
Stage3_print_pathsummary (T this, int pathnum, IIT_T chromosome_iit, IIT_T contig_iit,
			  char *dbversion, bool zerobasedp);
extern void
Stage3_print_pslformat (T this, int pathnum, IIT_T chromosome_iit, Sequence_T queryseq);
extern void
Stage3_print_mutations (T this, T reference, IIT_T chromosome_iit, char *dbversion,
			bool showalignp, bool zerobasedp, 
			bool continuousp, bool diagnosticp, int proteinmode,
			int invertmode, bool nointronlenp, int wraplength, int ngap);
extern void
Stage3_print_map (T this, IIT_T map_iit, int pathnum, bool map_bothstrands_p);
extern void
Stage3_print_alignment (T this, IIT_T chromosome_iit,
			bool alignsummaryonlyp, bool universalp, bool zerobasedp,
			bool continuousp, bool diagnosticp, bool genomefirstp, int proteinmode,
			int invertmode, bool nointronlenp, int wraplength, int ngap);

extern void
Stage3_print_cdna_exons (T this, int wraplength);
extern void
Stage3_print_protein_cdna (T this, int wraplength);
extern void
Stage3_print_protein_genomic (T this, int wraplength);

extern void
Stage3_print_compressed (T this, Sequence_T queryseq, IIT_T chromosome_iit,
			 char *version, int pathnum, int npaths,
			 bool checksump, int chimerapos, int chimeraequivpos,
			 double donor_prob, double acceptor_prob, 
			 int chimera_cdna_direction, bool zerobasedp);

extern T
Stage3_copy (T old, Pairpool_T pairpool);
extern T
Stage3_copy_bounded (T old, int minpos, int maxpos);

extern T
Stage3_compute (Stage2_T stage2, Sequence_T queryseq, Sequence_T genomicseg, 
		Matchpairend_T matchpairend, int straintype, char *strain,
		Chrnum_T chrnum, Genomicpos_T chroffset, Genomicpos_T chrpos, 
		bool watsonp, int maxpeelback, int maxlookback, 
		int extramaterial_end, int extramaterial_paired,
		int extraband_single, int extraband_end, int extraband_paired, int ngap,
		bool extend_mismatch_p, bool end_microexons_p, Pairpool_T pairpool, 
		Dynprog_T dynprogL, Dynprog_T dynprogM, Dynprog_T dynprogR,
		IIT_T altstrain_iit);

#undef T
#endif
