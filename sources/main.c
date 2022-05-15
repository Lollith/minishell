
#include "minishell.h"


	int main()
    {
      static  char *line = NULL;
      if (line)
      {
          free(line);
          line = NULL;
      }
        line = readline("test> ");
        if(line && *line)
         add_history (line);
        printf( "%s\n", line);

        return 0;
    }
