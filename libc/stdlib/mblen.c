/*
FUNCTION
<<mblen>>---minimal multibyte length function

INDEX
	mblen

ANSI_SYNOPSIS
	#include <stdlib.h>
	int mblen(const char *<[s]>, size_t <[n]>);

TRAD_SYNOPSIS
	#include <stdlib.h>
	int mblen(<[s]>, <[n]>)
	const char *<[s]>;
	size_t <[n]>;

DESCRIPTION
When MB_CAPABLE is not defined, this is a minimal ANSI-conforming 
implementation of <<mblen>>.  In this case, the
only ``multi-byte character sequences'' recognized are single bytes,
and thus <<1>> is returned unless <[s]> is the null pointer or
has a length of 0 or is the empty string.

When MB_CAPABLE is defined, this routine calls <<_mbtowc_r>> to perform
the conversion, passing a state variable to allow state dependent
decoding.  The result is based on the locale setting which may
be restricted to a defined set of locales.

RETURNS
This implementation of <<mblen>> returns <<0>> if
<[s]> is <<NULL>> or the empty string; it returns <<1>> if not MB_CAPABLE or
the character is a single-byte character; it returns <<-1>>
if the multi-byte character is invalid; otherwise it returns
the number of bytes in the multibyte character.

PORTABILITY
<<mblen>> is required in the ANSI C standard.  However, the precise
effects vary with the locale.

<<mblen>> requires no supporting OS subroutines.
*/

#include <stdlib.h>

int
_DEFUN (mblen, (s, n), 
        const char *s _AND
        size_t n)
{
#ifdef MB_CAPABLE
        static int state;

        return _mbtowc_r (_REENT, NULL, s, n, &state);
#else /* not MB_CAPABLE */
        if (s == NULL || *s == '\0')
                return 0;
        if (n == 0)
                return -1;
        return 1;
#endif /* not MB_CAPABLE */
}

