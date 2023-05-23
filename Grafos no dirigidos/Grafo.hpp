#ifndef GRAFO_H
#define GRAFO_H
#include <iostream>
#include <list>
#include <queue>
#include <climits>
#include <map>
#include "NodoAdya.hpp"
#include "NodoVertice.hpp"


template <class T, class C = int>
class Grafo
{
	private:
		NodoVertice<T,C> 	*ptrVertice;
		int nVertices, arcos;
        void copiarGrafo(NodoVertice<T,C> *ptrVer1);
        void eliminarArcoAux(NodoVertice<T,C>*  Nodo, const T vertice);
        void existeArcoAux(const T &inicio,const T &fin, bool &existe, C &peso);
		bool verificarAdya(const T &inicio, const T &fin, NodoVertice<T,C> *ptrVer)	const;
        NodoAdya<T,C>*	moverPtrAdya(NodoVertice<T,C> *ptrVer, const T &vertice) const;
        NodoVertice<T,C>*	moverVertice(NodoVertice<T,C> *ptrNodo, const T &vertice) const;
        NodoVertice<T,C>* buscarApuntador(const T &vertice) const;
        bool esIgual(const Grafo<T,C> &g) const;
        int getPosicionAux(const T &vertice, std::list<T> listaAux) const;
        void marcarVerticesLista(std::list<T> &lista);
        void DFSAUX(NodoVertice<T,C> *vertice, std::list<T> &lista);
        void caminoLargo(T vertice1, T vertice2, std::list<NodoVertice<T,C> *> &result, std::list<NodoVertice<T,C> *> caminoAct, C costo, C &costoMaximo);
	public:
    //Constructores
		Grafo():ptrVertice(0),nVertices(0),arcos(0){}
		Grafo(const Grafo<T,C> &g): ptrVertice(0),nVertices(0),arcos(0){*this=g;}
	//Modificadores
        void agregarVertice(const T &vertice);
        void agregarArco(const T &inicio, const T &fin, C costo = 0.0);
        void eliminarVertice(const T &vertice);
        void eliminarArco(const T &inicio, const T &fin);
        void marcarVertice(const T &vertice);
        void desmarcarVertice(const T &vertice);

        void desmarcarTodo();

	//Consultores

		bool esVacio() const {return ptrVertice ==NULL;}
		int  orden() const {return this->nVertices;}
        bool esBicoloreable() const;
		int  cardinalidadArcos() const {return this->arcos;}
		int  gradoVertice(const T &vertice)	const;
        bool existeVertice(const T &vertice) const;
        bool existeArco(const T &inicio, const T &fin);
        bool Adyacentes(const T &inicio, const T &fin) const;
        bool estaMarcado(const T &vertice) const;
        C CostoArco(const T &inicio, const T &fin);

        std::list<T> getCaminoMinimo(const T &vertice, const T &vertice2);
        std::list<T> getCaminoMaximo(const T &vertice, const T &vertice2);
        std::map<T,int> getMapa() const;
        std::list<T> getVertices()	const;
        std::list<T> getVecinos(const T &vertice) const;
        std::list<T> BFS(const T &vertice);
        std::list<T> getMarcados() const;
        std::list<T> DFS(const T vertice);
	//Sobrecarga de Operadores
		friend std::ostream& operator<< (std::ostream& os,const Grafo<T,C>& g)
        {
            // Declaramos dos punteros a objetos NodoVertice y NodoAdya
            NodoVertice<T,C> *ptrVer;
            NodoAdya<T,C> *ptrAdy;

            // Asignamos el puntero al primer vértice del grafo a ptrVer
            ptrVer = g.ptrVertice;

            // Mientras ptrVer no sea NULL
            while(ptrVer != NULL)
            {
                // Asignamos el puntero al primer vértice adyacente de ptrVer a ptrAdy
                ptrAdy = ptrVer->getAdya();

                // Si ptrAdy es NULL
                if(ptrAdy == NULL){
                    // Imprimimos el elemento de ptrVer
                    std::cout<<ptrVer->getElemento()<<std::endl;
                }else{
                    // Mientras ptrAdy no sea NULL
                    while(ptrAdy != NULL)
                    {
                        // Imprimimos el elemento de ptrVer y el elemento del vértice apuntado por ptrAdy
                        std::cout<<ptrVer->getElemento()<<"->"<<ptrAdy->getVertice()->getElemento()<<std::endl;
                        // Avanzamos ptrAdy al siguiente vértice adyacente
                        ptrAdy = ptrAdy->getProx();
                    }
                    std::cout<<std::endl;
                }
                // Avanzamos ptrVer al siguiente vértice
                ptrVer = ptrVer->getProx();
            }

            // Devolvemos la referencia al objeto ostream
            return os;
        }

		Grafo<T,C>& operator = (const Grafo<T,C>& g);
        bool operator != (const Grafo<T,C>& g) const;
        bool operator == (const Grafo<T,C>& g) const;
	//Destructor
		~Grafo();
};

// Define una plantilla de función que toma dos parámetros de plantilla: T y C
template<class T,class C>
// Define una función miembro de la clase Grafo que devuelve un std::list<T>
std::list<T> Grafo<T,C>::getCaminoMaximo(const T &vertice, const T &vertice2) {
    // Crea un std::list<NodoVertice<T,C> *> vacío para almacenar el resultado
    std::list<NodoVertice<T,C> *> listaResult;
    // Crea un std::list<NodoVertice<T,C> *> vacío para almacenar el camino actual
    std::list<NodoVertice<T,C> *> caminoActual;
    // Crea un std::list<T> vacío para almacenar la lista de retorno
    std::list<T> listaReturn;
    // Obtiene una lista de vértices marcados llamando a la función miembro getMarcados() de este objeto
    std::list<T> marcadosAux = this->getMarcados();
    // Inicializa el costo máximo en -1
    C costoMaximo = -1;
    // Inicializa el costo en 0
    C costo = 0;
    // Desmarca todos los vértices llamando a la función miembro desmarcarTodo() de este objeto
    this->desmarcarTodo();
    // Marca el primer vértice llamando a la función miembro marcarVertice() de este objeto con vertice como argumento
    this->marcarVertice(vertice);
    // Agrega el primer vértice al final de la lista de retorno
    listaReturn.push_back(vertice);
    // Llama a la función miembro caminoLargo() de este objeto con vertice, vertice2, listaResult, caminoActual, costo y costoMaximo como argumentos
    caminoLargo(vertice, vertice2, listaResult, caminoActual, costo, costoMaximo);
    // Para cada elemento en listaResult:
    for(typename std::list<NodoVertice<T,C> *>::iterator it = listaResult.begin(); it != listaResult.end(); it++){
        // Agrega el elemento del puntero al vértice actual al final de la lista de retorno
        listaReturn.push_back((*it)->getElemento());
    }
    // Marca los vértices en la lista marcadosAux llamando a la función miembro marcarVerticesLista() de este objeto con marcadosAux como argumento
    this->marcarVerticesLista(marcadosAux);
    // Devuelve la lista de retorno
    return listaReturn;
}

