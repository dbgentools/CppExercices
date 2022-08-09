#pragma once
#include <cstddef>

namespace exercice {
  /*
  * L'objectif est de faire une liste chainee capable de stocker
  * x donn�es de type _Ty, d'y acc�der et d'en supprimer.
  */
  template<typename _Ty>class SimpleChain {
  public:
    using value_type = _Ty;

    SimpleChain() {}

    /// <summary>
    /// Ajoute la donn�e data � la fin de la liste
    /// </summary>
    /// <param name="data">Data to add</param>
    /// <returns>The id of the newly added data</returns>
    std::size_t push_back(_Ty* data) { return 0ULL; }

    /// <summary>
    /// Supprime une donn�e de la liste par son id
    /// </summary>
    /// <param name="index">id de la data a suppr</param>
    void remove(std::size_t index) {}

    /// <summary>
    /// Acc�de � une donn�e via son id
    /// </summary>
    /// <note>
    /// Si la donn�e n'existe pas, renvoi nullptr
    /// </note>
    /// <param name="index">id de la donn�e a acc�der</param>
    /// <returns>ptr vers la donn�e</returns>
    _Ty* at(std::size_t index) { return nullptr; }

    /// <summary>
    /// Acc�s � la premi�re donn�e stock�e dans la liste
    /// </summary>
    /// <note>
    /// Si la donn�e n'existe pas, renvoi nullptr
    /// </note>
    /// <returns>ptr vers la donn�e</returns>
    _Ty* first() { return nullptr; }

    /// <summary>
    /// Acc�s � la derni�re donn�e stock�e dans la liste
    /// </summary>
    /// <note>
    /// Si la donn�e n'existe pas, renvoi nullptr
    /// </note>
    /// <returns>ptr vers la donn�e</returns>
    _Ty* last() { return nullptr; }

    /// <summary>
    /// Renvoi le nb d'elements dans la liste
    /// </summary>
    /// <returns></returns>
    std::size_t size() { return 0ULL; }

    /// <summary>
    /// Supprime toutes les donn�es de la liste
    /// </summary>
    void clear() {}
  };
}