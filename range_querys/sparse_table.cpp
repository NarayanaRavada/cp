const int MAXN = 1e6;
const int K = 25;
int Log[MAXN + 1];
int st[K + 1][MAXN + 1];

void compute_log() {
    Log[1] = 0;
    for (int i = 2; i <= MAXN; i++) {
        Log[i] = Log[i / 2] + 1;
    }
}

int f(int a, int b) {
    return a + b;
}

int get(int L, int R) {
    int res = 0;
    for (int i = K; i >= 0; i--) {
        if ((1 << i) <= R - L + 1) {
            res = f(res, st[i][L]);
            L += 1 << i;
        }
    }
    return res;
}

/* function is `idempotenet` { a & b & b & b = a & b }
 * min, max, gcd, &, .... query takes O(1)
 */
int get_eff(int L, int R) {
    int i = Log[R - L + 1];
    return f(st[i][L], st[i][R - (1 << i) + 1]);
}

void sparse_table(vector<int> &arr) {
    int N = arr.size();
    copy(all(arr), st[0]);
    for (int i = 1; i <= K; i++) {
        for (int j = 0; j + (1 << i) <= N; j++) {
            st[i][j] = f(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
        }
    }
}