// Define una plantilla de función que toma dos parámetros de plantilla: T y C
template<class T,class C>
// Define una función miembro de la clase Grafo que no devuelve nada
void Grafo<T,C>::caminoLargo(T vertice1, T vertice2, std::list<NodoVertice<T,C> *> &result, std::list<NodoVertice<T,C> *> caminoAct, C costo, C &costoMaximo){
    // Obtiene un puntero al vértice especificado por vertice1 llamando a la función miembro moverVertice() de este objeto
    NodoVertice<T,C> *ptrVer = moverVertice(this->ptrVertice, vertice1);
    // Obtiene un puntero al primer vértice adyacente del vértice actual llamando a su función miembro getAdya()
    NodoAdya<T,C> *ptrAdya = ptrVer->getAdya();
    // Mientras haya más vértices adyacentes:
    while(ptrAdya != NULL){
        // Obtiene un puntero al vértice adyacente actual
        ptrVer = ptrAdya->getVertice();
        // Si el vértice adyacente actual no está marcado:
        if(!ptrVer->estaMarcado()){
            // Marca el vértice adyacente actual
            ptrVer->marcar();
            // Agrega el vértice adyacente actual al final de la lista caminoAct
            caminoAct.push_back(ptrAdya->getVertice());
            // Agrega el peso del borde entre el vértice actual y el vértice adyacente actual al costo total
            costo = costo + ptrAdya->getPeso();
            // Si el elemento del vértice adyacente actual es igual a vertice2:
            if(ptrVer->getElemento() == vertice2){
                // Si el costo total es mayor o igual que el costo máximo:
                if(costo >= costoMaximo){
                    // Establece result en caminoAct
                    result = caminoAct;
                    // Establece costoMaximo en costo
                    costoMaximo = costo;
                }
            }else{
                // Llama recursivamente a la función caminoLargo() con el elemento del vértice adyacente actual como primer argumento
                caminoLargo(ptrVer->getElemento(), vertice2, result, caminoAct, costo, costoMaximo);
            }
            // Resta el peso del borde entre el vértice actual y el vértice adyacente actual del costo total
            costo = costo - ptrAdya->getPeso();
            // Elimina el último elemento de la lista caminoAct
            caminoAct.pop_back();
            // Desmarca el vértice adyacente actual
            ptrVer->desmarcar();
        }
        // Mueve el puntero al siguiente vértice adyacente
        ptrAdya = ptrAdya->getProx();
    }
}

// Define una plantilla de función que toma dos parámetros de plantilla: T y C
template<class T, class C>
// Define una función miembro de la clase Grafo que devuelve un std::list<T>
std::list<T> Grafo<T,C>::getCaminoMinimo(const T &vertice, const T &vertice2) {
    // Crea un std::map<T,int> llamando a la función miembro getMapa() de este objeto
    std::map<T,int> mapa = this->getMapa();
    // Crea un std::list<T> vacío para almacenar el resultado
    std::list<T> listaResult;
    // Crea una matriz de T con tamaño nVertices para almacenar el vértice anterior para cada vértice en el grafo
    T anterior[this->nVertices];
    // Crea una matriz de C con tamaño nVertices para almacenar el peso acumulado para cada vértice en el grafo
    C acumulado[this->nVertices];
    // Crea una std::queue<NodoVertice<T,C> *> vacía para usar como estructura de datos auxiliar
    std::queue<NodoVertice<T,C> *> colaAux;
    // Obtiene un puntero al primer vértice del grafo llamando a la función miembro ptrVertice de este objeto
    NodoVertice<T,C> *ptrVer = this->ptrVertice;
    // Inicializa el peso acumulado para cada vértice a un valor grande (9999)
    for(int i = 0; i < this->nVertices; i++){
        acumulado[i] = 9999;
    }
    // Obtiene la posición del primer vértice en el mapa
    int pos = mapa[vertice];
    // Establece el peso acumulado para el primer vértice en 0
    acumulado[pos] = 0;
    // Establece el vértice anterior para el primer vértice en sí mismo
    anterior[pos] = vertice;
    // Mueve el puntero al primer vértice para que apunte al vértice especificado por vertice
    ptrVer = moverVertice(ptrVer, vertice);
    // Empuja el puntero al primer vértice en la cola auxiliar
    colaAux.push(ptrVer);
    // Mientras la cola auxiliar no esté vacía:
    while(!colaAux.empty()){
        // Obtiene un puntero al elemento frontal de la cola y lo elimina de la cola
        ptrVer = colaAux.front();
        colaAux.pop();
        // Obtiene la posición del vértice actual en el mapa
        pos = mapa[ptrVer->getElemento()];
        // Obtiene un puntero al primer vértice adyacente del vértice actual llamando a su función miembro getAdya()
        NodoAdya<T,C> *ptrAdy = ptrVer->getAdya();
        // Mientras haya más vértices adyacentes:
        while(ptrAdy != NULL){
            // Obtiene la posición del vértice adyacente actual en el mapa
            int posAdy = mapa[ptrAdy->getVertice()->getElemento()];
            // Si el peso acumulado para este vértice adyacente es mayor que
            //la suma del peso acumulado para el vértice actual y el peso del borde entre ellos:
            if(acumulado[posAdy] > acumulado[pos] + ptrAdy->getPeso()){
                // Actualiza el peso acumulado para este vértice adyacente con nuevo valor
                acumulado[posAdy] = acumulado[pos] + ptrAdy->getPeso();
                // Establece el vértice anterior para este vértice adyacente como vértice actual
                anterior[posAdy] = ptrVer->getElemento();
                // Empuja el puntero a este vértice adyacente en la cola auxiliar
                colaAux.push(ptrAdy->getVertice());
            }
            // Mueve el puntero al siguiente vértice adyacente
            ptrAdy = ptrAdy->getProx();
        }
    }
    // Obtiene la posición del segundo vértice en el mapa
    pos = mapa[vertice2];
    // Mientras que el vértice anterior para la posición actual no sea igual al primer vértice:
    while(anterior[pos] != vertice){
        // Empuja el vértice anterior al frente de la lista de resultados
        listaResult.push_front(anterior[pos]);
        // Actualiza la posición con la posición del vértice anterior en el mapa
        pos = mapa[anterior[pos]];
    }
    // Empuja los primeros y segundos vértices en la lista de resultados (en frente y atrás respectivamente)
    listaResult.push_front(vertice);
    listaResult.push_back(vertice2);
    // Devuelve la lista resultante
    return listaResult;
}

template<class T, class C>
std::map<T,int> Grafo<T,C>::getMapa() const {
    // Crea un mapa vacío
    std::map<T,int> mapa;
    // Obtiene un puntero al primer vértice del grafo
    NodoVertice<T,C> *ptrVer = this->ptrVertice;
    // Un entero para el valor mapeado
    int mapeado = 0;
    // Recorre la lista de vértices
    while(ptrVer != NULL){
        // Agrega el elemento y su valor mapeado al mapa
        mapa[ptrVer->getElemento()] = mapeado;
        // Incrementa el valor mapeado
        mapeado++;
        // Avanza al siguiente vértice
        ptrVer = ptrVer->getProx();
    }
    // Devuelve el mapa resultante
    return mapa;
}

template<class T, class C>
void Grafo<T,C>::DFSAUX(NodoVertice<T,C> *vertice, std::list<T> &lista){
    T elemento;
    // Obtiene el puntero al primer nodo adyacente al vértice dado
    NodoAdya<T,C> *adyacentes = vertice->getAdya();
    // Recorre la lista de nodos adyacentes
    while(adyacentes != NULL){
        // Obtiene el elemento del vértice adyacente
        elemento = adyacentes->getVertice()->getElemento();
        // Si el vértice adyacente no ha sido marcado
        if(!adyacentes->getVertice()->estaMarcado()){
            // Agrega el elemento a la lista
            lista.push_back(elemento);
            // Marca el vértice adyacente
            this->marcarVertice(elemento);
            // Llama recursivamente a DFSAUX con el vértice adyacente y la lista actualizada
            DFSAUX(adyacentes->getVertice(), lista);
        }
        // Avanza al siguiente nodo adyacente
        adyacentes = adyacentes->getProx();
    }
}

template<class T, class C>
std::list<T> Grafo<T,C>::DFS(T vertice){
    // Crea una copia de la lista de vértices marcados al principio para tener registro de que vertices estaban marcados
    std::list<T> copiaVisitados = this->getMarcados();
    // Crea una lista vacía para almacenar el resultado
    std::list<T> listaResult;
    // Obtiene un puntero al vértice inicial
    NodoVertice<T,C> *ptrVer = this->moverVertice(this->ptrVertice, vertice);
    // Agrega el elemento del vértice inicial a la lista de resultados
    listaResult.push_back(ptrVer->getElemento());
    // Desmarca todos los vértices del grafo
    this->desmarcarTodo();
    // Marca el vértice inicial
    ptrVer->marcar();
    // Llama a la función auxiliar DFSAUX con el puntero al vértice inicial y la lista de resultados
    DFSAUX(ptrVer, listaResult);
    // Vuelve a marcar los vértices que estaban marcados originalmente
    this->marcarVerticesLista(copiaVisitados);
    // Devuelve la lista de resultados
    return listaResult;
}

