#pragma once
#include "Utils.hpp"
#include <cstddef>

namespace excercice {
  /*
    Le but de la classe est de faire comme std::vector, un tableau dynamique
    capable de stocker un nombre indéfini et variable d'objets. Dans notre
    cas, on n'a pas besoin de supprimer des objets spécifiques, on ne fait
    qu'en ajouter.
  */
  // _Ty correspond au type d'objet a stocker (comme les generic en C#)
  template<typename _Ty>class SimpleVector {
  public:
    using value_type = _Ty;

    // Optionnel: préalloue le tableau pour un certain nombre de données
    SimpleVector(std::size_t dsize) { }
    // Constructeur principal
    SimpleVector() {}

    /// <summary>
    /// Ajoute un élément dans le tableau par copie
    /// </summary>
    /// <param name="elem">Une copie de l'élement a ajouter</param>
    void push_back(_Ty elem) {}

    /// <summary>
    /// Donne le nombre d'éléments actuellement présents dans le tableau
    /// </summary>
    /// <returns>Le nb d'elems</returns>
    std::size_t size() { return 0ULL; }

    /// <summary>
    /// Permet d'accéder à un element particulier via un pointeur sans possibilité de modifier l'élément
    /// </summary>
    /// <param name="index">L'index de l'élément à acceder [0,+)</param>
    /// <returns>Un pointeur vers l'objet constant</returns>
    const _Ty* at(std::size_t index) { return nullptr; }

    /// <summary>
    /// Permet de vider le tableau.
    /// </summary>
    void clear() {}
  };
}