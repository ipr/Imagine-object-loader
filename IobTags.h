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

/* chunk and subchunk IDs */
#define FORMID_(a,b,c,d) (((a)<<24)|((b)<<16)|((c)<<8)|(d))

/* Universal IFF identifiers */
/** IFF start-identifier **/
#define ID_FORM		FORMID_('F','O','R','M')

/** 
 Imagine format: TDDD
**/
#define ID_TDDD		FORMID_('T','D','D','D')

#endif