// Definición de la función 'marcarVerticesLista' para la clase 'Grafo'
// La función toma un parámetro de tipo 'std::list<T>&' llamado 'lista'
// y no devuelve ningún valor
template <class T, class C>
void Grafo<T,C>::marcarVerticesLista(std::list<T> &lista){
    // Declara un puntero a 'NodoVertice' llamado 'ptrVer'
    // y lo inicializa con el valor de 'this->ptrVertice'
    NodoVertice<T,C> *ptrVer = this->ptrVertice;

    // Mientras la lista 'lista' no esté vacía
    while(!lista.empty()){
        // Asigna a 'ptrVer' el resultado de llamar a la función miembro 'moverVertice'
        // con los argumentos 'ptrVer' y el primer elemento de la lista 'lista'
        ptrVer = this->moverVertice(ptrVer, lista.front());

        // Llama a la función miembro 'marcar' en 'ptrVer'
        if(ptrVer != NULL){
                ptrVer->marcar();
        }
        // Elimina el primer elemento de la lista 'lista'
        lista.pop_front();
    }
}

// Definición de la función 'estaMarcado' para la clase 'Grafo'
// La función toma un parámetro de plantilla 'T' llamado 'vertice'
// y devuelve un valor booleano
template <class T, class C>
bool Grafo<T,C>::estaMarcado(const T &vertice) const {
    // Declara un puntero a 'NodoVertice' llamado 'ptrVer'
    // y lo inicializa con el resultado de llamar a la función miembro 'moverVertice'
    // con los argumentos 'this->ptrVertice' y 'vertice'
    NodoVertice<T,C> *ptrVer = this->moverVertice(this->ptrVertice, vertice);

    // Devuelve el resultado de llamar a la función miembro 'estaMarcado' en 'ptrVer'
    return ptrVer->estaMarcado();
}

// Definición de la función 'getMarcados' para la clase 'Grafo'
// La función no toma parámetros y devuelve una lista de elementos de tipo 'T'
template <class T, class C>
std::list<T> Grafo<T,C>::getMarcados() const {
    // Declara una lista de elementos de tipo 'T' llamada 'marcados'
    std::list<T> marcados;

    // Declara un puntero a 'NodoVertice' llamado 'ptrVer'
    // y lo inicializa con el valor de 'this->ptrVertice'
    NodoVertice<T,C> *ptrVer = this->ptrVertice;

    // Mientras 'ptrVer' no sea NULL
    while(ptrVer != NULL){
        // Si el resultado de llamar a la función miembro 'estaMarcado' en 'ptrVer' es verdadero
        if(ptrVer->estaMarcado()){
            // Agrega el elemento en 'ptrVer' al final de la lista 'marcados'
            marcados.push_back(ptrVer->getElemento());
        }
        // Asigna a 'ptrVer' el resultado de llamar a la función miembro 'getProx' en 'ptrVer' para buscar el siguiente nodo
        ptrVer = ptrVer->getProx();
    }

    // Devuelve la lista 'marcados'
    return marcados;
}

// Definición de la función 'desmarcarVertice' para la clase 'Grafo'
// La función toma un parámetro de plantilla 'T' llamado 'vertice'
// y no devuelve ningún valor
// la función desmarca el vértice 'vertice' que recibe como parametro
template <class T, class C>
void Grafo<T,C>::desmarcarVertice(const T &vertice) {
    // Declara un puntero a 'NodoVertice' llamado 'ptrVer'
    // y lo inicializa con el resultado de llamar a la función miembro 'moverVertice'
    // con los argumentos 'this->ptrVertice' y 'vertice'
    NodoVertice<T,C> *ptrVer = this->moverVertice(this->ptrVertice, vertice);

    // Llama a la función miembro 'desmarcar' en 'ptrVer'
    ptrVer->desmarcar();
}

// Definición de la función 'marcarVertice' para la clase 'Grafo'
// La función toma un parámetro de plantilla 'T' llamado 'vertice'
// y no devuelve ningún valor
// La función marca el vértice 'vertice' que recibe como parametro
template <class T, class C>
void Grafo<T,C>::marcarVertice(const T &vertice) {
    // Declara un puntero a 'NodoVertice' llamado 'ptrVer'
    // y lo inicializa con el resultado de llamar a la función miembro 'moverVertice'
    // con los argumentos 'this->ptrVertice' y 'vertice'
    NodoVertice<T,C> *ptrVer = this->moverVertice(this->ptrVertice, vertice);

    // Llama a la función miembro 'marcar' en 'ptrVer'
    ptrVer->marcar();
}

// Definición de la función 'desmarcarTodo' para la clase 'Grafo'
// La función no toma parámetros y no devuelve ningún valor
// La función desmarca todos los vértices del grafo
template<class T, class C>
void Grafo<T,C>:: desmarcarTodo(){
    // Declara un puntero a 'NodoVertice' llamado 'ptrVer'
    // y lo inicializa con el valor de 'this->ptrVertice'
    NodoVertice<T,C> *ptrVer = this->ptrVertice;

    // Mientras 'ptrVer' no sea NULL
    while(ptrVer != NULL){
        // Llama a la función miembro 'desmarcar' en 'ptrVer'
        ptrVer->desmarcar();

        // Asigna a 'ptrVer' el resultado de llamar a la función miembro 'getProx' en 'ptrVer'
        ptrVer = ptrVer->getProx();
    }
}


// Definición de la función 'BFS' para la clase 'Grafo'
// La función toma un parámetro de plantilla 'T' llamado 'vertice'
// y devuelve una lista de elementos de tipo 'T'
template<class T, class C>
std::list<T> Grafo<T, C>:: BFS(const T &vertice){
    // Declara una lista de elementos de tipo 'T' llamada 'orden'
    std::list<T> orden;
    // Declara una lista con todos los elementos marcados para devolverla al estado inicial
    std::list<T> copiaMarcados = this->getMarcados();
    // Declara una cola de punteros a 'NodoVertice' llamada 'cola'
    std::queue<NodoVertice<T,C> *> cola;

    // Llama a la función miembro 'desmarcarTodo' en 'this'
    this->desmarcarTodo();
    // Declara un puntero a 'NodoVertice' llamado 'ptrVer'
    // y lo inicializa con el resultado de llamar a la función miembro 'moverVertice'
    // con los argumentos 'this->ptrVertice' y 'vertice' para movernos al vertice fuente
    NodoVertice<T,C> *ptrVer = this->moverVertice(this->ptrVertice, vertice);

    // Declara un puntero a 'NodoVertice' llamado 'ptrVerAux'
    NodoVertice<T,C> *ptrVerAux;

    // Llama a la función miembro 'marcar' en 'ptrVer'
    ptrVer->marcar();

    // Agrega 'ptrVer' al final de la cola 'cola'
    cola.push(ptrVer);

    // Declara un puntero a 'NodoAdya' llamado 'ptrAdya'

    NodoAdya<T,C> *ptrAdya = ptrVer->getAdya();

    // Mientras la cola 'cola' no esté vacía
    while(!cola.empty()){
        // Asigna a 'ptrVer' el primer elemento de la cola 'cola'
        ptrVer = cola.front();

        // Elimina el primer elemento de la cola 'cola'
        cola.pop();

        // Agrega el elemento en 'ptrVer' al final de la lista 'orden'
        orden.push_back(ptrVer->getElemento());

        // y lo inicializa con el resultado de llamar a la función miembro 'getPtrAdy' en 'ptrVer'
        ptrAdya = ptrVer->getAdya();

        // Mientras 'ptrAdya' no sea NULL
        while(ptrAdya != NULL){
            // Asigna a 'ptrVerAux' el resultado de llamar a la función miembro 'getVertice' en 'ptrAdya' para ir al primer vertice vecino
            ptrVerAux = ptrAdya->getVertice();

            // Si el resultado de llamar a la función miembro 'estaMarcado' en 'ptrVerAux' es falso quiere decir que no lo hemos visitado
            if(!ptrVerAux->estaMarcado()){
                // Llama a la función miembro 'marcar' en 'ptrVertice'
                ptrVerAux->marcar();

                // Agrega 'ptrVerAux' al final de la cola 'cola'
                cola.push(ptrVerAux);
            }

            // Asigna a 'ptrAdya' el resultado de llamar a la función miembro 'getProx' en 'ptrAdya' para ir al siguiente nodo
            ptrAdya = ptrAdya->getProx();
        }
    }
    //devolvemos el grafo al estado original
    this->marcarVerticesLista(copiaMarcados);

    // Devuelve la lista 'orden'
    return orden;
}

