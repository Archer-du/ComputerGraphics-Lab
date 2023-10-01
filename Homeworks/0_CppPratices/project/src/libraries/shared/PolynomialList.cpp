#include "PolynomialList.h"

#include <iostream>
#include <fstream>

using namespace std;

PolynomialList::PolynomialList(const PolynomialList& other) {
    // TODO
}
list<PolynomialList::PolynomialTerm>::const_iterator PolynomialList::Begin() const {
    return termList.begin();
}
list<PolynomialList::PolynomialTerm>::const_iterator PolynomialList::End() const {
    return termList.end();
}
PolynomialList::PolynomialList(const string& path) {
    // TODO
    ifstream inputFile(path);
    if(!inputFile.is_open()){
        cerr << "fail opening file" << endl;
        return;
    }
    string indentifier;
    int itemNum;
    inputFile >> indentifier >> itemNum;
    for(int i = 0; i < itemNum; i++){
        PolynomialTerm term;
        inputFile >> term.exp >> term.coe;
        AddOneTerm(term);
    }
    inputFile.close();
    Sort();
    Merge();
}

PolynomialList& PolynomialList::operator+(const PolynomialList& right) const {
    // TODO{
    PolynomialList* result = new PolynomialList();
    auto it1 = termList.begin();
    auto it2 = right.Begin();
    while (it2 != right.End() && it1 != termList.end()) {
        PolynomialTerm term;
        if(it1->exp == it2->exp){
            term.exp = it1->exp;
            term.coe = it1->coe + it2->coe;
            it1++; it2++;
        }
        else if(it1->exp < it2->exp){
            term.exp = it1->exp;
            term.coe = it1->coe;
            it1++;
        }
        else{
            term.exp = it2->exp;
            term.coe = it2->coe;
            it2++;
        }
        result->AddOneTerm(term);
    }
    if(it2 == right.End() && it1 == termList.end()){
        return *result;
    }
    while(it1 != termList.end()){
        PolynomialTerm term;
        term.exp = it1->exp;
        term.coe = it1->coe;
        result->AddOneTerm(term);
    }
    while(it2 != termList.end()){
        PolynomialTerm term;
        term.exp = it2->exp;
        term.coe = it2->coe;
        result->AddOneTerm(term);
    }
    return *result;
}

PolynomialList& PolynomialList::operator-(const PolynomialList& right) const {
    // TODO
    PolynomialList* result = new PolynomialList();
    auto it1 = termList.begin();
    auto it2 = right.Begin();
    while (it2 != right.End() && it1 != termList.end()) {
        PolynomialTerm term;
        if (it1->exp == it2->exp) {
            term.exp = it1->exp;
            term.coe = it1->coe - it2->coe;
            it1++; it2++;
        }
        else if (it1->exp < it2->exp) {
            term.exp = it1->exp;
            term.coe = it1->coe;
            it1++;
        }
        else {
            term.exp = it2->exp;
            term.coe = -it2->coe;
            it2++;
        }
        result->AddOneTerm(term);
    }
    if (it2 == right.End() && it1 == termList.end()) {
        return *result;
    }
    while (it1 != termList.end()) {
        PolynomialTerm term;
        term.exp = it1->exp;
        term.coe = it1->coe;
        result->AddOneTerm(term);
    }
    while (it2 != termList.end()) {
        PolynomialTerm term;
        term.exp = it2->exp;
        term.coe = -it2->coe;
        result->AddOneTerm(term);
    }
    return *result;
}

PolynomialList& PolynomialList::operator*(const PolynomialList& right) const {
    // TODO
    PolynomialList* result = new PolynomialList();
    for (auto it1 = termList.begin(); it1 != termList.end(); it1++) {
        for (auto it2 = right.Begin(); it2 != right.End(); it2++) {
            PolynomialTerm term;
            term.coe = it1->coe * it2->coe;
            term.exp = it1->exp + it2->exp;
            result->AddOneTerm(term);
        }
    }
    result->Sort();
    result->Merge();
    return *result;
}

PolynomialList& PolynomialList::operator=(const PolynomialList& right) {
    // TODO
    termList = right.termList;
    return *this;
}

void PolynomialList::Print() const {
    // TODO{
    for(auto it = termList.begin(); it != termList.end(); it++){
        cout << it->exp << " " << it->coe << endl;
    }
}

void PolynomialList::AddOneTerm(const PolynomialTerm& term) {
    if (term.coe == 0) return;
    termList.push_back(term);
}
