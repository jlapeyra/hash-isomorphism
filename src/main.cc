#include <iostream>
#include <cassert>
#include <chrono>
#include "IsoGraph.cc"
#include <fstream>

/**
 * @brief 
 * 
 * @param n number of vertices
 * @param density edge densisty, i.e. probability of an edge given two vertices
 * @return IsoGraph 
 */
IsoGraph randomGraph(uint n, float density) {
    assert(0 <= density && density <= 1);
    IsoGraph g(n); 
    for (uint i = 0; i < n; i++) {
        for (uint j = i + 1; j < n; j++) {
            if (std::rand()%1000 < 1000*density) {
                g.addAdj(i, j);
            }
        }
    }
    return g;
}



//#define os std::cout

int main(int argc, char const *argv[])
{

    int seed = 123;
    if (argc > 1) {
        seed = std::atoi(argv[1]);
    }
    std::srand(seed);

    

    std::ofstream os;
    os.open("../analisi/v3_hash_groups_sparse.out.txt");

    os << "num_vtx : edge_density : num_edges | num_groups_hash_level_0 num_groups_hash_level_1 ... | time_spent" << std::endl;
    //for (int n : {10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 150, 200, 250, 300, 400, 500, 600, 700, 800}) {
    //    for (float density : {0.05, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9}) {
    for (int n : {10, 15, 20, 25, 30, 40, 50, 60, 70, 80, 90, 100, 150, 200, 250, 300, 400, 500}) {
        for (float density : {0.01, 0.02, 0.03, 0.04, 0.06, 0.08, 0.1, 0.12, 0.15, 0.18, 0.20, 0.25, 0.3, 0.4}) {
            if (n*(n-1)/2*density < 1.5) continue;
            density = density;
            for (int i = 0; i < 8; i++) {
                IsoGraph g = randomGraph(n, density);
                if (g.getNumEdges() == 0 || g.getNumEdges() == n*(n-1)/2) continue;
                os << n << " : " << density << " : " << g.getNumEdges() << " | ";
                auto start = std::chrono::steady_clock::now();
                for (int level = 0; level < n; level++) {
                    if (level == 0) { 
                        g.initHashes(); 
                    } else {
                        g.upgradeHashes();
                        os << ", ";
                    }
                    os << g.getClassification().getNumClasses();
                    if (g.getClassification().getNumClasses() >= n) break;
                }
                os << " | " << since(start).count() << " ms";
                os << std::endl;
            }
        }
        os << std::endl;
        os.flush();
    }
}

//*/