// Definición del operador de desigualdad '!=' para la clase 'Grafo'
// La función toma un parámetro de tipo 'const Grafo<T,C>&' llamado 'g'
// y devuelve un valor booleano
template <class T, class C>
bool Grafo<T,C>::operator != (const Grafo<T,C>& g) const
{
    // Devuelve el resultado de negar el resultado de llamar a la función miembro 'esIgual' en 'this'
    // con el argumento 'g'
    return !this->esIgual(g);
}

// Definición del operador de igualdad '==' para la clase 'Grafo'
// La función toma un parámetro de tipo 'const Grafo<T,C>&' llamado 'g'
// y devuelve un valor booleano
template <class T, class C>
bool Grafo<T,C>::operator == (const Grafo<T,C>& g) const
{
    // Devuelve el resultado de llamar a la función miembro 'esIgual' en 'this'
    // con el argumento 'g'
    return this->esIgual(g);
}



// Definición de la función 'esBicoloreable' para la clase 'Grafo'
template <class T, class C>
bool Grafo<T,C>::esBicoloreable() const{
    // Define los valores para representar los colores
    // 0 : NoColor
    // 1 : Color 1
    // 2 : Color 2
    const int NOCOLOR = 0;
    const int COLOR1 = 1;
    const int COLOR2 = 2;
    bool esBicoloreable=true;
    int color[this->nVertices];
    std::queue<NodoVertice<T,C> *> colaAux;
    NodoVertice<T,C> *verticeU, *verticeV;
    NodoAdya<T,C> *vecinos;
    std::map<T,int> mapa = this->getMapa();
    int i, posU,posV;
    // Inicializa todos los vértices sin color
    for( i = 0 ; i < this->nVertices ; i++){
        color[i]=NOCOLOR;
    }

    verticeU = this->ptrVertice;
    // Asigna el primer color al primer vértice
    color[mapa[verticeU->getElemento()]]=COLOR1;
    colaAux.push(verticeU);

    // Recorrido BFS
    while(!colaAux.empty() && esBicoloreable){
        // Tomamos el primer vértice de la cola
        verticeU=colaAux.front();
        // Avanzamos al siguiente vértice
        colaAux.pop();
        // Obtenemos los vecinos del vértice actual
        vecinos = verticeU->getAdya();
        // Obtenemos la posición del vértice actual en el mapa
        posU = mapa[verticeU->getElemento()];
        while(vecinos != NULL && esBicoloreable){
            //Tomamos el vertice adyacente
            verticeV = vecinos->getVertice();
            //Avanzamos al siguiente vertice
            vecinos = vecinos->getProx();
            //Obtenemos la posicion del vertice adyacente en el mapa
            posV = mapa[verticeV->getElemento()];
            // Si el vértice adyacente no tiene color asignado
            if(color[posV]==NOCOLOR){
                // Asigna el color opuesto al del vértice actual
                if(color[posU]==COLOR2){
                    color[posV]=COLOR1;
                }
                if(color[posU]==COLOR1){
                    color[posV]=COLOR2;
                }
                //Encolamos el vertice adyacente
                colaAux.push(verticeV);
            }else{
                // Si el vértice adyacente ya tiene un color asignado
                // Verifica si tiene el mismo color que el vértice actual
                if(color[posU]==color[posV]){
                    esBicoloreable=false;
                }
            }
        }
    }
    //Finalmente retornamos el valor de la variable booleana
    return esBicoloreable;
}

// Esta función verifica si dos grafos son iguales
template <class T, class C>
bool Grafo<T,C>::esIgual(const Grafo<T, C> &grafo) const {
    // Si el número de vértices o el número de arcos de los dos grafos es diferente, devuelve falso
    if(this->nVertices != grafo.nVertices || this->arcos != grafo.arcos) {
        return false;
    } else {
        // Declaración de punteros a vértices y adyacencias
        NodoVertice<T,C> *ptrVer, *ptrVerCOMP;
        ptrVerCOMP = grafo.ptrVertice;
        NodoAdya<T,C> *ptrAdy, *ptrAdyCOMP;
        // Declaración de variables booleanas
        bool bandPtrAdy;
        bool bandPtrAdyCOMP;
        bool bandPtrVer;
        bool bandPtrVerCOMP = true;
        // recorrido de la lista de vértices del grafo dado como parámetro
        while(ptrVerCOMP != NULL && bandPtrVerCOMP) {
            ptrVer = this->ptrVertice;
            bandPtrVer = false;
            // Búsqueda del vértice actual del grafo dado como parámetro en la lista de vértices del grafo instancia
            while(ptrVer != NULL && !bandPtrVer) {
                if(ptrVer->getElemento() == ptrVerCOMP->getElemento()) {
                    // Si se encontró el vértice
                    ptrAdyCOMP = ptrVerCOMP->getAdya();
                    bandPtrAdyCOMP = true;
                    // recorrido de la lista de adyacencias del vértice actual del grafo dado como parámetro
                    while(ptrAdyCOMP != NULL && bandPtrAdyCOMP) {
                        bandPtrAdy = false;
                        ptrAdy = ptrVer->getAdya();
                        // Búsqueda del arco actual del grafo dado como parámetro en la lista de adyacencias del vértice encontrado en el grafo instancia
                        while(ptrAdy != NULL && !bandPtrAdy) {
                            if(ptrAdy->getVertice()->getElemento() == ptrAdyCOMP->getVertice()->getElemento()) {
                                // Si se encontró el arco
                                if(ptrAdy->getPeso() == ptrAdyCOMP->getPeso()) {
                                    // Si el peso del arco es igual en ambos grafos
                                    bandPtrAdy = true;
                                }
                            }
                            ptrAdy = ptrAdy->getProx();
                        }
                        bandPtrAdyCOMP = bandPtrAdy;
                        ptrAdyCOMP = ptrAdyCOMP->getProx();
                    }
                    bandPtrVer = bandPtrAdyCOMP;
                }
                ptrVer = ptrVer->getProx();
            }
            bandPtrVerCOMP = bandPtrVer;
            ptrVerCOMP = ptrVerCOMP->getProx();
        }
        // Devuelve verdadero si los grafos son iguales, de lo contrario devuelve falso
        return bandPtrVerCOMP;
    }
}



template <class T, class C>
void Grafo<T,C>::agregarVertice(const T &vertice) {
    // Si el vértice está verificado o si no existe en el grafo
    if(!this->existeVertice(vertice)) {
        // Crea un nuevo nodo de vértice
        NodoVertice<T,C> *nodo;
        nodo = new NodoVertice<T,C>(vertice);
        // Establece el puntero siguiente del nuevo nodo al primer vértice actual
        nodo->setProx(this->ptrVertice);
        // Establece el nuevo nodo como el primer vértice
        this->ptrVertice = nodo;
        // Incrementa el número de vértices en el grafo
        this->nVertices++;
    }
}

