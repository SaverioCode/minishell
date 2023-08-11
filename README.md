This is a didactic project that I made for 42 School.

The project has been tested on Debian 11 (bullseye) and MacOS 10.?
In order to run the project 'readline' is requested. Two options are aviable:
  - installing readline
  - downloading readline and renaming the folder as 'readline', after that move it to minishell/include/.
    The first compilation of the program has to be done with 'make config', after that you can just use 'make'

Minishell, as the name suggest, is a reproduction of a simple shell, emulating bash.
For this project the following features have been implemented:
      - '<' '<<' '>' '>>'
      - '&&' '||' '|'
      - '()' (subshell)
      - single and souble quotes
      - $0 and $var_name
      - built in commands(some with limited features): echo, env, export, unset, cd, pwd, exit

As wrote before bash shell as been taken as model, then for the use of the program just refere to bash

Enjoy my minishell!
