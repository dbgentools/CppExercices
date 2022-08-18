#pragma once
#include <cstdint>
#include <cstddef>
#include <cstring>

namespace exercice1 {
  /*
  * Le but est de faire un tableau dynamique ayant globalement la même
  * interface que std::vector (ou SimpleVector) mais dont l'allocation en
  * interne se fait par segments.
  * Ainsi, au lieu d'avoir un seul gros tableau, on utilise une série
  * de plus petits tableaux. En pratique :
  *   On veut un tableau où foutre 100 éléments. Un SimpleVector fera une
  *   allocation de 100. SegmentedVector, lui, fera 4 allocations de 32.
  * 
  * SimpleVector:
  * [0, 1, 2, ..., 99]
  * SegmentedVector (segment size = 32):
  * [0, 1, 2, ..., 31]
  * [32, 33, 34, ..., 63]
  * [64, 65, 66, ..., 95]
  * [96, 97, 98, ..., 127]
  * 
  *
  * Ce design est parfois utile en pratique pour limiter les réallocations.
  * Ainsi, depuis ces 100 éléments, si nous voulons rajouter 20 éléments de plus,
  * aucune réallocation n'est nécessaire. Aussi, si nous voulons dépasser les 127
  * éléments, il suffit d'allouer un nouveau bloc au lieu de tout copier comme
  * dans le SimpleVector.
  *
  * Dans ce premier exercice, le nombre de segments et leur taille est fixe.
  * Aussi, nous n'avons pas besoin de la capacité à enlever des éléments des
  * tableaux (push-only).
  * 
  * Optionnel 1:
  * Nous voulons afficher un message d'erreur compréhensible dans le cas où 
  * l'utilisateur utilisait void comme type de donnée. Pour cette partie, 
  * interdit d'utiliser std::enable_if(_t) ni les concepts ou require. 
  * Le plus simple est le mieux !
  * 
  * Optionnel 2:
  * Pour légèrement augmenter la difficulté, il est possible de faire cet exercice 
  * sans stocker le nombre d'éléments actuels dans les segments. A la place, on peut 
  * utiliser des pointeurs. Il est même possible d'implémenter size() même sans avoir
  * le nombre d'élements par segments grâce à ces mêmes pointeurs.
  * 
  * Optionnel 3:
  * Au lieu d'utiliser une taille et un nombre de segments constant, on peut
  * faire un système dynamique capable de changer la géométrie de notre
  * tableau. Par exemple, modifier le nombre ou la taille des segments alors
  * que la donnée est deja présente dans le tableau.
  * 
  */
  template<typename _Ty>class SegmentedVector {
    
  public:
    // The maximum amount of segments
    const int SEGMENT_COUNT = 32;
    // The maximum number of elements in each segments
    const int SEGMENT_SIZE = 32;
    // Note: the maximum amount of elements in this
    // SegmentedVector is then COUNT*SIZE

    SegmentedVector() {}

    /// <summary>
    /// Add an element in the array
    /// </summary>
    /// <param name="elem">The elem to add</param>
    void push_back(_Ty elem) {}

    /// <summary>
    /// Copy the content to another array
    /// </summary>
    /// <param name="arr">The array to copy to</param>
    /// <param name="max">The maximum number of elements to copy</param>
    void copy(_Ty* arr, std::size_t max = static_cast<std::size_t>(-1)) {}

    /// <summary>
    /// Retrieve an element from the array
    /// </summary>
    /// <param name="index">The index of the element to retrieve</param>
    /// <returns></returns>
    _Ty& at(std::size_t index) {
      return _Ty();
    }

  };
}