template <class T, class C>
void Grafo<T,C>::agregarArco(const T &inicio,const T &fin, C costo) {
    // Declaración de punteros a vértices y adyacencias
    NodoVertice<T,C> *ptrVer, *ptrIni, *ptrFin;
    NodoAdya<T,C> *ptrAdy = NULL;
    // Inicialización de punteros
    ptrVer = ptrIni = ptrFin = NULL;
    // Asignación del primer vértice al puntero ptrVer
    ptrVer = this->ptrVertice;
    // Búsqueda de los vértices de inicio y fin en la lista de vértices
    while(ptrVer != NULL && (ptrIni == NULL || ptrFin == NULL)) {
        if(ptrVer->getElemento() == inicio) {
            ptrIni = ptrVer;
        }
        if(ptrVer->getElemento() == fin) {
            ptrFin = ptrVer;
        }
        ptrVer = ptrVer->getProx();
    }
    // Si el vértice final no existe, se agrega al grafo
    if(ptrFin == NULL) {
        ptrFin = new NodoVertice<T,C>;
        ptrFin->setElemento(fin);
        ptrFin->setProx(this->ptrVertice);
        this->ptrVertice = ptrFin;
        this->nVertices++;
    }
    // Si el vértice inicial no existe, se agrega al grafo y se asigna a ptrIni
    if(ptrIni == NULL) {
        ptrIni = new NodoVertice<T,C>;
        ptrIni->setElemento(inicio);
        ptrIni->setProx(this->ptrVertice);
        this->ptrVertice = ptrIni;
        this->nVertices++;
    }
    // Creación de un nuevo nodo de adyacencia y asignación a la lista de adyacencias del vértice inicial
    if(this->moverPtrAdya(ptrIni,fin) == NULL) {
        // Si el arco no existe en el grafo (no hay adyacencia entre los vértices)
        ptrAdy = new NodoAdya<T,C>(ptrFin,ptrIni->getAdya(),costo);
        ptrIni->setAdya(ptrAdy);
        ptrAdy = new NodoAdya<T,C>(ptrIni,ptrFin->getAdya(),costo);
        ptrFin->setAdya(ptrAdy);
        // Incremento del número de arcos en el grafo
        this->arcos++;
    }
}

template <class T, class C>
void Grafo<T,C>::eliminarVertice(const T &vertice) {
    // Declaración de punteros a vértices y adyacencias
    NodoVertice<T,C> *ptrVer, *ptrVerActual, *ptrVerAnt;
    NodoAdya<T,C> *ptrAdy, *ptrAdyActual;
    // Inicialización de punteros
    ptrVerActual = NULL;
    ptrVer = this->ptrVertice;
    // Búsqueda del vértice a eliminar en la lista de vértices
    while(ptrVer != NULL) {
        if(ptrVer->getElemento() == vertice) {
            // Asignación del vértice a eliminar al puntero ptrVerActual
            ptrVerActual = ptrVer;
            // Eliminación de la lista de adyacencias del vértice a eliminar
            ptrAdy = ptrVer->getAdya();
            while(ptrAdy != NULL) {
                ptrAdyActual = ptrAdy;
                this->arcos--;
                ptrAdy = ptrAdy->getProx();
                delete ptrAdyActual;
            }
        } else {
            // Eliminación de arcos que conectan al vértice a eliminar con otros vértices
            eliminarArcoAux(ptrVer,vertice);
        }
        if(ptrVerActual == NULL) {
            ptrVerAnt = ptrVer;
        }
        ptrVer = ptrVer->getProx();
    }
    // Si se encontró el vértice a eliminar
    if(ptrVerActual != NULL) {
        // Si el vértice a eliminar es el primer vértice de la lista
        if(this->ptrVertice->getElemento() == vertice) {
            this->ptrVertice = ptrVerActual->getProx();
        } else {
            // Si el vértice a eliminar no es el primer vértice de la lista
            ptrVerAnt->setProx(ptrVerActual->getProx());
        }
        // Decremento del número de vértices en el grafo
        this->nVertices--;
        delete ptrVerActual;
    }
}

template <class T, class C>
void Grafo<T,C>::eliminarArco(const T &inicio, const T &fin) {
    // Declaración de puntero a vértice
    NodoVertice<T,C> *ptrVer;
    // Búsqueda del vértice de inicio en la lista de vértices
    ptrVer = moverVertice(this->ptrVertice,inicio);
    // Si se encontró el vértice de inicio
    if(ptrVer != NULL) {
        // Eliminación del arco que conecta al vértice de inicio con el vértice final
        eliminarArcoAux(ptrVer,fin);
    }
    // Búsqueda del vértice de fin en la lista de vértices
    ptrVer = moverVertice(this->ptrVertice,fin);
    if(ptrVer != NULL) {
        // Eliminación del arco que conecta al vértice de inicio con el vértice final
        eliminarArcoAux(ptrVer,inicio);
    }
}

template <class T, class C>
bool Grafo<T,C>::existeVertice(const T &vertice) const {
    // Declaración de puntero a vértice
    NodoVertice<T,C> *ptrActual;
    // Asignación del primer vértice al puntero ptrActual
    ptrActual = this->ptrVertice;
    // Búsqueda del vértice en la lista de vértices
    while(ptrActual != NULL && ptrActual->getElemento() != vertice) {
        ptrActual = ptrActual->getProx();
    }
    // Si se encontró el vértice, devuelve verdadero, de lo contrario devuelve falso
    return ptrActual != NULL;
}

template <class T, class C>
bool Grafo<T,C>::existeArco(const T &inicio,const T &fin) {
    // Declaración de variable booleana y variable de peso
    bool existe = false;
    C peso;
    // Llamada a la función auxiliar para verificar si existe el arco
    existeArcoAux(inicio, fin, existe,peso);
    // Devuelve el valor de la variable booleana
    return existe;
}

template <class T, class C>
bool Grafo<T,C>::Adyacentes(const T &inicio, const T &fin) const {
    // Declaración de puntero a vértice
    NodoVertice<T,C> *ptrVer;
    // Declaración de variables booleanas
    bool inicioP, finP;
    inicioP = finP = false;
    // Asignación del primer vértice al puntero ptrVer
    ptrVer = this->ptrVertice;
    // Búsqueda de los vértices de inicio y fin en la lista de vértices
    while(ptrVer != NULL && !inicioP && !finP) {
        if(ptrVer->getElemento() == inicio) {
            inicioP = true;
        } else {
            if(ptrVer->getElemento() == fin) {
                finP = true;
            } else {
                ptrVer = ptrVer->getProx();
            }
        }
    }
    // Si se encontró alguno de los vértices de inicio o fin
    if (ptrVer != NULL) {
        // Si se encontró el vértice de inicio
        if (inicioP) {
            // Llamada a la función auxiliar para verificar si los vértices son adyacentes
            return verificarAdya(inicio, fin, ptrVer);
        } else {
            // Si se encontró el vértice final
            return verificarAdya(fin, inicio, ptrVer);
        }
    } else {
        // Si no se encontró ninguno de los vértices de inicio o fin, devuelve falso
        return false;
    }
}

// Esta función devuelve una lista de los predecesores de un vértice dado en el grafo

// Esta función devuelve una lista de los sucesores de un vértice dado en el grafo
template <class T, class C>
std::list<T> Grafo<T,C>::getVecinos(const T &vertice) const {
    // Declaración de lista de sucesores
    std::list<T> sucesores;
    // Declaración de punteros a vértices y adyacencias
    NodoVertice<T,C> *ptrVer;
    NodoAdya<T,C> *ptrAdy;
    // Búsqueda del vértice dado en la lista de vértices
    ptrVer = moverVertice(this->ptrVertice,vertice);
    // Si se encontró el vértice dado
    if(ptrVer != NULL) {
        // Asignación de la lista de adyacencias del vértice dado al puntero ptrAdy
        ptrAdy = ptrVer->getAdya();
        // recorrido de la lista de adyacencias del vértice dado
        while(ptrAdy != NULL) {
            // Agrega el vértice adyacente a la lista de sucesores
            sucesores.push_back(ptrAdy->getVertice()->getElemento());
            // Marca el vértice adyacente como visitado
            ptrAdy = ptrAdy->getProx();
        }
    }
    // Devuelve la lista de sucesores del vértice dado
    return sucesores;
}

