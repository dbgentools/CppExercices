#pragma once
#include <cstddef>

namespace exercice {
	/*
	* L'objectif est de faire une liste chainee capable de stocker
	* x donn�es de type _Ty, d'y acc�der et d'en supprimer.
	*/
	template<typename _Ty>class SimpleChain {
	public:
		struct node {
			_Ty* data;
			struct node* next;
		};
		using value_type = _Ty;
		node* head;
		node* tail;
		std::size_t chainSize;
		SimpleChain() {
			head = nullptr;
			tail = nullptr;
			chainSize = 0;
		}

		/// <summary>
		/// Ajoute la donn�e data � la fin de la liste
		/// </summary>
		/// <param name="data">Data to add</param>
		/// <returns>The id of the newly added data</returns>
		std::size_t push_back(_Ty* data) {
			tail = (head == nullptr) ? head = initNode(data, nullptr) : initNode(data, tail);
			chainSize++;
			return chainSize - 1;
		}

		/// <summary>
		/// Supprime une donn�e de la liste par son id
		/// </summary>
		/// <param name="index">id de la data a suppr</param>
		void remove(std::size_t index) {
			node* ptr = findRecur(0, index, head);
			if (ptr != nullptr) {
				if (ptr == head)
					head = ptr->next;
				else {
					node* prev = findRecur(0, index - 1, head);
					prev->next = ptr == tail ? nullptr : ptr->next;
				}
				chainSize--;
				delete ptr;
			}
		}

		/// <summary>
		/// Acc�de � une donn�e via son id
		/// </summary>
		/// <note>
		/// Si la donn�e n'existe pas, renvoi nullptr
		/// </note>
		/// <param name="index">id de la donn�e a acc�der</param>
		/// <returns>ptr vers la donn�e</returns>
		_Ty* at(std::size_t index) {
			if (index < chainSize) {
				node* ptr = findRecur(0, index, head);
				return ptr != nullptr ? ptr->data : nullptr;
			}
			else return nullptr;
		}

		/// <summary>
		/// Acc�s � la premi�re donn�e stock�e dans la liste
		/// </summary>
		/// <note>
		/// Si la donn�e n'existe pas, renvoi nullptr
		/// </note>
		/// <returns>ptr vers la donn�e</returns>
		_Ty* first() { return head->data; }

		/// <summary>
		/// Acc�s � la derni�re donn�e stock�e dans la liste
		/// </summary>
		/// <note>
		/// Si la donn�e n'existe pas, renvoi nullptr
		/// </note>
		/// <returns>ptr vers la donn�e</returns>
		_Ty* last() { return tail->data; }

		/// <summary>
		/// Renvoi le nb d'elements dans la liste
		/// </summary>
		/// <returns></returns>
		std::size_t size() { return chainSize; }

		/// <summary>
		/// Supprime toutes les donn�es de la liste
		/// </summary>
		void clear() {
			deleteRecur(head);
			chainSize = 0;
			head = nullptr;
			tail = nullptr;
		}
		~SimpleChain() {
			clear();
		}

	private:
		node* initNode(_Ty* data, node* prev) {
			node* n = new node;
			n->data = data;
			if (prev != nullptr)
				prev->next = n;
			n->next = nullptr;
			return n;
		}

		node* findRecur(int index, int indexCible, node* n) {
			if (n != nullptr) return index == indexCible ? n : findRecur(++index, indexCible, n->next);
			else return nullptr;
		}

		void deleteRecur(node* n) {
			if (n != nullptr) {
				deleteRecur(n->next);
			}
			delete n;
		}
	};
}