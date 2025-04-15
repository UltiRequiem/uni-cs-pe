import sys
import heapq

def main():
    sys.setrecursionlimit(1 << 25)

    t = int(sys.stdin.readline())
    data = []
    for _ in range(t):
        n, m, q = map(int, sys.stdin.readline().split())
        edges = [[] for _ in range(n)]
        for _ in range(m):
            u, v, w = map(int, sys.stdin.readline().split())
            u -=1
            v -=1
            edges[u].append((v,w))
            edges[v].append((u,w))
        queries = []
        max_k = 0
        for _ in range(q):
            a, b, k = map(int, sys.stdin.readline().split())
            a -=1
            b -=1
            queries.append((a,b,k))
            if k > max_k:
                max_k = k
        data.append((n, edges, queries, max_k))

    for n, edges, queries, max_k in data:
        dist = [ [None] * n for _ in range(n)]  
        for s in range(n):
            dist_s = [None] * n
            dist_s[s] = []
            heap = []
            heapq.heappush(heap, (tuple(dist_s[s]), s))
            while heap:
                seq_u, u = heapq.heappop(heap)
                seq_u = list(seq_u)
                if dist_s[u] != seq_u:
                    continue
                for v, w in edges[u]:
                    seq_v_new = insert_w(seq_u, w, max_k)
                    if dist_s[v] is None or compare_sequences(seq_v_new, dist_s[v]) < 0:
                        dist_s[v] = seq_v_new
                        heapq.heappush(heap, (tuple(dist_s[v]), v))
            dist[s] = dist_s

            
        for a, b, k in queries:
            seq = dist[a][b]
            if seq is None or len(seq) < k:
                print(-1, end=' ')
            else:
                print(seq[k-1], end=' ')
        print()

def insert_w(seq_u, w, max_k):
    seq_v_new = []
    inserted = False
    idx_u = 0
    while idx_u < len(seq_u) and len(seq_v_new) < max_k:
        if not inserted and seq_u[idx_u] < w:
            seq_v_new.append(w)
            inserted = True
            if len(seq_v_new) == max_k:
                break
        seq_v_new.append(seq_u[idx_u])
        idx_u += 1
    if not inserted and len(seq_v_new) < max_k:
        seq_v_new.append(w)
    return seq_v_new[:max_k]

def compare_sequences(seq1, seq2):
    n = min(len(seq1), len(seq2))
    for i in range(n):
        if seq1[i] != seq2[i]:
            return seq1[i] - seq2[i]
    return len(seq1) - len(seq2)

main()