// Esta función devuelve una lista de los vértices del grafo
template <class T, class C>
std::list<T> Grafo<T,C>::getVertices() const {
    // Declaración de lista de vértices
    std::list<T> l;
    // Declaración de puntero a vértice
    NodoVertice<T,C> *ptrVer;
    // Asignación del primer vértice al puntero ptrVer
    ptrVer = this->ptrVertice;
    // recorrido de la lista de vértices
    while(ptrVer) {
        // Agrega el elemento del vértice actual a la lista de vértices
        l.push_back(ptrVer->getElemento());
        ptrVer = ptrVer->getProx();
    }
    // Devuelve la lista de vértices del grafo
    return l;
}

//Protegidos
template <class T, class C>
NodoVertice<T,C>* Grafo<T,C>::buscarApuntador(const T &vertice) const
{
    // Declaramos un puntero a un objeto NodoVertice
    NodoVertice<T,C> *ptrNodo;

    // Asignamos el puntero al primer vértice del grafo a ptrNodo
    ptrNodo = this->ptrVertice;

    // Mientras el elemento de ptrNodo no sea igual al valor del vértice dado
    while(ptrNodo->getElemento() != vertice)
    {
        // Avanzamos ptrNodo al siguiente vértice
        ptrNodo = ptrNodo->getProx();
    }

    // Devolvemos el valor de ptrNodo
    return ptrNodo;
}

template <class T, class C>
inline bool Grafo<T,C>::verificarAdya(const T &inicio, const T &fin, NodoVertice<T,C> *ptrVer) const
{
    // Si no existe un arco entre ptrVer y el vértice con el valor dado
    if (moverPtrAdya(ptrVer, fin) == NULL) {
        // Obtenemos un puntero al objeto NodoVertice que representa el vértice con el valor dado
        NodoVertice<T,C> *ptrVerAux = moverVertice(ptrVer, fin);
        // Si ptrVerAux es NULL
        if (ptrVerAux == NULL) {
            // Devolvemos false
            return false;
        } else {
            // Devolvemos true si existe un arco entre ptrVerAux y el vértice con el valor dado
            return (moverPtrAdya(ptrVerAux, inicio) != NULL);
        }
    } else {
        // Devolvemos true
        return true;
    }
}

//Si existe el arco devuelve true y el peso del arco
template <class T, class C>
void Grafo<T,C>::existeArcoAux(const T &inicio,const T &fin, bool &existe, C &peso)
{
    // Declaramos dos punteros a objetos NodoVertice y NodoAdya
    NodoVertice<T,C> *ptrVer;
    NodoAdya<T,C> *ptrAdy;

    // Asignamos el puntero al primer vértice del grafo a ptrVer
    ptrVer = this->ptrVertice;
    // Inicializamos ptrAdy con NULL
    ptrAdy = NULL;

    // Mientras ptrVer no sea NULL y no se haya encontrado el arco
    while(ptrVer && !existe)
    {
        // Si el elemento de ptrVer es igual al valor del vértice de inicio
        if(ptrVer->getElemento() == inicio)
        {
            // Asignamos el puntero al objeto NodoAdya que representa el arco entre ptrVer y el vértice con el valor dado a ptrAdy
            ptrAdy = moverPtrAdya(ptrVer, fin);
            // Si ptrAdy no es NULL
            if( ptrAdy != NULL)
            {
                // Asignamos true a la variable booleana
                existe = true;
                // Asignamos el peso del arco a la variable de peso
                peso = ptrAdy->getPeso();
            }
            else{
                // Asignamos NULL a ptrVer para salir del bucle
                ptrVer = NULL;
            }
        }
        // Si ptrVer no es NULL
        if(ptrVer != NULL){
            // Avanzamos ptrVer al siguiente vértice
            ptrVer = ptrVer->getProx();
        }
    }
}

template <class T, class C>
void Grafo<T,C>::copiarGrafo(NodoVertice<T,C> *ptrVer1)
{
    // Declaramos tres punteros a objetos NodoVertice
    NodoVertice<T,C> *ptrAux, *ptrAux2,*ptrAux3;
    // Declaramos tres punteros a objetos NodoAdya
    NodoAdya<T,C> *ptrAdy, *ptrAdy2,*ptrAdy3;

    // Inicializamos ptrAux con el puntero pasado como argumento
    ptrAux = ptrVer1;
    // Inicializamos ptrAux2 con el puntero al primer vértice del grafo
    ptrAux2 = this->ptrVertice;

    // Mientras ptrAux no sea NULL
    while(ptrAux != NULL)
    {
        // Si el puntero al primer vértice del grafo es NULL
        if(this->ptrVertice == NULL)
        {
            // Creamos un nuevo objeto NodoVertice con el elemento de ptrAux y lo asignamos a ptrVertice
            this->ptrVertice = new NodoVertice<T,C>(ptrAux->getElemento());
            // Asignamos ptrVertice a ptrAux2
            ptrAux2 = this->ptrVertice;
        }
        else
        {
            // Creamos un nuevo objeto NodoVertice con el elemento de ptrAux y lo asignamos al siguiente vértice de ptrAux2
            ptrAux3 = new NodoVertice<T,C>(ptrAux->getElemento());
            ptrAux2->setProx(ptrAux3);
            // Avanzamos ptrAux2 al siguiente vértice
            ptrAux2=ptrAux2->getProx();
        }
        // Avanzamos ptrAux al siguiente vértice
        ptrAux = ptrAux->getProx();
    }

    // Reinicializamos ptrAux2 con el puntero al primer vértice del grafo
    ptrAux2 = this->ptrVertice;
    // Reinicializamos ptrAux con el puntero pasado como argumento
    ptrAux = ptrVer1;

    // Mientras ptrAux no sea NULL
    while(ptrAux != NULL)
    {
        // Inicializamos ptrAdy con el puntero al primer vértice adyacente de ptrAux
        ptrAdy = ptrAux->getAdya();
        // Inicializamos ptrAdy2 con el puntero al primer vértice adyacente de ptrAux2
        ptrAdy2 = ptrAux2->getAdya();

        // Mientras ptrAdy no sea NULL
        while(ptrAdy!=NULL)
        {
            // Si el puntero al primer vértice adyacente de ptrAux2 es NULL
            if(ptrAdy2 == NULL)
            {
                // Creamos un nuevo objeto NodoAdya con el apuntador al vértice correspondiente y el peso de la arista y lo asignamos a la lista de adyacencia de ptrAux2
                ptrAdy2 = new NodoAdya<T,C>(buscarApuntador(ptrAdy->getVertice()->getElemento()),NULL,ptrAdy->getPeso());
                ptrAux2->setAdya(ptrAdy2);
            }
            else
            {
                // Creamos un nuevo objeto NodoAdya con el apuntador al vértice correspondiente y el peso de la arista y lo asignamos al siguiente vértice adyacente de ptrAdy2
                ptrAdy3 = new NodoAdya<T,C>(buscarApuntador(ptrAdy->getVertice()->getElemento()),NULL,ptrAdy->getPeso());
                ptrAdy2->setProx(ptrAdy3);
                // Avanzamos ptrAdy2 al siguiente vértice adyacente
                ptrAdy2 = ptrAdy2->getProx();
            }
            // Avanzamos ptrAdy al siguiente vértice adyacente
            ptrAdy = ptrAdy->getProx();
        }
        // Avanzamos ptrAux2 al siguiente vértice
        ptrAux2 = ptrAux2->getProx();
        // Avanzamos ptrAux al siguiente vértice
        ptrAux = ptrAux->getProx();
    }
}

