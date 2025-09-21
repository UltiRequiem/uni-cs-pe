from collections import Counter

t = int(input())

for _ in range(t):
    n, k = map(int, input().split())
    a = list(map(int, input().split()))
    

    freq = Counter(a)
    
    freq_list = sorted(freq.values(), reverse=True)
    
    prefix_sums = [0]

    for f in freq_list:
        prefix_sums.append(prefix_sums[-1] + f)
    
    n_unique = len(freq_list)
    min_fa = n_unique
    
    for u in range(1, n_unique + 1):
        total_changes = n - prefix_sums[u]
        if total_changes <= k:
            min_fa = u
            break  
    
    print(min_fa)
