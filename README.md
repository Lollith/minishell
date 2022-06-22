# Minishell
School 42 project.

The goal of this project is to create a minimalist shell.

This will be a little copy of bash.

### Authors
- [@Lollith](https://www.github.com/Lollith)
- [@LolinEagle](https://www.github.com/LolinEagle)

### Deployment
To deploy this project run
```bash
git clone --recurse-submodules https://github.com/Lollith/minishell.git &&
cd minishell && make && ./minishell
```

### Related
Here are some related projects

[Submodule libft](https://github.com/LolinEagle/libft)

[pipex](https://github.com/Lollith/pipex.git)

### Test
```bash
/bin/ls "|" /usr/bin/grep minishell ";" /bin/echo i love my minishell
mkdir a ; cd a ; rm -rf ../a
ls $HOME/Desktop
cat Makefile | ./minishell
env -i ./minishell
export A=" coucou " ; echo "$A"
export A=" coucou " ; echo $A$A
export A=' mdr' ; echo @$A@
export A='mdr ' ; echo @$A@
export A=' mdr ' ; echo @$A@
echo -n a '' b '' c '' d
e"ch"o bonjour
echo\ bonjour
echo $ejknfenf hey
echo "$ejnzefc" hey
```
