#include "ft_sh.h"

/*
 *	ft_prompt 
 *
 *	there's no end, just 
 *
 *	dquote> 	"
 *	quote> 		'
 *	bquote> 	`
 *	subsh> 		(
 *
 *
 *	ft_prompt is gonna return a raw string
 *		check for incomplete capsule
 *			call ft_prompt and concatinate those string
 *	RAW STRING -> STILL_RAW STRING
 *
 *	STILL_RAW STRING -> tokenizer
 *		tokenizer is gonna delete the special characters and eliminate the encapsulate
 *		while its reading and fragmentating
 *	
 *		2 PART TOKENIZER
 *			built a tree
 *	
 *	
 *	change spaecial characters:
 *		- backslashes		\
 *		- env values		$
 *		- spaecial chars	~ <- $HOME
 *			so this is another env value
 *	BEFORE EXECUTION
 *
*/

// implement an enum


#define DQUOTE '"'
#define QUOTE '''
#define BQUOTE '`'
#define SUBSH '('

#define DQUOTE_PROMPT "dquote> "
#define QUOTE_PROMPT "quote> "
#define BQUOTE_PROMPT "bquote> "
#define SUBSH_PROMPT "subsh> "

#define IS_CAPSULE (str[i] == '"' || str[i] == ''' || str[i] == '(' || str[i] == '`')


/*
**	capsule:
**		capsule[0] == DQUOTE;
**		capsule[0] == QUOTE;
**		capsule[0] == BQUOTE;
**		capsule[0] == SUBSH;
*/

char	*ft_strjoin_newline(char const *s1, char const *s2)
{
	char	*tmp;
	int		len;
	int		i;

	if (!s1 || !s2)
		return (0);
	i = -1;
	len = ft_strlen(s1) + ft_strlen(s2) + 1; // for the newline
	tmp = ft_strnew(len);
	if (!tmp)
		return (0);
	while (*s1)
		*(tmp + ++i) = *(s1++);
	tmp[++i] = '\n';
	while (*s2)
		*(tmp + ++i) = *(s2++);
	return (tmp);
}


/*
**	basically calling ft_prompt over and over again until the prompt is fully
**	complete
**	the only moment where you have to free is when you do the join thingy
**	
**	IMPORTANT
**	after you check with one type you need to check if any other type is also
**	involved so you run is capsule_incomplete in the concat string
*/
char		*concatinated_string(char type)
{
	char	*temp;
	char	*concat;
	char	*join;
	int		cont_nbr_capsule;

	temp = ft_prompt(get_type_prompt(type));
	cont_chars_capsules(temp, type, &(cont_nbr_capsule));
	while (cont_nbr_capsule % 1 == 1)
	{
		concat = ft_prompt(get_type_prompt(type));
		join = ft_strjoin_newline(temp, concat);
		free(temp);
		free(concat);
		temp = join;
		cont_chars_capsules(temp, type, &(cont_nbr_capsule));
	}
	else
		return (temp);
}

char		*get_type_prompt(char value)=
{
	if (value == DQUOTE)
		return (DQUOTE_PROMPT);
	else if (value == QUOTE)
		return (QUOTE_PROMPT);
	else if (value == BQUOTE)
		return (BQUOTE_PROMPT);
	else if (value == SUBSH)
		return (SUBSH_PROMPT);
	else
		return (NULL);
}

void		cont_chars_capsules(char *str, char schar, int *cont)
{
	int		i;

	i = 0;
	while(str[i])
	{
		if (str[i] == schar)
		{
			if (i == 0)
				*(cont)++;
			else
				if (str[i - 1] == '\'')
					;
				else
					*(cont)++;
		}
		i++;
	}
}

char		is_capsule_incomplete(char *str, char **temp)
{
	int		i;
	char	capsule[4];
	int		cont_nbr_capsule;
	char	get_capsule;
	char	*concat;

	get_capsule = 0;
	i = -1
	while(++i < 4)
		capsule[i] = 0;
	i = -1;
	cont_nbr_capsule = 0;
	while(str[i])
	{
		if (IS_CAPSULE)
		{
			get_capsule = str[i];
			cont_chars_capsules(str, get_capsule, &(cont_nbr_capsule));
			if (cont_nbr_capsule % 2 == 1)
			{
				concat = concatinated_string(get_capsule);// string to concatinate
				// find begining of capsule, and see if it has and end,
				// otherwise, find the latest 
			}
		}
		++i;
	}
}

// you will concantinate str with the new line

char		*parse_line(char *str)
{
	char	*temp;

	// this function can be a void one
	is_capsule_incomplete(str, &(temp));
	while(str[i])
	{
	}
	
	return (temp);
}



// DECIPHER BACKSLASH
//  talk to curtis and liam
//  this can be easily handle in the tokenizer

/*
char		*decipher_back_slash(char *str)
{
	char	*temp;
	int		i;

	while()
}
*/
