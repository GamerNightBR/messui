/***************************************************************************

  M.A.M.E.UI  -  Multiple Arcade Machine Emulator with User Interface
  Win32 Portions Copyright (C) 1997-2003 Michael Soderstrom and Chris Kirmse,
  Copyright (C) 2003-2007 Chris Kirmse and the MAME32/MAMEUI team.

  This file is part of MAMEUI, and may only be used, modified and
  distributed under the terms of the MAME license, in "readme.txt".
  By continuing to use, modify or distribute this file you indicate
  that you have read the license and understand and accept it fully.

 ***************************************************************************/

/****************************************************************************
 *      datafile.c
 *      History database engine
 *
 *      Token parsing by Neil Bradley
 *      Modifications and higher-level functions by John Butler
 ****************************************************************************/
// standard windows headers
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// standard C headers
#include <assert.h>
#include <ctype.h>

// MAME/MAMEUI headers
#include "emu.h"
#include "osdcomm.h"
#include "datafile.h"
#include "mui_opts.h" // For MameUIGlobal()
#include "drivenum.h"

/****************************************************************************
 *      token parsing constants
 ****************************************************************************/

#define CR      0x0d    /* '\n' and '\r' meanings are swapped in some */
#define LF      0x0a    /*     compilers (e.g., Mac compilers) */

enum
{
	TOKEN_COMMA,
	TOKEN_EQUALS,
	TOKEN_SYMBOL,
	TOKEN_LINEBREAK,
	TOKEN_INVALID=-1
};

#define MAX_TOKEN_LENGTH        256


/****************************************************************************
 *      datafile constants
 ****************************************************************************/
#define DATAFILE_TAG '$'

static const char *DATAFILE_TAG_KEY = "$info";
static const char *DATAFILE_TAG_BIO = "$bio";
static const char *DATAFILE_TAG_MAME = "$mame";

char *g_history_filename = NULL;
char *g_mameinfo_filename = NULL;
bool is_historydat = 0;

/****************************************************************************
 *      private data for parsing functions
 ****************************************************************************/
static emu_file *fp;				       /* Our file pointer */
static long dwFilePos;					  /* file position */
static UINT8 bToken[MAX_TOKEN_LENGTH];	  /* Our current token */

/* an array of driver name/drivers array index sorted by driver name
   for fast look up by name */
typedef struct
{
    const char *name;
    int index;
} driver_data_type;
static driver_data_type *sorted_drivers = NULL;
static int num_games;


/**************************************************************************
 **************************************************************************
 *
 *              Parsing functions
 *
 **************************************************************************
 **************************************************************************/

/*
 * DriverDataCompareFunc -- compare function for GetGameNameIndex
 */
static int CLIB_DECL DriverDataCompareFunc(const void *arg1,const void *arg2)
{
    return strcmp( ((driver_data_type *)arg1)->name, ((driver_data_type *)arg2)->name );
}

/*
 * GetGameNameIndex -- given a driver name (in lowercase), return
 * its index in the main drivers[] array, or -1 if it's not found.
 */
static int GetGameNameIndex(const char *name)
{
	driver_data_type *driver_index_info;
	driver_data_type key;
	key.name = name;

	if (sorted_drivers == NULL)
	{
		/* initialize array of game names/indices */
		int i;

		sorted_drivers = (driver_data_type *)malloc(sizeof(driver_data_type) * num_games);
		for (i=0;i<num_games;i++)
		{
			sorted_drivers[i].name = driver_list::driver(i).name;
			sorted_drivers[i].index = i;
		}
		qsort(sorted_drivers,num_games,sizeof(driver_data_type),DriverDataCompareFunc);
	}

	/* uses our sorted array of driver names to get the index in log time */
	driver_index_info = (driver_data_type *)bsearch(&key,sorted_drivers,num_games,sizeof(driver_data_type),
								DriverDataCompareFunc);

	if (driver_index_info == NULL)
		return -1;

	return driver_index_info->index;

}

/****************************************************************************
 *      GetNextToken - Pointer to the token string pointer
 *                                 Pointer to position within file
 *
 *      Returns token, or TOKEN_INVALID if at end of file
 ****************************************************************************/
