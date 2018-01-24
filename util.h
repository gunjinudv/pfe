/*-----------------------------------------------------------------------------
  
			       U T I L . H
				   
		       Version 1.2 - 15 Mai 1995
				   
			     Nicolas ROUGON
	         Institut National des Telecommunications
		      Departement SIGNAL & IMAGES

-----------------------------------------------------------------------------*/

/******************* P A C K A G E  D E S C R I P T I O N ********************



******************************************************************************/

#define my_max(a,b)	((a) > (b) ? (a) : (b))
#define my_min(p,q)	((p) < (q) ? (p) : (q))
#define my_max3(a,b,c)	( ((a>b) && (a>c)) ? a : (b>c ? b : c))
#define my_min3(a,b,c)	( ((a<b) && (a<c)) ? a : (b<c ? b : c))

#define SIGN(a)         ((a) > .0 ? 1 : ((a) < .0 ? -1 : 0))

/* MONO returns total intensity of r,g,b triple (i = .33R + .5G + .17B) */
#define MONO(rd,gn,bl) ( ((int)(rd)*11 + (int)(gn)*16 + (int)(bl)*5) >> 5)

/* RANGE forces a to be in the range b..c (inclusive) */
#define RANGE(a,b,c) 	\
 if ( (a) < (b) )	\
   a = b;	       	\
 else if ( (a) > (c) )  \
   a = c;

#define RANGE2(a,b,c)	( (a<b) ? b : ( (a>c) ? c : a ) )

#define IS_IN_INTERVAL(a,b,c) (((a<b) || (a>c)) ? 0 : 1)
