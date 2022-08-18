#pragma once
#include <cstdint>
#include <cstddef>
#include <cstring>

namespace exercice1 {
  /*
  * Le but est de faire un tableau dynamique ayant globalement la m�me
  * interface que std::vector (ou SimpleVector) mais dont l'allocation en
  * interne se fait par segments.
  * Ainsi, au lieu d'avoir un seul gros tableau, on utilise une s�rie
  * de plus petits tableaux. En pratique :
  *   On veut un tableau o� foutre 100 �l�ments. Un SimpleVector fera une
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
  * Ce design est parfois utile en pratique pour limiter les r�allocations.
  * Ainsi, depuis ces 100 �l�ments, si nous voulons rajouter 20 �l�ments de plus,
  * aucune r�allocation n'est n�cessaire. Aussi, si nous voulons d�passer les 127
  * �l�ments, il suffit d'allouer un nouveau bloc au lieu de tout copier comme
  * dans le SimpleVector.
  *
  * Dans ce premier exercice, le nombre de segments et leur taille est fixe.
  * Aussi, nous n'avons pas besoin de la capacit� � enlever des �l�ments des
  * tableaux (push-only).
  * 
  * Optionnel 1:
  * Nous voulons afficher un message d'erreur compr�hensible dans le cas o� 
  * l'utilisateur utilisait void comme type de donn�e. Pour cette partie, 
  * interdit d'utiliser std::enable_if(_t) ni les concepts ou require. 
  * Le plus simple est le mieux !
  * 
  * Optionnel 2:
  * Pour l�g�rement augmenter la difficult�, il est possible de faire cet exercice 
  * sans stocker le nombre d'�l�ments actuels dans les segments. A la place, on peut 
  * utiliser des pointeurs. Il est m�me possible d'impl�menter size() m�me sans avoir
  * le nombre d'�lements par segments gr�ce � ces m�mes pointeurs.
  * 
  * Optionnel 3:
  * Au lieu d'utiliser une taille et un nombre de segments constant, on peut
  * faire un syst�me dynamique capable de changer la g�om�trie de notre
  * tableau. Par exemple, modifier le nombre ou la taille des segments alors
  * que la donn�e est deja pr�sente dans le tableau.
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