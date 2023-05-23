//Autor Ennio Gonzalez

#ifndef NODOADYA_H
#define NODOADYA_H

template <class T, class C>
class NodoVertice;

template <class T, class C>
class NodoAdya
{
	protected:

		NodoVertice<T,C> 	*ptrNodoVertice;
		NodoAdya<T,C>		*ptrProximo;
		C 			peso;
		bool			visitado;

	public:

		//Constructores
		inline NodoAdya(NodoVertice<T,C>* const vertice, NodoAdya<T,C>* const ady = NULL, C costo = 0);
		inline NodoAdya(const NodoAdya<T,C> &nodo);

		//Modificadores
		inline void setVertice(NodoVertice<T,C>* vertice);
		inline void setProx(NodoAdya<T,C>* nodo);
		inline void setPeso(C peso);

		//Observadores
		inline C 			getPeso() 		const;
		inline bool				visitar()		const;
		inline NodoVertice<T,C>* 	getVertice() 	const;
		inline NodoAdya<T,C>*		getProx() 		const;

};

template <class T, class C>
inline NodoAdya<T,C>::NodoAdya(NodoVertice<T,C>* const vertice, NodoAdya<T,C>* const ady, C costo):	ptrNodoVertice(vertice),
																									ptrProximo(ady),
																									peso(costo){}

template <class T, class C>
inline NodoAdya<T,C>::NodoAdya(const NodoAdya<T,C> &nodo): 	ptrNodoVertice(nodo.ptrNodoVertice),
												 		ptrProximo(nodo.ptrProximo),
												 		peso(nodo.peso){}

template <class T, class C>
inline void NodoAdya<T,C>::setVertice(NodoVertice<T,C>* vertice) {this->ptrNodoVertice =  vertice;}

template <class T, class C>
inline void NodoAdya<T,C>::setProx(NodoAdya<T,C>* nodo){this->ptrProximo = nodo;}

template <class T, class C>
inline void NodoAdya<T,C>::setPeso(C peso){this->peso = peso;}

template <class T, class C>
inline C NodoAdya<T,C>::getPeso() const {return this->peso;}

template <class T, class C>
inline NodoAdya<T,C>* NodoAdya<T,C>::getProx() const {return this->ptrProximo;}

template <class T, class C>
inline NodoVertice<T,C>* NodoAdya<T,C>::getVertice() const {return	ptrNodoVertice;}


#endif