static UINT32 GetNextToken(UINT8 **ppszTokenText, long *pdwPosition)
{
	UINT32 dwLength = 0;						/* Length of symbol */
	long dwPos = 0;						/* Temporary position */
	UINT8 *pbTokenPtr = bToken;			     /* Point to the beginning */
	UINT8 bData = 0;						    /* Temporary data byte */

	while (1)
	{
		bData = fp->getc();				  /* Get next character */

		/* If we're at the end of the file, bail out */

		if (fp->eof())
			return(TOKEN_INVALID);

		/* If it's not whitespace, then let's start eating characters */

		if (' ' != bData && '\t' != bData)
		{
			/* Store away our file position (if given on input) */

			if (pdwPosition)
				*pdwPosition = dwFilePos;

			/* If it's a separator, special case it */

			if (',' == bData || '=' == bData)
			{
				*pbTokenPtr++ = bData;
				*pbTokenPtr = '\0';
				++dwFilePos;

				if (',' == bData)
					return(TOKEN_COMMA);
				else
					return(TOKEN_EQUALS);
			}

			/* Otherwise, let's try for a symbol */

			if (bData > ' ')
			{
				dwLength = 0;		   /* Assume we're 0 length to start with */

				/* Loop until we've hit something we don't understand */

				while (bData != ',' && bData != '=' && bData != ' '
						&&bData != '\t' && bData != '\n' && bData != '\r' && fp->eof() == 0)
				{
					++dwFilePos;
					*pbTokenPtr++ = bData;  /* Store our byte */
					++dwLength;
					assert(dwLength < MAX_TOKEN_LENGTH);
					bData = fp->getc();
				}

				/* If it's not the end of the file, put the last received byte */
				/* back. We don't want to touch the file position, though if */
				/* we're past the end of the file. Otherwise, adjust it. */

				if (0 == fp->eof())
				{
					fp->ungetc(bData);
				}

				/* Null terminate the token */

				*pbTokenPtr = '\0';

				/* Connect up the */

				if (ppszTokenText)
					*ppszTokenText = bToken;

				return(TOKEN_SYMBOL);
			}

			/* Not a symbol. Let's see if it's a cr/cr, lf/lf, or cr/lf/cr/lf */
			/* sequence */

			if (LF == bData)
			{
				/* Unix style perhaps? */

				bData = fp->getc();	  /* Peek ahead */
				fp->ungetc(bData);	  /* Force a retrigger if subsequent LF's */

				if (LF == bData)		/* Two LF's in a row - it's a UNIX hard CR */
				{
					++dwFilePos;
					*pbTokenPtr++ = bData;  /* A real linefeed */
					*pbTokenPtr = '\0';
					return(TOKEN_LINEBREAK);
				}

				/* Otherwise, fall through and keep parsing. */

			}
			else
			if (CR == bData)		/* Carriage return? */
			{
				/* Figure out if it's Mac or MSDOS format */

				++dwFilePos;
				bData = fp->getc();	  /* Peek ahead */

				/* We don't need to bother with EOF checking. It will be 0xff if */
				/* it's the end of the file and will be caught by the outer loop. */

				if (CR == bData)		/* Mac style hard return! */
				{
					/* Do not advance the file pointer in case there are successive */
					/* CR/CR sequences */

					/* Stuff our character back upstream for successive CR's */

					fp->ungetc(bData);

					*pbTokenPtr++ = bData;  /* A real carriage return (hard) */
					*pbTokenPtr = '\0';
					return(TOKEN_LINEBREAK);
				}
				else
				if (LF == bData)	/* MSDOS format! */
				{
					++dwFilePos;		    /* Our file position to reset to */
					dwPos = dwFilePos;	      /* Here so we can reposition things */

					if (is_historydat)
					{
						fp->seek(dwPos, SEEK_SET);

						if (pdwPosition)
							*pdwPosition = dwPos;

						*pbTokenPtr++ = '\r';
						*pbTokenPtr++ = '\n';
						*pbTokenPtr = '\0';

						return(TOKEN_LINEBREAK);
					}

					/* Look for a followup CR/LF */

					bData = fp->getc();  /* Get the next byte */

					if (CR == bData)	/* CR! Good! */
					{
						bData = fp->getc();  /* Get the next byte */

						/* We need to do this to pick up subsequent CR/LF sequences */

						fp->seek(dwPos, SEEK_SET);

						if (pdwPosition)
							*pdwPosition = dwPos;

						if (LF == bData)	/* LF? Good! */
						{
							*pbTokenPtr++ = '\r';
							*pbTokenPtr++ = '\n';
							*pbTokenPtr = '\0';

							return(TOKEN_LINEBREAK);
						}
					}
					else
					{
						--dwFilePos;
						fp->ungetc(bData);  /* Put the character back. No good */
					}
				}
				else
				{
					--dwFilePos;
					fp->ungetc(bData);  /* Put the character back. No good */
				}

				/* Otherwise, fall through and keep parsing */
			}
		}

		++dwFilePos;
	}
}


/****************************************************************************
 *      ParseClose - Closes the existing opened file (if any)
 ****************************************************************************/
static void ParseClose(void)
{
	/* If the file is open, time for fclose. */

	if (fp)
	{
		global_free(fp);
	}

	fp = NULL;
}


