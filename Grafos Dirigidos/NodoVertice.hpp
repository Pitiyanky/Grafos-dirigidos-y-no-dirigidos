//Autor Ennio Gonzalez

#ifndef NODOVERTICE_H
#define NODOVERTICE_H

template <class T, class C>
class NodoAdya;

template <class T, class C>
class NodoVertice
{

	protected:
		NodoAdya<T,C> 	*ptrNodoAdya;
		NodoVertice<T,C> 	*ptrProximo;
		T 				elemento;
		bool			visitado;

	public:

		//Constructores
		inline NodoVertice();
		inline NodoVertice(T e);
		inline NodoVertice(const NodoVertice<T,C>& nodo);

		//Modificadores
		inline void setAdya(NodoAdya<T,C>* adya);
		inline void setProx(NodoVertice<T,C>* nodo);
		inline void setElemento(const T e);
		inline void	marcar();
		inline void	desmarcar();
		
		//Observadores
		inline bool estaMarcado()				const {return visitado;}
		inline NodoAdya<T,C>* 	getAdya()		const;
		inline NodoVertice<T,C>* 	getProx() 		const;
		inline T 				getElemento() 	const;
};

template <class T, class C>
inline NodoVertice<T,C>::NodoVertice(): 	ptrNodoAdya(0),
							 			ptrProximo(0),
							 			visitado(false){}

template <class T, class C>
inline NodoVertice<T,C>::NodoVertice(T e):	ptrNodoAdya(0),
							 				ptrProximo(0),
							 				visitado(false){this->elemento = e;}

template <class T, class C>						 			
inline NodoVertice<T,C>::NodoVertice(const NodoVertice<T,C> &nodo):	ptrNodoAdya(nodo.ptrNodoAdya),
												 				ptrProximo(nodo.ptrProximo),
												 				elemento(nodo.visitado),
												 				visitado(nodo.visitado){}

template <class T, class C>
inline void NodoVertice<T,C>::setAdya(NodoAdya<T,C>* adya){this->ptrNodoAdya = adya;}

template <class T, class C>
inline void NodoVertice<T,C>::setProx(NodoVertice<T,C>* nodo){this->ptrProximo = nodo;}

template <class T, class C>
inline void NodoVertice<T,C>::setElemento(const T e){this->elemento = e;}

template <class T, class C>
inline void	NodoVertice<T,C>::marcar() {this->visitado = true;}

template <class T, class C>
inline void	NodoVertice<T,C>::desmarcar() {this->visitado = false;}

template <class T, class C>
inline NodoAdya<T,C>* NodoVertice<T,C>::getAdya() const {return	ptrNodoAdya;}

template <class T, class C>
inline NodoVertice<T,C>* NodoVertice<T,C>::getProx() const {return	ptrProximo;}

template <class T, class C>
inline T NodoVertice<T,C>::getElemento() const {return elemento;}

#endif