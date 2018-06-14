#include "ft_sh.h"

/*
**	ft_prompt 
**
**	there's no end, just 
**
**	dquote> 	"
**	quote> 		'
**	bquote> 	`
**	subsh> 		(
**
**
**	ft_prompt is gonna return a raw string
**		check for incomplete capsule
**			call ft_prompt and concatinate those string
**	RAW STRING -> STILL_RAW STRING
**
**	STILL_RAW STRING -> tokenizer
**		tokenizer is gonna delete the special characters and eliminate the encapsulate
**		while its reading and fragmentating
**	
**		2 PART TOKENIZER
**			built a tree
**	
**	
**	change spaecial characters:
**		- backslashes		\
**			*which is basically waiting for a new line
**		- env values		$
**		- spaecial chars	~ <- $HOME
**			so this is another env value
**	BEFORE EXECUTION
**
**	ACTUALLY SUBSHELL MIGHT FAIL BECUASE IT NEED TO FIND FOR THE CLOSING BRACKETS
**
** you can change IS_CAPSULE to differ QUOTES and OTHER INHIBS
** like:
**		\ PRIORITY
**		( PRIORITY
**		{
**		[
**
**		SUBSH is currently not handle it
*/


#define DQUOTE '\"'
#define QUOTE '\''
#define BQUOTE '`'
#define SUBSH '('

#define NEWLINE '\\'

#define DQUOTE_PROMPT "dquote> "
#define QUOTE_PROMPT "quote> "
#define BQUOTE_PROMPT "bquote> "
#define SUBSH_PROMPT "subsh> "
#define NEWLINE_PROMPT "> "


#define IS_CAPSULE (str[i] == '\"' || str[i] == '\'' || str[i] == '`')
//#define IS_BRACK_NL (str[i] == '\\' || str[i] == '(' || str[i] == ')')
#define IS_BRACK_NL (str[i] == '\\')

#define STRNWL(x, y) ft_strjoin_newline(x, y)
#define ALLO_AND_FREE(dest, x, y) dest = STRNWL(x, y); free(x); free(y)



/*
**	basically calling ft_prompt over and over again until the prompt is fully
**	complete
**	the only moment where you have to free is when you do the join thingy
**	
**	IMPORTANT
**	after you check with one type you need to check if any other type is also
**	involved so you run is capsule_incomplete in the concat string
*/

/*
**  for newline
**  	ft_streq(ft_strstr(str, "\"), "")
**		
**  because it doesnt really matter if it has a space after that it shouldn prompt
**
**
*/

char		*concatinated_string(char type)
{
	char	*temp;
	char	*concat;
	char	*join;
	int		cont_nbr_capsule;

	cont_nbr_capsule = 0;
	temp = ft_prompt(get_type_prompt(type));
	cont_chars_capsules(temp, type, &(cont_nbr_capsule));
	while (cont_nbr_capsule % 1 == 1 || cont_nbr_capsule == 0)
	{
		concat = ft_prompt(get_type_prompt(type));
		join = ft_strjoin_newline(temp, concat);
		free(temp);
		free(concat);
		temp = join;
		cont_nbr_capsule = 0;
		cont_chars_capsules(temp, type, &(cont_nbr_capsule));
	}
	return (temp);
}

/*
*	you can use this thing recursively 
*/

#define LAST_CHAR_BSLASH(x, i) (ft_strequ(ft_strstr(x + i, "\\"), "\\") == 1)
#define N_SLASH(x, i) cont_nbr_backslashes(x, i)

char		*concatined_newline(int i) // this can be void
{
	char	*temp;
	char	*concat;
	char	*join;
	int		e;
	char	*extra;

	e = -1;
	temp = ft_prompt(NEWLINE_PROMPT);
	if (LAST_CHAR_BSLASH(temp, i) && ((N_SLASH(temp, i) % 2 == 0 ) || \
		(N_SLASH(temp, i) == 0)))
	{
		concat = ft_prompt(NEWLINE_PROMPT);
		while (concat[++e])
			if (concat[e] == '\\')
				if (LAST_CHAR_BSLASH(concat, e) && \
				((N_SLASH(concat, e) % 2 == 0 ) || (N_SLASH(concat, e) == 0)))
				{
					extra = concatined_newline(e);
					ALLO_AND_FREE(join, concat, extra);
					concat = join;
				}
		ALLO_AND_FREE(join, temp, concat);
		temp = join;
	}
	return (temp);
}


char		is_capsule_incomplete(char *str, char **temp)
{
	int		i;
	int		cont_nbr_capsule;
	char	get_capsule;
	char	*concat;
	char	*tmp;

//	get_capsule = 0;
	i = 0;
	cont_nbr_capsule = 0;
	while(str[i])
	{
		if (IS_CAPSULE)
		{
			get_capsule = str[i];
			cont_chars_capsules(str, get_capsule, &(cont_nbr_capsule));
			if (cont_nbr_capsule % 2 == 1)
			{
				concat = concatinated_string(get_capsule);
				ALLO_AND_FREE(tmp, str, concat);
				str = tmp;
			}
			cont_nbr_capsule = 0;
		}
		else if (IS_BRACK_NL)
		{
			if (LAST_CHAR_BSLASH(str, i) && ((N_SLASH(str, i) % 2 == 0 ) || \
			(N_SLASH(str, i) == 0)))
			{
				concat = concatined_newline(i);
				ALLO_AND_FREE(tmp, str, concat);
				str = tmp;
			}
		}
		++i;
	}
	*temp = str;
	return (0);
}

// you will concantinate str with the new line

char		*parse_line(char *str)
{
	char	*temp;

	// this function can be a void one
	is_capsule_incomplete(str, &(temp));
//	printf("temp |%s|\n", temp);
	return (temp);
}

// DECIPHER BACKSLASH
//  talk to curtis and liam
//  this can be easily handle in the tokenizer