/****************************************************************************
 *      ParseOpen - Open up file for reading
 ****************************************************************************/
static BOOL ParseOpen(const char *pszFilename)
{
	/* Open file up in binary mode */
	is_historydat = 0;
	fp = global_alloc(emu_file("", OPEN_FLAG_READ));
	/* If this is NULL, return FALSE. We can't open it */
	if (fp == NULL)
		return FALSE;

	file_error err = fp->open(pszFilename);
	if (err != FILERR_NONE)
	{
		global_free(fp);
		fp = NULL;
		return FALSE;
	}

	/* See if it is history.dat by checking if 2nd byte is a hash */
	UINT8 bData = fp->getc();
	bData = fp->getc();
	if (bData == 0x23) is_historydat = 1;

	/* Otherwise, prepare! */
	dwFilePos = 0;
	return TRUE;
}


/****************************************************************************
 *      ParseSeek - Move the file position indicator
 ****************************************************************************/
static UINT8 ParseSeek(long offset, int whence)
{
	int result = fp->seek(offset, whence);

	if (0 == result)
	{
		dwFilePos = fp->tell();
	}
	return (UINT8)result;
}



/**************************************************************************
 **************************************************************************
 *
 *	      Datafile functions
 *
 **************************************************************************
 **************************************************************************/


/**************************************************************************
 *      ci_strncmp - case insensitive character array compare
 *
 *      Returns zero if the first n characters of s1 and s2 are equal,
 *      ignoring case.
 **************************************************************************/
static int ci_strncmp (const char *s1, const char *s2, int n)
{
	int c1 = 0, c2 = 0;

	while (n)
	{
		if ((c1 = tolower (*s1)) != (c2 = tolower (*s2)))
			return (c1 - c2);
		else if (!c1)
			break;
		--n;

		s1++;
		s2++;
	}
	return 0;
}


/**************************************************************************
 *      index_datafile
 *      Create an index for the records in the currently open datafile.
 *
 *      Returns 0 on error, or the number of index entries created.
 **************************************************************************/
static int index_datafile (struct tDatafileIndex **_index)
{
	struct tDatafileIndex *idx;
	int count = 0;
	UINT32 token = TOKEN_SYMBOL;
		num_games = driver_list::total();
	/* rewind file */
	if (ParseSeek (0L, SEEK_SET)) return 0;

	/* allocate index */
	idx = *_index = (tDatafileIndex *)malloc (num_games * sizeof (struct tDatafileIndex));
	if (NULL == idx) return 0;

	/* loop through datafile */
	while ((count < (num_games - 1)) && TOKEN_INVALID != token)
	{
		long tell = 0;
		UINT8 *s = 0;

		token = GetNextToken (&s, &tell);
		if (TOKEN_SYMBOL != token) continue;

		/* DATAFILE_TAG_KEY identifies the driver */
		if (!ci_strncmp (DATAFILE_TAG_KEY, (char *)s, strlen (DATAFILE_TAG_KEY)))
		{
			token = GetNextToken (&s, &tell);
			if (TOKEN_EQUALS == token)
			{
				int done = 0;

				token = GetNextToken (&s, &tell);
				while (!done && TOKEN_SYMBOL == token)
				{
					int game_index = 0;
					UINT8 *p = 0;
					for (p = s; *p; p++)
						*p = tolower(*p);

					game_index = GetGameNameIndex((char *)s);
					if (game_index >= 0)
					{
						idx->driver = &driver_list::driver(game_index);
						idx->offset = tell;
						idx++;
						count++;
						/* done = 1;  Not done, as we must process other clones in list */

					}
					if (!done)
					{
						token = GetNextToken (&s, &tell);

						if (TOKEN_COMMA == token)
							token = GetNextToken (&s, &tell);
						else
							done = 1; /* end of key field */
					}
				}
			}
		}
	}

	/* mark end of index */
	idx->offset = 0L;
	idx->driver = 0;
	return count;
}


/**************************************************************************
 *      load_datafile_text
 *
 *      Loads text field for a driver into the buffer specified. Specify the
 *      driver, a pointer to the buffer, the buffer size, the index created by
 *      index_datafile(), and the desired text field (e.g., DATAFILE_TAG_BIO).
 *
 *      Returns 0 if successful.
 **************************************************************************/
static int load_datafile_text (const game_driver *drv, char *buffer, int bufsize,
	struct tDatafileIndex *idx, const char *tag)
{
	int     offset = 0;
	int found = 0;
	UINT32  token = TOKEN_SYMBOL;
	UINT32  prev_token = TOKEN_SYMBOL;

	*buffer = '\0';

	/* find driver in datafile index */
	while (idx->driver)
	{
		if (idx->driver == drv) break;

		idx++;
	}
	if (idx->driver == 0) return 1; /* driver not found in index */

