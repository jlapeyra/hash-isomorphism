#ifndef ISO_GRAPH_CC
#define ISO_GRAPH_CC

#include <iostream>
#include <vector>
#include <set>
#include <cassert>
#include "Classification.cc"
#include "utils.cc"

typedef uint col; //color
typedef uint vtx; //vertex
typedef ulong hash;
#define numeric typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type
#define nothing std::nullopt;

class IsoGraph {
private:
    std::vector<std::set<vtx>> adjList;
    uint numVertices;
    ulong numEdges;
    std::vector<col> colors;
    std::vector<hash> hashes;
    Classification<hash> verticesByHashes;
    bool classificationUpdated = false;
    int hashLevel = -1;
    const int SHIFT = sizeof(hash)*8 / 2;  //if long is 64-bit long, then SHIFT=32
public:
    IsoGraph(uint numVertices) {
        adjList = std::vector<std::set<vtx>>(numVertices, std::set<vtx>());
        colors = std::vector<col>(numVertices, 0);
        this->numVertices = numVertices;
        this->numEdges = 0;
    }

    uint getNumVertices() const {
        return numVertices;
    }
    uint getNumEdges() const {
        return numEdges;
    }
    const std::vector<std::set<vtx>>& getAdjList() const {
        return adjList;
    }
    bool areAdj(vtx vertex1, vtx vertex2) const {
        return adjList[vertex1].count(vertex2) > 0; //C++20: adjList[vertex1].contains(vertex2)
    }


    void addAdj(vtx vertex1, vtx vertex2) {
        assert(vertex1 < numVertices);
        assert(vertex2 < numVertices);
        if (adjList[vertex1].insert(vertex2).second) {
            adjList[vertex2].insert(vertex1);
            numEdges++;
        }
    }

    void setColor(vtx vertex, col color) {
        colors[vertex] = color;
    }



    void initHashes() {
        hashes = std::vector<hash>(numVertices);
        for (vtx i = 0; i < numVertices; i++) 
            hashes[i] = (hash(colors[i]) << SHIFT) ^ adjList[i].size();
        hashLevel = 0;
    }

    static hash getHash(hash h1, const std::multiset<hash>& h2) {
        hash result = 0;
        for (hash h : h2) {
            result = 31 * result + h;
        }
        // 31 and 127 are primes 2^p-1
        return result;
    }

    void upgradeHashes() {
        std::vector<hash> nextHashes(numVertices);
        for (vtx vertex = 0; vertex < numVertices; vertex++) {
            std::multiset<hash> adjHashes; //sorted set allowing duplicates
            for (vtx adjVertex : adjList[vertex]) {
                adjHashes.insert(hashes[adjVertex]);
            }
            hash vertexHash = hashes[vertex];
            nextHashes[vertex] = getHash(vertexHash, adjHashes);
        }
        hashes = nextHashes;
        hashLevel++;
        classificationUpdated = false;
    }

    void upgradeHashes(int level) {
        while (this->hashLevel < level) {
            upgradeHashes();
        }
    }

    void updateClassification() {
        if (!classificationUpdated) {
            verticesByHashes = Classification<hash>(hashes);
            classificationUpdated = true;
        }
    }

    const Classification<hash>& getClassification() {
        updateClassification();
        return verticesByHashes;
    }

    std::set<std::set<vtx>> getClassificationSets() {
        updateClassification();
        std::set<std::set<vtx>> result;
        for (std::pair<hash, std::set<vtx>> item : verticesByHashes.getMap()) {
            result.insert(item.second);
        }
        return result;
    }

    static void upgradeHashes(IsoGraph& g1, IsoGraph& g2, int hashLevel) {
        g1.upgradeHashes(hashLevel);
        g2.upgradeHashes(hashLevel);
    }

    friend std::ostream& operator<<(std::ostream &os, const IsoGraph& obj) {
        for (vtx i = 0; i < obj.numVertices; i++) {
            os << i << ":";
            for (vtx j : obj.adjList[i]) {
                os << " " << j;
            }
            os << "\n";
        }
        return os;
    }

    std::ostream& printHashes(std::ostream &os=std::cout) const {
        os << "Hash level: " << hashLevel << "\n";
        os << Classification<hash>(hashes);
        return os;
    }

    const std::vector<hash>& getHashes() const {
        return hashes;
    }

    bool isIsomorphic(IsoGraph& otherGraph) {
        return getIsomorphism(otherGraph) != nothing;
    }

    std::optional<std::vector<uint>> getIsomorphism(IsoGraph& otherGraph) {
        IsoGraph* other = &otherGraph; //for symmetry with `this`
        if (this->numVertices != other->numVertices) return nothing;
        if (this->numEdges != other->numEdges) return nothing;

    }
};

#endif
