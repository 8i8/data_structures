/*
 * add()
 * getMin()
 * isEmpty()
 * print()
 * contains()
 * printSideways()
 * remove()
 *
 * 4 cases to consider for removing a leaf:
 *
 * 1) a leaf - jsut use null and remove.
 * 2) left child only, replace with left child
 * 3) right child only, replace with right child.
 * 4) two childred, move up the least most (deepest left) inner right child,
 * or, the maximum value from the left side.
 */
