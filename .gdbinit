#
# simple debuggging with: gdb -x ~/workspace/ds/.gdbinit {exe}
#

set listsize 40
set breakpoint pending on
set cwd /root/workspace/ds
set debuginfod enabled off

b /root/workspace/ds/tests/test_generaltreenode.cpp:15
b /root/workspace/ds/src/ds/GeneralTreeNode.hpp:addChild
# b /root/workspace/ds/src/ds/BinaryTree.hpp:removeValue
# b /root/workspace/ds/tests/test_binarytree.cpp:138
# b /root/workspace/ds/src/ds/binarytree.hpp:insert
# b /root/workspace/ds/src/ds/binarytree.hpp:insertDelegate
# b /root/workspace/ds/src/ds/binarytree.hpp:insertFixUp

info break
