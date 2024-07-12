#include "../minishell.h"

t_cmd_field *create_field(char *input_str, int type)
{
	t_cmd_field *field;

	field = (t_cmd_field *)malloc(sizeof(t_cmd_field));
	// if (!field->value)
	// 	return (free_tok(field), exit(1), NULL); //handle exit in error.c
	field->length = ft_strlen(input_str);
	field->value = (char *)malloc((field->length + 1) * sizeof(char));
	// if (field->value == NULL)
	// 	return (free_tok(field), exit(1), NULL); //handle exit
	ft_strlcpy(field->value, input_str, field->length + 1);
    field->type = type;
	field->next = NULL;
	field->prev = NULL;
	if (type == TO_FILE)
		field->P = 1;
    if (type == TO_TO_FILE)
		field->P = 2;
    if (type == FROM_FILE)
		field->P = 0;
	return (field);
}