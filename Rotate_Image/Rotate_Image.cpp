// Rotate_Image.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vector>
#include <assert.h>

using namespace std;

class Solution {
public:
    void rotate(vector<vector<int> > &matrix) {
        swapTopDown(matrix);
        swapDiag(matrix);
    }

private:
    void swapTopDown(vector<vector<int> > &matrix){
        int n = matrix.size();
        int i = 0, j = n - 1;
        while (i < j){
            for (int k = 0; k < n; ++k)
                swap(matrix[i][k], matrix[j][k]);
            ++i; --j;
        }
    }

    void swapDiag(vector<vector<int> > &matrix){
        int n = matrix.size();
        for (int i = 0; i < n; ++i){
            for (int j = 0; j < i; ++j)
                swap(matrix[i][j], matrix[j][i]);
        }
    }
};


int _tmain(int argc, _TCHAR* argv[])
{
    vector<int> singleLine;
    vector<vector<int>> matrix;
    singleLine.push_back(1);
    singleLine.push_back(2);
    singleLine.push_back(3);
    singleLine.push_back(4);
    matrix.push_back(singleLine);
    singleLine.clear();
    singleLine.push_back(5);
    singleLine.push_back(6);
    singleLine.push_back(7);
    singleLine.push_back(8);
    matrix.push_back(singleLine); 
    singleLine.clear();
    singleLine.push_back(9);
    singleLine.push_back(10);
    singleLine.push_back(11);
    singleLine.push_back(12);
    matrix.push_back(singleLine);
    singleLine.clear();
    singleLine.push_back(13);
    singleLine.push_back(14);
    singleLine.push_back(15);
    singleLine.push_back(16);
    matrix.push_back(singleLine);
    singleLine.clear();
 

    Solution    so;
    so.rotate(matrix);

	return 0;
}

