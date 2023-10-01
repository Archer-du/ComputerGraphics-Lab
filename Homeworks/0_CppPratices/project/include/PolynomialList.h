#pragma once

#if defined(_WIN32) && defined(Ubpa_AsShared_PolynomialList)
#  ifdef Ubpa_Export_PolynomialList
#    define DECLSPEC_PolynomialList __declspec(dllexport)
#  else
#    define DECLSPEC_PolynomialList __declspec(dllimport)
#  endif
#else
#  define DECLSPEC_PolynomialList
#endif

#include <list>
#include <string>
#include <vector>

using namespace std;

class DECLSPEC_PolynomialList PolynomialList {
private:
    struct PolynomialTerm {
        int exp;
        double coe;

        PolynomialTerm(int exp, double coe) : exp(exp), coe(coe) { }
        PolynomialTerm() : PolynomialTerm(0, 0) { }
    };
    void AddOneTerm(const PolynomialTerm& term); // add one term into m_Polynomial

public:
    PolynomialList() { };
    PolynomialList(const PolynomialList& other);
    PolynomialList(const std::string& file); // initialization using file

    // overload
    PolynomialList& operator+(const PolynomialList& right) const; //Overload operator +
    PolynomialList& operator-(const PolynomialList& right) const; //Overload operator -
    PolynomialList& operator*(const PolynomialList& right) const; //Overload operator *
    PolynomialList& operator=(const PolynomialList& right); //Overload operator =

    void Print() const;

    list<PolynomialTerm>::const_iterator Begin() const;
    list<PolynomialTerm>::const_iterator End() const;

private:
    list<PolynomialTerm> termList; // high degree -> low degree

private:
    void Sort() {
        termList.sort([](const PolynomialTerm& term1, const PolynomialTerm& term2) 
            { return term1.exp < term2.exp; });
    }
    void Merge() {
        auto it = termList.begin();
        while (next(it) != termList.end()) {
            if (it->exp == next(it)->exp) {
                it->coe += next(it)->coe;
                it = termList.erase(next(it));
            }
            else it++;
        }
    }
};
