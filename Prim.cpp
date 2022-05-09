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

vector < pair<int, int> > adj[MAX]; // 인접리스트 배열생성 (0번 idx 사용 x)
int N, M, Q;

struct Node{
	int src, dest, cost;
};

/* prim 알고리즘
 start 노드를 입력으로 받고, 비용의 총합을 출력
 path 벡터를 입력으로 받은뒤 경로정보 저장
*/
int prim(int start, vector<int> &path) {
	path.clear(); // start를 변경할때 마다 path가 변하므로 초기화  

	vector<int> Dist(MAX, INF); // 초기에 모든 거리를 무한대로 초기화
	vector<int> Unseen(MAX, UNSEEN); // 모든 정점을 unseen으로 초기화

	Dist[start] = 0; // 자기자신과의 거리는 0으로 설정
	Unseen[start] = TREE; // start는 tree를 unseen -> tree vertices로 변경

	int ans = 0; // 함수에서 반환할 비용의 총합

	// start를 path에 추가
	path.push_back(start);

	// start 정점을 기준으로 인접한 정점들을 fringe에 추가
	for (int i = 0; i < adj[start].size(); i++) {
		int next = adj[start][i].DEST;
		int cost = adj[start][i].COST;
		Dist[next] = cost;
		Unseen[next] = FRINGE;
	}

	/* fringe 노드중에서 최소값 찾기 
	unsroted array를 이용하므로 모든 fringe node를 탐색하며 최소값을 찾아야함
	*/
	for (int i = 1; i <= N-1; i++) {
		int min = INF; // 최소값을 무한대로 초기화
		int cur = -1; // 현재 최소값을 저장하고 있는 idx, -1로 초기화
		for (int j = 1; j <= N; j++) {
			if (Unseen[j] == FRINGE) { // FRINGE 노드탐색
				if (min > Dist[j]) { // 더 작은 최소값을 찾으면
					min = Dist[j]; // 최소값 갱신
					cur = j; // 최소값 저장 idx 갱신
				}
			}
		}

		// path에 cur 정점 추가
		path.push_back(cur);
		

		Unseen[cur] = TREE; // 최소 값을 TREE vertices에 추가
		ans += min; // total cost 갱신

		
		if (cur != -1) {
			/*  Decrease KEY 구현
		 새로 tree vertieces가 된 cur 정점의 인접한 정점들을 fringe에 추가한다.
		 추가 시 이미 tree vertices라면 넘어가고, unseen인 경우엔 바로 추가
		 이미 fringe에 있는 경우 기존 값보다 작다면 작은 값으로 갱신
		*/
			for (int j = 0; j < adj[cur].size(); j++) {
				int next = adj[cur][j].DEST;
				int cost = adj[cur][j].COST;

				// 이미 tree vertices라면 continue
				if (Unseen[next] == TREE) continue;
				// UNSEEN인 경우엔 FRINGE에 추가
				if (Unseen[next] == UNSEEN) {
					Dist[next] = cost;
					Unseen[next] = FRINGE;
					continue;
				}
				// fringe에 이미 있는경우 
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
		// 인접리스트에 시작점, 출발점, 비용 정보 입력
		// 무향 그래프이므로 시작,출발 && 출발,시작 2번 삽입
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