#include "../includes/minishell.h"

int first_check_1(char *line, t_shell *sh)
{
  int i;

  i = 0;
  while (line[i])
  {
    // puts("here");
    if ((line[i] == '<' && line[i + 1] == '<') || (line[i] == '<' && line[i + 1] == '<' && line[i + 2] == '<'))
    {
      write(1, "Error:Syntax error\n", 20);
      return (1);
    }
    else if ((line[i] == '>' && line[i + 1] == '>' && line[i + 2] == '>'))
    {
      write(1, "Error:Syntax error\n", 20);
      return (1);
    }
    else if (line[i] == '>' && line[i + 1] == '>')
    {
      // puts(&line[i]);
      i = i + 2;
      while (line[i] == ' ' || line[i] == '\t')
        i++;
      if (line[i] == '\n' || line[i] == '\0')
      {
        write(1, "Error:Syntax error\n", 20);
        return (1);
      }
    }
    else if (line[i] == '>' || line[i] == '<')
    {
      i++;
      while (line[i] == ' ' || line[i] == '\t')
        i++;
      if (line[i] == '\n' || line[i] == '\0')
      {
        write(1, "Error:Syntax error\n", 20);
        return (1);
      }
    }
    i++;
  }
  return (0);
}

int first_check(char *line, t_shell *sh)
{
  int i;

  i = 0;
  if (line[0] == '|')
  {
    write(1, "Syntax error near unexpected token Pipe\n", 41);
    return (1);
  }
  else if (line[0] == ';')
  {
    write(1, "Syntax error near unexpected token semicomma\n", 46);
    return (1);
  }
  else if ((line[0] == '\'' || line[0] == '\"') && ((line[1] == '<' || line[1] == '>' || (line[1] == '>' && line[2] == '>'))))
  {
    write(1, "Error:Syntax error\n", 20);
    return (1);
  }
  else
  {
    while ((line[i] == ' ' || line[i] == '\t') && line[i])
      i++;
    if (line[i] == '|')
    {
      write(1, "Syntax error near unexpected token Pipe\n", 41);
      return (1);
    }
    else if (line[i] == ';')
    {
      write(1, "Syntax error near unexpected token semicomma\n", 46);
      return (1);
    }
    else
      return (0);
  }
}

int second_check(char *line, t_shell *sh)
{
  int i;

  i = 0;
  while (line[i] != ';' && line[i] != '|' && line[i] != '\"' && line[i] != '\'' && line[i])
    i++;
  if (line[i] == '\"')
    i = dbl_quote(line, i + 1) + 1;
  if (line[i] == '\'')
    i = spl_quote(line, i + 1) + 1;
  if ((line[i] == ';' || line[i] == '|') && line[i])
  {
    i++;
    while ((line[i] == ' ' || line[i] == '\t') && line[i])
      i++;
    if (line[i] == ';' || line[i] == '|')
    {
      write(1, "Error:Syntax error\n", 20);
      return (1);
    }
    // else if (line[i + 1] == ' ')
    // {
    //   while ((line[i++] == ' ' || line[i + 1] == '\t') && line[i])
    //     i++;
    //   if ((line[i + 1] == ';' || line[i + 1] == '|') && line[i])
    //   {
    //     write(1, "Error:Syntax error\n", 20);
    //     return (1);
    //   }
    // }
  }
  return (0);
}

int check_0(char *line, t_shell *sh)
{
  int i;

  i = 0;
  while (((line[i] != '<' && line[i] != '>')) && line[i])
    i++;
  if ((line[i] == '>' && line[i + 1] == '>'))
    i = i + 2;
  else if ((line[i] == '>' || line[i] == '<'))
    i++;
  while ((line[i] == ' ' || line[i] == '\t') && line[i])
    i++;
  if (line[i] == ';' || line[i] == '|')
  {
    write(1, "syntax error\n", 14);
    return (1);
  }
  else
    return (0);
}
int check_1(char *line)
{
  int i = 0;

  while (line[i])
  {
    if (line[i] == '>' && line[i + 1] != '>')
    {
      i++;
      while ((line[i] == ' ' || line[i] == '\t') && line[i])
        i++;
      if (line[i] == '<')
      {
        write(1, "syntax error\n", 14);
        return (1);
      }
      else if (line[i] == '>')
      {
        write(1, "syntax error\n", 14);
        return (1);
      }
      else if (line[i] == ' ')
      {
        while (line[i] == ' ')
          i++;
        if (line[i] == '<')
        {
          write(1, "syntax error\n", 14);
          return (1);
        }
      }
    }
    else if (line[i] == '<')
    {
      i++;
      while ((line[i] == ' ' || line[i] == '\t') && line[i])
        i++;
      if (line[i] == '>' || line[i] == '<')
      {
        write(1, "syntax error\n", 14);
        return (1);
      }
      else if (line[i] == ' ')
      {
        while (line[i] == ' ')
          i++;
        if (line[i] == '>' || line[i] == '<')
        {
          write(1, "syntax error\n", 14);
          return (1);
        }
      }
    }
    else if (line[i] == '>' && line[i + 1] == '>')
    {
      i = i + 2;
      while ((line[i] == ' ' || line[i] == '\t') && line[i])
        i++;
      if (line[i] == '>' || line[i] == '<')
      {
        write(1, "syntax error\n", 14);
        return (1);
      }
    }
    i++;
  }
  return (0);
}

int quote_nbr(char *line, t_shell *sh)
{
  int i;
  int j;
  int k;
  int u;

  i = 0;
  j = 0;
  k = 0;
  u = 0;
  while (line[i] != '\0')
  {

    if (line[i] == '\\' && line[i + 1] != '\n')
    {
      u = 0;
      while (line[i] == '\\')
      {
        u++;
        i++;
      }
      if (u % 2 != 0)
      {
        if (line[i] == '\n')
        {
          write(1, "Error:Syntax error\n", 20);
          return 1;
        }
        else
          i++;
      }
      else if (u % 2 == 0)
        continue;
    }
    else if (line[i] == '\"')
    {
      j++;
      i = dbl_quote(line, i + 1) + 1;
      if (i > 1)
        j++;
      else
        break;
    }
    else if (line[i] == '\'')
    {
      k++;
      i = spl_quote(line, i + 1) + 1;
      if (i > 1)
        k++;
      else
        break;
    }
    else if ((line[i] == '$' && line[i + 1] == '\\' && line[i + 2] == '\n') || (line[i] == '\\' && line[i + 1] == '\n'))
    {
      write(1, "Error:Syntax error\n", 20);
      return 1;
    }
    else
      i++;
  }

  if (j % 2 != 0 || k % 2 != 0)
  {
    // puts("here");
    write(1, "Error:Syntax error\n", 20);
    return 1;
  }

  return (0);
}

void check_line_error(char *line, t_shell *sh)
{

  if (quote_nbr(line, sh) == 1 || first_check(line, sh) == 1 || first_check_1(line, sh) == 1 || second_check(line, sh) == 1)
  {
    sh->error = 1;
  }
  if (sh->error == 0 && search(line) == 1)
  {
    if (check_0(line, sh) == 1 || check_1(line) == 1)
      sh->error = 1;
  }
}

//  ls <
//  ls ;   ; pwd
//  s |      |       pwd
//  ls > *
//  ls > >
//  ls >><pwd