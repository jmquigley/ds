#
# simple debuggging with: gdb -x ~/workspace/ds/.gdbinit {exe}
#

set listsize 40
set breakpoint pending on
set cwd /root/workspace/ds
set debuginfod enabled off

b /root/workspace/ds/src/ds/helpers.hpp:107
b /root/workspace/ds/tests/test_list.cpp:481
# b /root/workspace/ds/tests/test_generaltreenode.cpp:16
# b /root/workspace/ds/src/ds/GeneralTreeNode.hpp:241
b /root/workspace/ds/src/ds/List.hpp:406
# b /root/workspace/ds/src/ds/GeneralTree.hpp:insert
# b /root/workspace/ds/src/ds/GeneralTree.hpp:breadth
# b /root/workspace/ds/tests/test_list.cpp:34
# b /root/workspace/ds/src/ds/GeneralTree.hpp:depth
# b /root/workspace/ds/src/ds/BinaryTree.hpp:removeValue
# b /root/workspace/ds/tests/test_binarytree.cpp:138
# b /root/workspace/ds/src/ds/binarytree.hpp:insert
# b /root/workspace/ds/src/ds/binarytree.hpp:insertDelegate
# b /root/workspace/ds/src/ds/binarytree.hpp:insertFixUp

info break
