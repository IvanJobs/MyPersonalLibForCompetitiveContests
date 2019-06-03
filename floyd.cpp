#include <bits/stdc++.h>

using namespace std;

int f[110][110][110];
int w[110][110]; // w[i][j] => (A, B, C) => (i, j, w[i][j])

int main() {
  int N, M;
  while(true) {
    cin>>N>>M;
    if (N == 0 && M == 0) break;
    
    for (int i = 1; i <= N; i++) {
      for (int j = 1; j <= N; j++) {
        if (i == j) {
          w[i][j] = 0;
        } else {
          w[i][j] = 20000000;
        }
      }
    }

    for (int i = 0; i < M; i++) {
      int A, B, C;
      cin>>A>>B>>C;
      w[A][B] = C;
      w[B][A] = C;
    }
    
    // init f[*][*][0]
    for (int i = 1; i <= N; i++) {
      for (int j = 1; j <= N; j++) {
        f[i][j][0] = w[i][j];
      }
    }

    // calculate k from 1 to N;
    for (int k = 1; k <= N; k++) {
      for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
          // f[i][j][k]
          int candidate1 = f[i][j][k - 1];
          int candidate2 = f[i][k][k - 1] + f[k][j][k - 1];
          f[i][j][k] = min(candidate1, candidate2); 
        }
      }
    }

    cout<<f[1][N][N]<<endl;
  }
  return 0;
}