template <class T, class C>
int Grafo<T,C>::gradoVertice(const T &vertice)const
{
    // Declaramos una variable entera para almacenar el grado del vértice
    int grado = 0;
    // Declaramos dos punteros a objetos NodoVertice y NodoAdya
    NodoVertice<T,C> *ptrVer;
    NodoAdya<T,C> *ptrAdy;

    // Asignamos el puntero al primer vértice del grafo a ptrVer
    ptrVer = this->ptrVertice;

    // Mientras ptrVer no sea NULL
    while(ptrVer != NULL )
    {
        // Asignamos el puntero al primer vértice adyacente de ptrVer a ptrAdy
        ptrAdy = ptrVer->getAdya();

        // Mientras ptrAdy no sea NULL
        while(ptrAdy != NULL)
        {
            // Si el elemento del vértice apuntado por ptrAdy es igual al valor del vértice dado o el elemento de ptrVer es igual al valor del vértice dado
            if(ptrAdy->getVertice()->getElemento() == vertice  ||  ptrVer->getElemento() == vertice){
                // Incrementamos en uno el grado del vértice
                grado++;
            }
            // Avanzamos ptrAdy al siguiente vértice adyacente
            ptrAdy = ptrAdy->getProx();
        }
        // Avanzamos ptrVer al siguiente vértice
        ptrVer = ptrVer->getProx();
    }

    // Devolvemos el valor del grado del vértice
    return grado;
}

template <class T, class C>
void Grafo<T,C>::eliminarArcoAux(NodoVertice<T,C>* Nodo, const T vertice)
{
    // Declaramos dos punteros a objetos NodoAdya
    NodoAdya<T,C> *ptrAdy, *ptrAdyAnt;
    // Declaramos una variable booleana para indicar si se ha encontrado el arco a eliminar
    bool encontrado = false;

    // Inicializamos ptrAdyAnt con 0
    ptrAdyAnt = 0;
    // Inicializamos ptrAdy con el puntero al primer vértice adyacente de Nodo
    ptrAdy= Nodo->getAdya();

    // Mientras ptrAdy no sea NULL y no se haya encontrado el arco a eliminar
    while(ptrAdy != NULL && !encontrado)
    {
        // Si el elemento del vértice apuntado por ptrAdy es igual al valor del vértice dado
        if(ptrAdy->getVertice()->getElemento()==vertice)
        {
            // Si el elemento del primer vértice adyacente de Nodo no es igual al valor del vértice dado
            if (Nodo->getAdya()->getVertice()->getElemento() != vertice) {
                // Asignamos el siguiente vértice adyacente de ptrAdy como el siguiente vértice adyacente de ptrAdyAnt
                ptrAdyAnt->setProx(ptrAdy->getProx());
            } else {
                // Asignamos el siguiente vértice adyacente de ptrAdy como el primer vértice adyacente de Nodo
                Nodo->setAdya(ptrAdy->getProx());
            }
            // Indicamos que se ha encontrado el arco a eliminar
            encontrado = true;
            // Asignamos NULL como el siguiente vértice adyacente de ptrAdy
            ptrAdy->setProx(NULL);
            // Eliminamos el objeto apuntado por ptrAdy
            delete ptrAdy;
            // Decrementamos en uno la cantidad de arcos del grafo
            this->arcos--;
        }else{
            // Asignamos ptrAdy a ptrAdyAnt
            ptrAdyAnt = ptrAdy;
            // Avanzamos ptrAdy al siguiente vértice adyacente
            ptrAdy = ptrAdy->getProx();
        }
    }
}

template <class T, class C>
NodoAdya<T,C>* Grafo<T,C>::moverPtrAdya(NodoVertice<T,C> *ptrVer, const T &vertice) const
{
    // Declaramos un puntero a un objeto NodoAdya e inicializamos con NULL
    NodoAdya<T,C> *ptrAdy = NULL;

    // Asignamos el puntero al primer vértice adyacente de ptrVer a ptrAdy
    ptrAdy = ptrVer->getAdya();

    // Mientras ptrAdy no sea NULL y el elemento del vértice apuntado por ptrAdy no sea igual al valor del vértice dado
    while(ptrAdy != NULL && ptrAdy->getVertice()->getElemento()!=vertice)
    {
        // Avanzamos ptrAdy al siguiente vértice adyacente
        ptrAdy = ptrAdy->getProx();
    }

    // Devolvemos el valor de ptrAdy
    return ptrAdy;
}

template <class T, class C>
NodoVertice<T,C>* Grafo<T,C>::moverVertice(NodoVertice<T,C> *ptrNodo, const T &vertice) const
{
    // Declaramos un puntero a un objeto NodoVertice
    NodoVertice<T,C> *ptrVer;

    // Asignamos el puntero pasado como argumento a ptrVer
    ptrVer = ptrNodo;

    // Mientras ptrVer no sea NULL y el elemento de ptrVer no sea igual al valor del vértice dado
    while(ptrVer != NULL && ptrVer->getElemento() != vertice)
    {
        // Avanzamos ptrVer al siguiente vértice
        ptrVer = ptrVer->getProx();
    }

    // Devolvemos el valor de ptrVer
    return ptrVer;
}


template <class T, class C>
Grafo<T,C>::~Grafo()
{
    // Declaramos dos punteros a objetos NodoVertice y NodoAdya y un puntero auxiliar
    NodoVertice<T,C> *ptrVer;
    NodoAdya<T,C> *ptrAdy, *ptrAux;

    // Mientras el puntero al primer vértice del grafo no sea NULL
    while(ptrVertice != NULL)
    {
        // Asignamos el puntero al primer vértice del grafo a ptrVer
        ptrVer = this->ptrVertice;
        // Asignamos el puntero al primer vértice adyacente de ptrVer a ptrAux
        ptrAux = ptrVer->getAdya();
        // Asignamos el siguiente vértice de ptrVer como el primer vértice del grafo
        this->ptrVertice = ptrVer->getProx();

        // Mientras ptrAux no sea NULL
        while( ptrAux != NULL)
        {
            // Asignamos ptrAux a ptrAdy
            ptrAdy = ptrAux;
            // Asignamos el siguiente vértice adyacente de ptrAdy a ptrAux
            ptrAux = ptrAdy->getProx();
            // Eliminamos el objeto apuntado por ptrAdy
            delete ptrAdy;
        }
        // Eliminamos el objeto apuntado por ptrVer
        delete ptrVer;
    }

    // Asignamos NULL al puntero al primer vértice del grafo
    this->ptrVertice = NULL;
    // Asignamos 0 a la cantidad de vértices y arcos del grafo
    this->nVertices = 0;
    this->arcos = 0;
}


