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

/**
  INFO: only in TurboSilver "cell" files (optional)
*/
#define ID_INFO		MakeID('I','N','F','O')

/**
  OBJ: in both "cell" and "object" files,
  supports object hierarchies
*/
#define ID_OBJ		MakeID('O','B','J',' ')

/** sub-chunks of OBJ */
/**
	EXTR: describes "external" object (in a separate file),
	only used by TurboSilver "cell" files and not supported by Imagine?
*/
#define ID_EXTR		MakeID('E','X','T','R')

/** DESC: describe one node in hierarchy */
#define ID_DESC		MakeID('D','E','S','C')

/** TOBJ: "terminating object" ending of hierarchy chain */
#define ID_TOBJ		MakeID('T','O','B','J')

#endif

