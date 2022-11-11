#pragma once
#include "Utils.hpp"
#include <cstddef>
#include <cstdlib>
#include <string.h>

namespace excercice {
	/*
	  Le but de la classe est de faire comme std::vector, un tableau dynamique
	  capable de stocker un nombre indéfini et variable d'objets. Dans notre
	  cas, on n'a pas besoin de supprimer des objets spécifiques, on ne fait
	  qu'en ajouter.

	* Pro Tip: pour le debugger VS dans les watch (espions en francais), tu peux
	* afficher les ptr sous forme de tableau :
	* Avec: _Ty* ptr;
	* Pour afficher ptr[0..9]: ptr,10
	* Pour afficher ptr[5..9]: ptr+5,5
	* https://docs.microsoft.com/fr-fr/visualstudio/debugger/format-specifiers-in-cpp?view=vs-2022
	*/
	// _Ty correspond au type d'objet a stocker (comme les generic en C#)
	template<typename _Ty>class SimpleVector {
	public:
		using value_type = _Ty;
		_Ty* data;
		std::size_t memorySize;
		std::size_t arraySize;
		// Optionnel: préalloue le tableau pour un certain nombre de données
		SimpleVector(std::size_t dsize) {
			init(dsize);
		}
		// Constructeur principal
		SimpleVector() : SimpleVector(DEFAULT_ARRAY_SIZE) { }

		/// <summary>
		/// Ajoute un élément dans le tableau par copie
		/// </summary>
		/// <param name="elem">Une copie de l'élement a ajouter</param>
		void push_back(_Ty elem) {
			arraySize++;
			if (memorySize <= arraySize) allocate();
			data[arraySize - 1] = elem;
		}


		/// <summary>
		/// Donne le nombre d'éléments actuellement présents dans le tableau
		/// </summary>
		/// <returns>Le nb d'elems</returns>
		std::size_t size() {
			return arraySize;
		}

		/// <summary>
		/// Permet d'accéder à un element particulier via un pointeur sans possibilité de modifier l'élément
		/// </summary>
		/// <param name="index">L'index de l'élément à acceder </param>
		/// <returns>Un pointeur vers l'objet constant</returns>
		const _Ty* at(std::size_t index) { return &data[index]; }

		/// <summary>
		/// Permet de vider le tableau.
		/// </summary>
		void clear() {
			delete[] data;
		}
		~SimpleVector() {
			delete[] data;
		}
	private:
		const int DEFAULT_ARRAY_SIZE = 16;
		void allocate() {
			if (data == nullptr) {
				data = new _Ty[memorySize];
			}
			else {
				memorySize += DEFAULT_ARRAY_SIZE;
				_Ty* newPtr = (_Ty*)memcpy(new _Ty[memorySize], data, memorySize * sizeof(_Ty));
				delete[] data;
				data = newPtr;
			}
		}
		void init(std::size_t size) {
			data = nullptr;
			memorySize = size;
			arraySize = 0;
			allocate();
		}
	};
}