template <class T, class C>
Grafo<T,C>& Grafo<T,C>::operator = (const Grafo<T,C>& g)
{
    // Llamamos al destructor para liberar la memoria dinámica utilizada por el objeto
    this->~Grafo();
    // Copiamos el grafo representado por el puntero al primer vértice de g en el objeto
    this->copiarGrafo(g.ptrVertice);
    // Asignamos la cantidad de vértices de g a la cantidad de vértices del objeto
    this->nVertices = g.nVertices;

    // Devolvemos una referencia al objeto
    return *this;
}
#endif
//"La música es el corazón de la vida. Por ella habla el amor; sin ella no hay bien posible y con ella todo es hermoso."
// Franz Liszt (1811-1886) Compositor húngaro.
//                   .  ...   .                                                                         ....................................    ...  ...
//                    .         ...  .  .                                                                       ....................................   .
//                   . . ..                                                                             .  ..  .........................................
//              . .   .                                                                               .......   .. .................... ....  .... .....
//                                                                                        .           .... ................................ ...... .....
//                                                                                             ....     .............................. . ...............
//                                                                                                ...   ......... .. ........ ......... ..  .. ...  ....
//                                                             .   . .                                ....    ....        ..............  .  ....... ...
//                                                       .......,,,,,,,....     ..                .....  . ..... .        .......... ...................
//                                             .....,,,,..,,,*((///*. ........                    ....................   ....... ...............  ... ..
//                                          ......,,/(/*/*/(####/*,,,*/////*,. .                  ... ............................................ .. ..
// //                                      .....,*//,.,,/###%#((///(((((//**,...,....     .          ................................................ ..
//                                     .......,,(     ,*/%#%%%%%%%%%%%#%%%%%%#(***,,**,....  ..          ...............................................
//    .              .                 .....,....  ..*(%%%%%&&&&&&&&&&&&&&&&&&%%##((((/***,,,.....         .............................................
//   .....                         ........,,.....*(#%%%%&&&&&&&&&&&&&&@&&&&&&&%%%%######(*,***,....   ..   ............................................
//.  ...  .                      ... .....,,,..,*/#%%%&&&&&&&&&&&&&&&&@@@@@&&&&&&%%%%%%###/**,,,,,....  ...   ..........................................
// ......                   . .  ..........,..,*(#%%&&&&&&&&&&&@&&@@@@&&&@&&&&&%%%%%%%%%###/*,,,,.,,...   ..............................................
// ..... . .. .          . ..............,,,.,*(#%%%&&&&&&&&&@&@&&@@@@@@@&&&&&%%%%%%%#%####//*,,,..,*,. . . .. .........................................
//. ... .......              ............,,.,,/#%%%&&&&&&&&&&&&@&&&&@@&@&&&&%%%%%%%%%%###((//*,,,....,,. ..... .........................................
//... .......       .. ..     ...........,,,,*##%%%%&&&&&&&&&&%%%%&&%%&%%%%#%#%%######((((/****...,... . .....    ..........,...........................
//........           .      ............,,.,*#######%%%%&%%%#(/*,,**/////*//**/((((((((/*/**,,,,......... .......    ...,,..............................
//.... .. .          ...  ... ..  ......,..*((//(,..,,/##%%#(*,**,,**//*,,*//***////////**,,,,........    .  ...     ...,...............................
//.           ..     . .. .....    ......,*(/,,,,,,,***/%%%%(******#*,*((*,,*///////(((//*,,,..............  ...   .....................................
//.        ..... .  ... ................,,,,,**,*,*/#%##%%#(///##(###%%%#((*/##%%####(#(**,,,...,.......... .. .   ......,,,,,..,,...................,,.
//...     . .. ....... .................,,.***///(#######(//((##%%%%&%%%%%%%%%&%%%%###((/*,..,.............          .....,....,...,,...............,,,,
//...  ......  .......   ...  .........,.,/,,/(((#%%%#%#((((###%%&&%%%%%&%&%&&%%%####(//*,...,,......  ... ..        ..........,.,,,,...............,,,.
//....................  ...  ..........,,,*,,####%%%#%###((#(##%%&&&&&&%%%%&%%%%%###(/**,,..........    .. .. ....    .............................,,...
//............ .....         .............,.*(##%%%%&%#(//((((#%%&&&&&%%%&%%%%%##(((/**,,.. ...,.....    ..     ..    ..................................
//...........   .   .    ..... . ...........*(##%%#&%##((/###(*#%%&%%%%%%%%%%%##((//**,,,... ...... .                  .................................
//......... ..... .    ..  .............,.. ./(###(((/,,...,***(%#%%%%%%%%%%%%###(//***,..... .....                   . ................................
//...... . ...  .    ..    .. .... ....,, ...*(((((#/(/,,*/((##%%%%%##%%%%%%%%##((////*,..,,,    ..                      ...............................
//........... .. ... ..   .......  ....,,. ..,((##%%#%%#%%%%#####%%%#####%%%%%%##(///**,..,*/,......              .   .   ..............................
//................................ ....,,....,/(###%##%&%%%%#%#%##########%%%%%##((//**,...,*,.. ....                .     .............................
//....................................... .  .*(###(/,,*****//*****(#######%%%##((//***,. ....  ..,.                        ............................
//..................................... . . ,.,/#####/(//*///(((##%%%%######%###((//***,,... .. *,,.,                        ...........................
//..............................  ..... .  ....*(##%%#(((((((#####%%%####(####((///**,,,,.... . ,,,.                          ..........................
//,..,..........,.........................  ....*((##%%%%%%%%%%%######(((/((((//***,,,.,,,.......,.                            .........................
//,...,....................,............       ..*(##%%#%%%%%%#%%###(///*****,,,,*,,,,,,..,*,,...,.                              .......................
//,.............,........................     ..../#############((/*,,,,,,,,,***,*,,,,,.*(/**,.. ..               .    ..         ......................
//...........,...,,,.,...................   ...... ,(((/*****,,,..,,,,,,,,,,*****,,,,*%%###(/,..             .,,,,,,,. .           .....................
//....,...,.,,.,.,,.,,,..,...........,...   .,. .. ...,,,,.,,,,,,,,,,,,,,,****,,,,*(@@@%%%%%##(,, ..   .......,***/,,                    ...............
//,,...,.,,,,,,,.....................,......, ....      ...  ..,,,,,,*,,,,,*,,***#@@@@%%%%%###%#/,/*,...,,,*****/,...  ..               ................
//.........,.,.,,,...............,,..,.. ... ..,.,.    . .... .......,,,,,,,**%&@@@@@&&%%%%%####%#/,,.......,,,....                   ..................
//..,..,,,,,....,...................,,,.,,*.....,.    ..  . . .((*,,,,,,,,/%&@@@@@@&&&%%&%%%%%%%##.        . . ...                    .  ...............
//....,,.,,.......................,,,,,*** .   ,     .   ...*&/(((((//**(&@@@@@@@@@&&&%%%%%%%&@(.                                 ......................
//................................,,,,**,..  ...   ......*&&&%%((((((((&&@@@@@@@@&&&%%%%%%&@@@/.                                .............,,,,.......
//...................................*.... ........,,.*#&%%&&%%#(((((/.....(&@@@&&%%%%%@@@@@(.                                            ......,,,,....
//....,,..............................  ...... ..,,,*%&&&&&&%%%%(((/(/..    .,%%&&&&@@@@&@, .                                     .        .   ....,,,,,
//..............................................,,,/&&&&&%*..,,,*/(##%.      . ,&@&@&@&%.                       ...       .  .                   . ..,,,
//..........................................,,,,,*%&&&#,.       .*,,..           .#&#. .                                          .             .......,
//..........................................,,,*#%%(,..                                                                                           ... ..
//.............,,.................,.......,,,((*,.....                                                                    .      ...  .         .......
//..,.........,,.........................,,,.,.....                                              ..                      ...                  .......  .
//..............,......................,,,,,,,,..                                            ...                                               .........
//.................,..........,.....,.,,,,,....                                                                                       .  . .. ... ......
//...............,,,...........,.....,,,,....                           .,*,                                              .      ..            .........
//..,..........................,,,,,,....                       ,*,.*/((((/.. ..                                         ...            ..   ...........
//............................,,,,,.....                      .//((((((//..  ....                                        ..       ......     ...........
//..........,,,,.......,,..,.,,,,...                        .(((#(((//*.                       .      ...     ....   .....................  ............
//,..,.....,.,.,,,,,,,,,,,,,,,...                          ,/#////**.   .                                           .. .............. ......  ..........
//,,,........,,,,,,,,,,,,,....                            *(///**.                            .             ..... .... .................................
//,,,........,,.,,,,,,,,...                           . .*/***..                          ..  ..        ..........  ....................................
//........,.,,.,,,,,,,.....                            *,*,,.                             ..  ..........................................................
//......,,.,,,,,,,,,,....       ..            .       ,,...                              ...................................... ........................
//,,,,,,,,,,,,,,,,,,.... .                           ...  .       .......              .....................................    ........................
//,..,,..,,,,,,,,,,......                       .  ..                          ......................................   ..      ........................
//,..,,...,,,,,,,......                        . ...                                  .  ................ ...          ..... .  ........................
//........,,.,,.. ...                         .                                   ..  . ..........  ..........        .  ...............................
//........,,,.....                                                                ..   ..... ..                     ....................................
//,,.,,........                                                                      .... ....                 .........................................
//.......,....                                                               .  ..                           ...........................................
//,.....,...   .    .                                                        .....                        .....................  .......................
//,..,.,.....     .                                                   .     ...                       ........... ..........      ......................
//.,,,...                                                                    ..    ...            ...... .  ............................................