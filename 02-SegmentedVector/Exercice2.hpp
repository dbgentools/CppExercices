#pragma once
#include <cstdint>
#include <cstddef>
#include <cstring>

namespace exercice2 {
  /*
  * Le but est de faire comme dans l'exercice 1 mais en autorisant
  * des manipulations plus poussées du tableau.
  * 
  * On rajoute deux fonctions : reorganize et remove
  * 
  * reorganize doit pouvoir modifier la géométrie du tableau
  * vers une nouvelle tout en compactant ses éléments
  * en clair, reorganize doit combler tous les trous du
  * tableau mais aussi doit permettre de changer dynamiquement
  * la taille et le nombre de segments
  * 
  * remove permet d'enlever un élément du tableau par son index
  * 
  * Optionnel :
  * !!! Attention cette partie est excessivement compliquée
  * algorithmitiquement parlant !!!
  * 
  * faire la fonction remove sans déplacer de données _Ty tout en
  * conservant la fonction reorganize
  */
  template<typename _Ty>class SegmentedVector {
  public:
    using value_type = _Ty;

    SegmentedVector(std::size_t segmentSize = 32U, std::size_t segmentCount = 32U) { }

    void reorganize(std::size_t nwSegSz, std::size_t nwSegCnt) {

    }

    void push_back(_Ty elem) {}

    void copy(_Ty* arr, std::size_t max = static_cast<std::size_t>(-1)) { }

    _Ty& at(std::size_t index) {
      static _Ty _to_remove;
      return _to_remove;
    }

    void remove(std::size_t index) {}

    // return false tant que le dernier segment
    // n'est pas rempli sinon true
    bool is_lineary_full() {}

  };
}