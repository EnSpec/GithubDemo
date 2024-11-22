#include <stdio.h>
#include <stdlib.h>
//#include <math.h>

void cumulative_sum(int *lst, int n, int *csum) {
    csum[0] = 0;
    for (int i = 1; i <= n; i++) {
        csum[i] = csum[i - 1] + lst[i - 1];
    }
}

void calculate_sump_matrix(int *lst, int n, int **result) {
    int *csum = (int *)malloc((n + 1) * sizeof(int));
    cumulative_sum(lst, n, csum);

    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            result[i][j] = csum[j + 1] - csum[i];
        }
    }

    free(csum);
}

int DP(int n, int *list_p) {
    int **R = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        R[i] = (int *)calloc(n, sizeof(int));
    }

    for (int i = 0; i < n - 1; i++) {
        R[i][i + 1] = list_p[i] < list_p[i + 1] ? list_p[i] : list_p[i + 1];
    }

    int **sump_matrix = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        sump_matrix[i] = (int *)malloc(n * sizeof(int));
    }

    calculate_sump_matrix(list_p, n, sump_matrix);

    for (int offset = 2; offset < n; offset++) {
        for (int i = 0; i < n - offset; i++) {
            int j = i + offset;
            int left_k = i;
            int right_k = j - 1;

            while (left_k < right_k - 1) {
                int mid_k = (left_k + right_k) / 2;
                int left_value = sump_matrix[i][mid_k] + R[i][mid_k];
                int right_value = sump_matrix[mid_k + 1][j] + R[mid_k + 1][j];

                if (left_value > right_value) {
                    right_k = mid_k;
                } else {
                    left_k = mid_k;
                }
            }

            int tmp1 = sump_matrix[left_k + 1][j] + R[left_k + 1][j];
            if (sump_matrix[i][left_k] + R[i][left_k] < tmp1) {
                tmp1 = sump_matrix[i][left_k] + R[i][left_k];
            }

            int tmp2 = sump_matrix[right_k + 1][j] + R[right_k + 1][j];
            if (sump_matrix[i][right_k] + R[i][right_k] < tmp2) {
                tmp2 = sump_matrix[i][right_k] + R[i][right_k];
            }

            R[i][j] = tmp1 > tmp2 ? tmp1 : tmp2;
        }
    }

    int result = R[0][n - 1];

    for (int i = 0; i < n; i++) {
        free(R[i]);
        free(sump_matrix[i]);
    }
    free(R);
    free(sump_matrix);

    return result;
}

int main() {
    int n;
    scanf("%d", &n);

    int *list_p = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &list_p[i]);
    }

    printf("%d\n", DP(n, list_p));

    free(list_p);
    return 0;
}
