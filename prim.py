INF = 99999

graph = [
    [0,7,14,10,2],
    [7,0,6,INF,3],
    [14,6,0,9,15],
    [10,INF,9,0,40],
    [2,3,15,40,0]
]

V = len(graph)
selected = [False] *V
selected[0] = True

num_edge = 0
total_weight = 0

while num_edge < V-1:
    min_value = INF
    x=0
    y=0

    for i in range(V):
        if selected[i]:
            for j in range(V):
                if not selected[j] and graph[i][j]:
                    if min_value > graph[i][j]:
                        min_value = graph[i][j]
                        x=i
                        y=j
    
    print (f" {x} - {y} : {graph[x][y]}")
    selected [ y ] = True
    num_edge +=1
    total_weight += graph[x][y]
    