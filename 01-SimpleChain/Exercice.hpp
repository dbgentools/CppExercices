#pragma once
#include <cstddef>

namespace exercice {
  /*
  * L'objectif est de faire une liste chainee capable de stocker
  * x données de type _Ty, d'y accéder et d'en supprimer.
  */
  template<typename _Ty>class SimpleChain {
  public:
    using value_type = _Ty;

    SimpleChain() {}

    /// <summary>
    /// Ajoute la donnée data à la fin de la liste
    /// </summary>
    /// <param name="data">Data to add</param>
    /// <returns>The id of the newly added data</returns>
    std::size_t push_back(_Ty* data) { return 0ULL; }

    /// <summary>
    /// Supprime une donnée de la liste par son id
    /// </summary>
    /// <param name="index">id de la data a suppr</param>
    void remove(std::size_t index) {}

    /// <summary>
    /// Accède à une donnée via son id
    /// </summary>
    /// <note>
    /// Si la donnée n'existe pas, renvoi nullptr
    /// </note>
    /// <param name="index">id de la donnée a accéder</param>
    /// <returns>ptr vers la donnée</returns>
    _Ty* at(std::size_t index) { return nullptr; }

    /// <summary>
    /// Accès à la première donnée stockée dans la liste
    /// </summary>
    /// <note>
    /// Si la donnée n'existe pas, renvoi nullptr
    /// </note>
    /// <returns>ptr vers la donnée</returns>
    _Ty* first() { return nullptr; }

    /// <summary>
    /// Accès à la dernière donnée stockée dans la liste
    /// </summary>
    /// <note>
    /// Si la donnée n'existe pas, renvoi nullptr
    /// </note>
    /// <returns>ptr vers la donnée</returns>
    _Ty* last() { return nullptr; }

    /// <summary>
    /// Renvoi le nb d'elements dans la liste
    /// </summary>
    /// <returns></returns>
    std::size_t size() { return 0ULL; }

    /// <summary>
    /// Supprime toutes les données de la liste
    /// </summary>
    void clear() {}
  };
}