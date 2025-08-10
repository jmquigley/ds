#
# simple debuggging with: gdb -x ~/workspace/ds/.gdbinit {exe}
#

set listsize 40
set breakpoint pending on
set cwd /root/workspace/ds
set debuginfod enabled off
set python print-stack full
# set print elements 0
set max-value-size unlimited
tui disable
# dashboard -enabled off

# b /root/workspace/ds/src/ds/SortedList.hpp:128
# b /root/workspace/ds/tests/test_sortedlist.cpp:192
# b /root/workspace/ds/tests/test_generaltreenode.cpp:16
# b /root/workspace/ds/src/ds/GeneralTreeNode.hpp:197
# b /root/workspace/ds/src/ds/List.hpp:410
# b /root/workspace/ds/src/ds/List.hpp:355
# b /root/workspace/ds/src/ds/GeneralTree.hpp:insert
# b /root/workspace/ds/src/ds/GeneralTree.hpp:breadth
b /root/workspace/ds/tests/test_bitflag.cpp:63
# b /root/workspace/ds/src/ds/GeneralTree.hpp:depth
# b /root/workspace/ds/src/ds/BinaryTree.hpp:removeValue
# b /root/workspace/ds/tests/test_binarytree.cpp:138
# b /root/workspace/ds/src/ds/binarytree.hpp:insert
# b /root/workspace/ds/src/ds/binarytree.hpp:insertDelegate
# b /root/workspace/ds/src/ds/binarytree.hpp:insertFixUp

info break
