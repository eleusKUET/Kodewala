#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> find_cofactor(vector<vector<int>> a, int r, int c)
{
    vector<vector<int>> mat;
    int n = a.size();
    for (int i = 0; i < n; i++) {
        vector<int> row;
        if (r == i) continue;
        for (int j = 0; j < n; j++) {
            if (j == c) continue;
            row.push_back(a[i][j]);
        }
        mat.push_back(row);
    }
    return mat;
}

int determinant(vector<vector<int>> a)
{
    if (a.size() == 1) {
        return a[0][0];
    }
    int n = a.size();
    int sign = +1;
    int det = 0;
    for (int i = 0; i < n; i++) {
        vector<vector<int>> cf_mat = find_cofactor(a, 0, i);
        int cofactor = determinant(cf_mat);
        det += cofactor * sign * a[0][i];
        sign = -sign;
    }
    return det;
}

signed main()
{
    vector<vector<int>> mat = {
        {2, -3, 1},
        {2, 0, -1},
        {1, 4, 5}
    };

    int det = determinant(mat);

    cout << det << "\n";
}