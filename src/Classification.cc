#ifndef CLASSIFICATION_cc
#define CLASSIFICATION_cc

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <limits.h>
#include "utils.cc"

template<typename T>
class Classification {

private:
    std::map<T, std::set<uint>> classification;
    int numElems;

public:
    Classification() {}

    Classification(const std::vector<T>& list) {
        for (uint elem = 0; elem < list.size(); elem++) {
            T klass = list[elem];
            std::set<uint>& class_elems = classification[klass];
            class_elems.insert(elem);
        }
        numElems = list.size();
    }

    int getNumClasses() const {
        return classification.size();
    }

    int getNumElems() const {
        return numElems;
    }

    std::map<T, std::set<uint>> getMap() {
        return classification;
    }

    std::set<uint> getElemsByClass(const T& klass) const {
        auto it = classification.find(klass);
        if (it != classification.end()) {
            return it->second;
        }
        return std::set<uint>();
    }

    std::map<T, std::set<uint>> getElemsByClass() const {
        return classification;
    }

    int getNumElemsByClass(const T& klass) const {
        return getElemsByClass(klass).size();
    }

    std::map<T, uint> getNumElemsByClass() const {
        std::map<T, uint> ret;
        for (const auto& entry : classification) {
            ret[entry.first] = entry.second.size();
        }
        return ret;
    }

    bool isEquivalent(const Classification<T>& other) const {
        return (this->getNumElemsByClass() == other.getNumElemsByClass());
    }

    ulong getNumPermutations() const {
        ulong permutations = 1;
        for (const auto& elems_class : classification) {
            ulong factorial = factorial(elems_class.second.size());
            if (multOverflow(permutations, factorial)) return LONG_MAX;
            else permutations *= factorial;
            
        }
        return permutations;
    }

    friend std::ostream& operator<<(std::ostream &os, const Classification& c) {
        for (const std::pair<T, std::set<uint>>& item : c.classification) {
            os << item.first << ": " << item.second << "\n";
        }
        return os;
    }


};


#endif
