#include "minishell.h"

char	**ft_ex_splt(char const *s, char c);

static int	ft_conut_w(char const *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			i++;
		else
		{
			count++;
			while (str[i] && str[i] != c)
				i++;
		}
	}
	return (count);
}

static char	*ft_put_word(char *word, char const *s, int i, int word_len)
{
	int	x;

	x = 0;
	while (word_len > 0)
	{
		word[x] = s[i - word_len];
		x++;
		word_len--;
	}
	word[x] = '\0';
	return (word);
}

static char	**ft_splt_w(const char *s, char c, char **sfinal,
int num_words)
{
	int	i;
	int	word;
	int	word_len;

	i = 0;
	word = 0;
	word_len = 0;
	while (word < num_words)
	{
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
		{
			i++;
			word_len++;
		}
		sfinal[word] = (char *)ft_allocate(1, sizeof(char) * (word_len + 1));
		if (!sfinal[word])
			return (NULL);
		ft_put_word(sfinal[word], s, i, word_len);
		word_len = 0;
		word++;
	}
	sfinal[word] = 0;
	return (sfinal);
}

char	**ft_ex_splt(char const *s, char c)
{
	char			**sfinal;
	unsigned int	num_words;

	if (!s)
		return (0);
	num_words = ft_conut_w(s, c);
	sfinal = (char **)ft_allocate(1, sizeof(char *) * (num_words + 1));
	if (!sfinal)
		return (0);
	sfinal = ft_splt_w(s, c, sfinal, num_words);
	return (sfinal);
}