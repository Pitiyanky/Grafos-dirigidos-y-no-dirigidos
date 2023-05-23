#include <iostream>
#include "Grafo.hpp"
#include <list>

int main()
{
	Grafo<char> p,k;
    Grafo<char> g,h;
//	char vertice1, vertice2;
	std::list<char> pasos,optima;
    std::cout<<"Comenzamos"<<std::endl;

	p.agregarArco('a','b',5);
	p.agregarArco('a','c',2);
	p.agregarArco('b','c',1);
	p.agregarArco('c','f',4);
	p.agregarArco('e','b',6);
	p.agregarArco('e','f',8);
	p.agregarArco('e','a',4);
	p.agregarArco('d','f',6);
	p.agregarArco('d','c',9);
	p.agregarArco('d','e',1);
	p.agregarArco('f','t',1);
    //std::cout<<"Imprimimos P"<<std::endl;
    std::cout<<"P:"<<std::endl<<p;
    pasos = p.DFS('a');
    if(p.esBicoloreable()){
        std::cout<<"Es bicoloreable"<<std::endl;
    }else{
        std::cout<<"No es bicoloreable"<<std::endl;
    }
    std::cout<<"DFS:"<<std::endl;
    for(std::list<char>::iterator it = pasos.begin(); it != pasos.end(); ++it)
        std::cout<<*it<<" ";
    std::cout<<std::endl;
    pasos = p.BFS('a');
    std::cout<<"DFS:"<<std::endl;
    for(std::list<char>::iterator it = pasos.begin(); it != pasos.end(); ++it)
        std::cout<<*it<<" ";
    std::cout<<std::endl<<"Camino minimo entre a y t:"<<std::endl;
    std::list<char> camino = p.getCaminoMinimo('a','t');
    for(std::list<char>::iterator it = camino.begin(); it != camino.end(); ++it)
        std::cout<<*it<<" ";
    std::cout<<std::endl<<"Camino maximo entre a y t:"<<std::endl;
    camino = p.getCaminoMaximo('a','t');
    std::cout<<"Imprimimos el camino maximo"<<std::endl;
    for(std::list<char>::iterator it = camino.begin(); it != camino.end(); ++it)
        std::cout<<*it<<" ";
    std::cout<<std::endl;
    std::cout<<"salimos"<<std::endl;
    h.agregarArco('a','b');
    h.agregarArco('a','f');
    h.agregarArco('b','c');
    h.agregarArco('c','f');
    h.agregarArco('e','b');
    h.agregarArco('e','f');
    h.agregarArco('e','a');
    h.agregarArco('d','f');
    h.agregarArco('d','e');
    h.agregarArco('d','c');
    h.agregarArco('d','e');
    h.agregarArco('f','t');
    h.agregarArco('f','t');
    std::cout<<"vecinos"<<std::endl<<h;
    std::list<char> vecinos = h.getVecinos('d');
    std::cout<<"Vecinos de d:"<<std::endl;
    for(std::list<char>::iterator it = vecinos.begin(); it != vecinos.end(); ++it)
        std::cout<<*it<<" ";
    std::cout<<std::endl;
    k.agregarArco('a','b');
    k.agregarArco('a','c');
    k.agregarArco('d','f');
    k.agregarArco('d','e');
    k.agregarArco('d','c');
    k.agregarArco('d','e');
    k.agregarArco('f','t');
    k.agregarArco('f','t');

    g.agregarArco('d','f');
    g.agregarArco('d','e');
    g.agregarArco('d','e');
    g.agregarArco('f','t');
    g.agregarArco('a','b');
    g.agregarArco('a','c');
    g.agregarArco('d','c');
    g.agregarArco('f','t');
    std::list<char> vertices = g.getVertices();
    std::cout<<"Vertices de g:"<<std::endl;
    for(std::list<char>::iterator it = vertices.begin(); it != vertices.end(); ++it)
        std::cout<<*it<<" ";
	std::cout<<"K:"<<std::endl<<k;

    if ( p==k) {
        std::cout<<"Son iguales"<<std::endl;
    }else{
        std::cout<<"No son iguales"<<std::endl;
    }
    std::cout<<"G:"<<std::endl<<g;
    if ( k==g ) {
        std::cout << "Son iguales" << std::endl;
    }else{
        std::cout<<"No son iguales"<<std::endl;
    }
    std::cout<<"H:"<<std::endl<<h;

    if ( p!=h ) {
        std::cout<<"No son iguales"<<std::endl;

    }else{
        std::cout << "Son iguales" << std::endl;
    }
    p.eliminarArco('a','b');
    std::cout<<"P:"<<std::endl<<p;
    //Prueba bicoloreable
    Grafo<char> b;
    b.agregarArco('a','c');
    b.agregarArco('b','c');
    b.agregarArco('c','d');
    b.agregarArco('c','e');
    if(b.esBicoloreable()) {
        std::cout << "Es bicoloreable" << std::endl;
    }else{
        std::cout<<"No es bicoloreable"<<std::endl;
    }
    return 0;

}
/*
list<char> OrdTop(Grafo<char> g)
{
	list<char> suc, fuente,recorrido;
	char vertice;

	fuente = g.Fuentes();

	while(!fuente.esVacia())
	{
		vertice = fuente.consultar(1);
		fuente.eliminar(1);
		recorrido.insertar(vertice,recorrido.longitud()+1);
		suc = g.Sucesores(vertice);
		g.EliminarVertice(vertice);
		while(!suc.esVacia())
		{
			vertice = suc.consultar(1);
			suc.eliminar(1);
			if(g.Predecesores(vertice).esVacia())
				fuente.insertar(vertice,fuente.longitud()+1);
		}
	}

	return recorrido;
}


void OrdenPrece(Grafo<char> &g,char vertice, list<char> opciones,list<char> &optima, list <char> &pasos, int &opti, int n)
{
	char aux;
	list<char> suc;
	while(!opciones.esVacia())
	{
		aux = opciones.consultar(1);
		opciones.eliminar(1);
		suc = g.Sucesores(aux);
		if(!suc.esVacia() or aux == vertice)
		{
			pasos.insertar(aux,1);
			if(aux==vertice and n>opti )
			{
				optima = pasos;
				opti = n;
			}
			else
				OrdenPrece(g,vertice,suc,optima,pasos,opti,n+1);
			pasos.eliminar(1);
		}
	}
}
for (typename std::map<T, int>::iterator it = mapa.begin(); it != mapa.end(); ++it) {
        std::cout << it->first << ": " << it->second << std::endl;
    }
    for(int i = 0; i < this->nVertices; i++){
        std::cout<<"anterior:"<<anterior[i]<<" "<<i<<" ";

    }*/