	/* seek to correct point in datafile */
	if (ParseSeek (idx->offset, SEEK_SET)) return 1;

	/* read text until buffer is full or end of entry is encountered */
	while (TOKEN_INVALID != token)
	{
		UINT8 *s;
		int len = 0;
		long tell = 0;

		token = GetNextToken (&s, &tell);
		if (TOKEN_INVALID == token) continue;

		if (found)
		{
			/* end entry when a tag is encountered */
			if (TOKEN_SYMBOL == token && DATAFILE_TAG == s[0] && TOKEN_LINEBREAK == prev_token) break;

			prev_token = token;

			/* translate platform-specific linebreaks to '\n' */
			if (TOKEN_LINEBREAK == token)
							strcpy ((char *)s, "\n");

			/* append a space to words */
			if (TOKEN_LINEBREAK != token)
							strcat ((char *)s, " ");

			/* remove extraneous space before commas */
			if (TOKEN_COMMA == token)
			{
				--buffer;
				--offset;
				*buffer = '\0';
			}

			/* Get length of text to add to the buffer */
			len = strlen ((char *)s);

			/* Check for buffer overflow */
			/* For some reason we can get a crash if we try */
			/* to use the last 30 characters of the buffer  */
			if ((bufsize - offset) - len <= 45)
			{
			    strcpy ((char *)s, " ...[TRUNCATED]");
			    len = strlen((char *)s);
			    strcpy (buffer, (char *)s);
			    buffer += len;
			    offset += len;
			    break;
			}

			/* add this word to the buffer */
			strcpy (buffer, (char *)s);
			buffer += len;
			offset += len;
		}
		else
		{
			if (TOKEN_SYMBOL == token)
			{
				/* looking for requested tag */
				if (!ci_strncmp (tag, (char *)s, strlen (tag)))
					found = 1;
				else if (!ci_strncmp (DATAFILE_TAG_KEY, (char *)s, strlen (DATAFILE_TAG_KEY)))
					break; /* error: tag missing */
			}
		}
	}
	return (!found);
}


/**************************************************************************
 *      load_driver_history
 *      Load history text for the specified driver into the specified buffer.
 *      Combines $bio field of HISTORY.DAT with $mame field of MAMEINFO.DAT.
 *
 *      Returns 0 if successful.
 *
 *      NOTE: For efficiency the indices are never freed (intentional leak).
 **************************************************************************/
int load_driver_history (const game_driver *drv, char *buffer, int bufsize)
{
	static struct tDatafileIndex *hist_idx = 0;
	static struct tDatafileIndex *mame_idx = 0;
//  const game_driver *clone_of = NULL;
	int history = 0, mameinfo = 0;
	int err = 0;

	*buffer = 0;


//	if (!g_history_filename || !*g_history_filename)
//		g_history_filename = mame_strdup("sysinfo.dat");

	/* try to open history datafile */
	if (ParseOpen (g_history_filename))
	{
		/* create index if necessary */
		if (hist_idx)
			history = 1;
		else
			history = (index_datafile (&hist_idx) != 0);

		/* load history text */
		if (hist_idx)
		{
			const game_driver *gdrv;

			gdrv = drv;
			do
			{
				if ( ( gdrv->flags & GAME_IS_BIOS_ROOT) == 1 )
					break;
				err = load_datafile_text (gdrv, buffer, bufsize,
										  hist_idx, DATAFILE_TAG_BIO);
						int g = driver_list::clone(*gdrv);
						if (g!=-1) gdrv = &driver_list::driver(g); else gdrv = NULL;
			} while (err && gdrv);

			if (err) history = 0;
		}
		ParseClose ();
	}

//	if (!g_mameinfo_filename || !*g_mameinfo_filename)
//		g_mameinfo_filename = mame_strdup("messinfo.dat");

	/* try to open mameinfo datafile */
	if (ParseOpen (g_mameinfo_filename))
	{
		/* create index if necessary */
		if (mame_idx)
			mameinfo = 1;
		else
			mameinfo = (index_datafile (&mame_idx) != 0);

		/* load informational text (append) */
		if (mame_idx)
		{
			int len = strlen (buffer);
			const game_driver *gdrv;

			gdrv = drv;
			do
			{
				if ( (gdrv->flags & GAME_IS_BIOS_ROOT) == 1 )
					break;
				err = load_datafile_text (gdrv, buffer+len, bufsize-len,
										  mame_idx, DATAFILE_TAG_MAME);

					int g = driver_list::clone(*gdrv);
					if (g!=-1) gdrv = &driver_list::driver(g); else gdrv = NULL;
			} while (err && gdrv);

			if (err) mameinfo = 0;
		}
		ParseClose ();
	}

	return (history == 0 && mameinfo == 0);
}
