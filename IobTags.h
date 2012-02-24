////////////////////////////////////
// IobTags.h : definitions of Imagine-object 
// tags for loading and parsing files
// in common IFF-style format.
//
// Tags found in TDDD-FORM specification.
//
// Ilkka Prusi 2012
//


#ifndef _IOBTAGS_H_
#define _IOBTAGS_H_

/* helper to generate chunk and subchunk IDs */
/* MakeID macro found in original EA-IFF85 standard specification */
#define MakeID(a,b,c,d) (((a)<<24)|((b)<<16)|((c)<<8)|(d))

/* Universal IFF identifiers */
/** IFF start-identifier **/
#define ID_FORM		MakeID('F','O','R','M')

/** 
 Imagine format: TDDD
**/
#define ID_TDDD		MakeID('T','D','D','D')

#endif

