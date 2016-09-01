/**
 * Definition for binary tree with next pointer.
 * public class TreeLinkNode {
 *     int val;
 *     TreeLinkNode left, right, next;
 *     TreeLinkNode(int x) { val = x; }
 * }
 */
public class Solution {
    public void connect(TreeLinkNode root) {
        TreeLinkNode anchor;
        for (; root != null; root = root.left) {
            for (anchor = root;  anchor != null; anchor = anchor.next) {
                if (anchor.left != null) {
                    anchor.left.next = anchor.right;
                    if (anchor.next == null) {
                        break;
                    }
                    anchor.right.next = anchor.next.left;
                }
            }
        }
        return;
    }
}
