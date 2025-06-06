#
# simple debuggging with: gdb -x ~/workspace/ds/.gdbinit {exe}
#

set auto-load safe-path /
set listsize 40
set breakpoint pending on
set debuginfod enabled off
set cwd /root/workspace/ds

b /root/workspace/ds/include/list.hpp:78

info break
