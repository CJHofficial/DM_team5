#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

struct QD {
    int a, b, w, d; //Edge : a ->b  Weight : w source부터 거리 : d
};

class PQ {
private:
    QD Arr[1000];
    int cnt;
public:
    PQ();
    void Insert(QD x);
    QD Delete();

};

PQ::PQ()
{
    this->cnt = 0;
}

void PQ::Insert(QD x)
{
    int i;
    QD temp;
    Arr[++cnt] = x;
    i = cnt;
    while (i > 1) {
        if (Arr[i].d < Arr[i / 2].d) {
            temp = Arr[i]; Arr[i] = Arr[i / 2]; Arr[i / 2] = temp;
            i = i / 2;
        }
        else
            break;
    }
    return;
}

QD PQ::Delete()
{
    QD ret, temp;
    int i;

    ret = Arr[1];
    if (cnt == 1) {
        cnt = 0;
    }
    else {
        Arr[1] = Arr[cnt]; cnt--;
        i = 1;
        while (true) {
            if (cnt >= i * 2 + 1) {
                if (Arr[i].d > Arr[i * 2].d || Arr[i].d > Arr[i * 2 + 1].d) {
                    if (Arr[i * 2].d < Arr[i * 2 + 1].d) {
                        temp = Arr[i]; Arr[i] = Arr[i * 2]; Arr[i * 2] = temp;
                        i = i * 2;
                    }
                    else {
                        temp = Arr[i]; Arr[i] = Arr[i * 2 + 1]; Arr[i * 2 + 1] = temp;
                        i = i * 2 + 1;
                    }
                }
                else {
                    break;
                }
            }
            else if (cnt == i * 2) {
                if (Arr[i].d > Arr[i * 2].d) {
                    temp = Arr[i]; Arr[i] = Arr[i * 2]; Arr[i * 2] = temp;
                    i = i * 2;
                }
                else {
                    break;
                }
            }
            else {
                break;
            }
        }
    }
    return ret;
}


int main() {

    PQ Q;
    pair<int, int> temp;
    QD t1, t2;
    vector<pair<int, int>> Edge[1000];
    int Mark[1000]; //distance
    int n, m, i, j, s, t, w, oi;    //round 몇 번 
    scanf("%d %d", &n, &m);
    for (i = 0; i < m; i++) {
        scanf("%d %d %d", &s, &t, &w);
        temp.first = t; temp.second = w;
        Edge[s].push_back(temp);    // s => source 시작하는 노드 t => 연결된 노드 w => Weigth
        temp.first = s; temp.second = w;
        Edge[t].push_back(temp);
    }

    for (i = 1; i <= n; i++) Mark[i] = 1000000;    //infinity
    Mark[1] = 0;    //source

    for (j = 0; j < Edge[1].size(); j++) {
        t1.a = 1;
        t1.b = Edge[1][j].first;
        t1.w = Edge[1][j].second;
        t1.d = Mark[1] + Edge[1][j].second;
        Q.Insert(t1);
    }
    printf("\n"); printf("\n"); printf("\n");
    oi = 1;

    while (oi < n) {
        t1 = Q.Delete();    //a b w d

        if (Mark[t1.b] == 1000000) {
            printf("%d ", t1.b);
            oi++;
            Mark[t1.b] = t1.d;
            for (j = 0; j < Edge[t1.b].size(); j++) {
                t2.a = t1.b;
                t2.b = Edge[t1.b][j].first;
                t2.w = Edge[t1.b][j].second;
                t2.d = Mark[t1.b] + Edge[t1.b][j].second;
                Q.Insert(t2);
            }
        }
    }

    printf("\n"); printf("\n"); printf("\n");
    for (i = 1; i <= n; i++) {
        printf("%d ", Mark[i]);
    }
    printf("\n");

    return 0;
}

/*
4 5
1 2 3
2 3 2
3 4 4
4 1 1
2 4 5

5 10
1 2 10
1 4 5
1 5 6
2 3 1
2 4 3
2 4 4
3 4 2
3 5 4
3 5 6
4 5 2

4 6
1 2 1
1 3 2
2 3 2
1 4 5
2 4 6
3 4 7
*/