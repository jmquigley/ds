#
# simple debuggging with: gdb -x ~/workspace/ds/.gdbinit {exe}
#

set listsize 40
set breakpoint pending on
set cwd /root/workspace/ds
set debuginfod enabled off

b /root/workspace/ds/src/BinaryTree.hpp:removeValue
# b /root/workspace/ds/tests/test_binarytree.cpp:25
# b /root/workspace/ds/src/binarytree.hpp:insert
# b /root/workspace/ds/src/binarytree.hpp:insertDelegate
# b /root/workspace/ds/src/binarytree.hpp:insertFixUp

info break
