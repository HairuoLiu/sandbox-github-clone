import java.util.*;

public class Solution {
    public int singleNumber(int[] A) {
        return Arrays.stream(A).reduce(0, (x, y) -> x^y);
    }

    public static void main(String[] args) {
        Solution s = new Solution();
        int A[] = {1, 2, 2, 3, 1};
        int result = s.singleNumber(A);
        System.out.println(result);
    }
}
