readline
rl_clear_history
rl_on_new_line
rl_replace_line
rl_redisplay
add_history

ls -a < file | grep -p | wc -l

        __PIPE___
       /         \
    CMD          PIPE
    / \          /  \
  file -a       -p   -l
  /     \      /      \
 <       ls  grep     wc
