#include <iostream>
#include <vector>
#define INF 2100000000
#define MAX 10001
#define DEST first
#define COST second
#define UNSEEN	0
#define FRINGE	1
#define TREE	2
using namespace std;

vector < pair<int, int> > adj[MAX]; // ��������Ʈ �迭���� (0�� idx ��� x)
int N, M, Q;

struct Node{
	int src, dest, cost;
};

/* prim �˰���
 start ��带 �Է����� �ް�, ����� ������ ���
 path ���͸� �Է����� ������ ������� ����
*/
int prim(int start, vector<int> &path) {
	path.clear(); // start�� �����Ҷ� ���� path�� ���ϹǷ� �ʱ�ȭ  

	vector<int> Dist(MAX, INF); // �ʱ⿡ ��� �Ÿ��� ���Ѵ�� �ʱ�ȭ
	vector<int> Unseen(MAX, UNSEEN); // ��� ������ unseen���� �ʱ�ȭ

	Dist[start] = 0; // �ڱ��ڽŰ��� �Ÿ��� 0���� ����
	Unseen[start] = TREE; // start�� tree�� unseen -> tree vertices�� ����

	int ans = 0; // �Լ����� ��ȯ�� ����� ����

	// start�� path�� �߰�
	path.push_back(start);

	// start ������ �������� ������ �������� fringe�� �߰�
	for (int i = 0; i < adj[start].size(); i++) {
		int next = adj[start][i].DEST;
		int cost = adj[start][i].COST;
		Dist[next] = cost;
		Unseen[next] = FRINGE;
	}

	/* fringe ����߿��� �ּҰ� ã�� 
	unsroted array�� �̿��ϹǷ� ��� fringe node�� Ž���ϸ� �ּҰ��� ã�ƾ���
	*/
	for (int i = 1; i <= N-1; i++) {
		int min = INF; // �ּҰ��� ���Ѵ�� �ʱ�ȭ
		int cur = -1; // ���� �ּҰ��� �����ϰ� �ִ� idx, -1�� �ʱ�ȭ
		for (int j = 1; j <= N; j++) {
			if (Unseen[j] == FRINGE) { // FRINGE ���Ž��
				if (min > Dist[j]) { // �� ���� �ּҰ��� ã����
					min = Dist[j]; // �ּҰ� ����
					cur = j; // �ּҰ� ���� idx ����
				}
			}
		}

		// path�� cur ���� �߰�
		path.push_back(cur);
		

		Unseen[cur] = TREE; // �ּ� ���� TREE vertices�� �߰�
		ans += min; // total cost ����

		
		if (cur != -1) {
			/*  Decrease KEY ����
		 ���� tree vertieces�� �� cur ������ ������ �������� fringe�� �߰��Ѵ�.
		 �߰� �� �̹� tree vertices��� �Ѿ��, unseen�� ��쿣 �ٷ� �߰�
		 �̹� fringe�� �ִ� ��� ���� ������ �۴ٸ� ���� ������ ����
		*/
			for (int j = 0; j < adj[cur].size(); j++) {
				int next = adj[cur][j].DEST;
				int cost = adj[cur][j].COST;

				// �̹� tree vertices��� continue
				if (Unseen[next] == TREE) continue;
				// UNSEEN�� ��쿣 FRINGE�� �߰�
				if (Unseen[next] == UNSEEN) {
					Dist[next] = cost;
					Unseen[next] = FRINGE;
					continue;
				}
				// fringe�� �̹� �ִ°�� 
				if (Dist[next] > cost) Dist[next] = cost;
			}
		}
		

	}
	return ans;

}


int main() {
	cin >> N >> M >> Q;

	for (int i = 0; i < M; i++) {
		int src, dest, cost;
		cin >> src >> dest >> cost;
		// ��������Ʈ�� ������, �����, ��� ���� �Է�
		// ���� �׷����̹Ƿ� ����,��� && ���,���� 2�� ����
		adj[src].push_back(make_pair(dest, cost));
		adj[dest].push_back(make_pair(src, cost));
	}
	
	for (int i = 0; i < Q; i++) {
		char x;
		cin >> x;
		if (x == 'P') {
			int s;
			cin >> s;
			vector<int> p;
			cout << prim(s, p);
			for (int i = 0; i < p.size(); i++) {
				cout << " " << p[i];
			}
			cout << "\n";
		}
	}
}