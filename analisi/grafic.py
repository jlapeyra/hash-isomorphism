import matplotlib.pyplot as plt
import glob
from collections import Counter

def parsenum(s:str) -> int|float|str:
    s = s.strip()
    try: return int(s)
    except:
        try: return float(s)
        except: return s

def open_files(*paths:tuple[str]):
    for path in paths:
        with open(path) as file:
            yield from file


#with open('hash_groups_sparse.out.txt') as f:
#with open('kk.out.txt', 'w') as file:
for path in glob.glob('analisi/*.out.txt'):
    #points = []
    anomalies = []
    num_experiments = 0
    for line in open_files(path):
        if line.strip() and line.split()[0].isnumeric():
            num_experiments += 1
            graph, groups, _ = line.split('|')
            num_vtx, edge_density, num_edges = map(parsenum, graph.split(':'))
            groups = list(map(parsenum, groups.split(',')))

            unary_groups:bool = max(groups) == num_vtx
            num_iterations = groups.index(max(groups))
            densitat = num_edges/(num_vtx*(num_vtx-1)/2)
            for i in range(len(groups)-1):
                if groups[i+1] < groups[i]:
                    anomalies.append(i+1)
                    #print(f'Anomalia al pas {i+1}: [[{graph}]]')
            #if max(groups) != groups[min(5, len(groups)-1)]:
            #    print(line, end='', file = None)
            #points.append((densitat, num_iterations, unary_groups))
                    
    print(path, num_experiments, len(anomalies), len(anomalies)/num_experiments, sum(anomalies)/(len(anomalies) or 1),  sep='\t')


'''
    x = [point[0] for point in points]
    y = [point[1] for point in points]
    c = [('green' if not p[2] else 'blue') for p in points]
    fig, ax = plt.subplots(figsize = (8,8))
    ax.scatter(x, y, c=c,  s=60, alpha=0.5, edgecolors="k")
    #ax.set_xscale("log")
    plt.show()'''