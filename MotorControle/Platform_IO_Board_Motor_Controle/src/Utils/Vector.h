
#ifndef VECTEUR_H
#define VECTEUR_H

//#define NULL 0

template <class T>
class Vector{
	public:

	Vector(){
		this->capacite = 5;
		this->taille = 0;
		this->tableau = new T[capacite];
	}
	
	Vector(Vector<T>& copy)
	{
		this->capacite = copy.getCapacite();
		this->tableau = new T[capacite];
		for(int x= 0; x < copy.size(); x++)
		{
			 this->tableau[x] = copy.get(x);
			
		}
		this->taille = copy.size();
	}
	
	T get(int index){
		if(index >=0 && index < taille)
			return tableau[index];
		return __null;
	}

	bool add(T item){
		if(item == __null)
			return false;

		if(taille+1>capacite){
			T* temp = new T[2*capacite];
			for(int x=0; x>taille ;x++){
				temp[x] = tableau[x];
			}
			delete[] tableau;		
			tableau = temp;
			capacite *=2;	
		}
		tableau[taille] = item;
		taille++;
		return true;
	}

	T remove(int index){
		if(index >=0 && index < taille){
			T temp = tableau[index];
			for(int x=index; x<taille;x++){
				tableau[x] = tableau[x+1];
			}
			taille--;
			return temp;
		}
		else
			return __null;
	}

	bool clear(){
		delete[] tableau;		
		taille = 0;
		capacite =5;
		tableau = new T[capacite];
		return true;
	}
		
	bool isEmpty(){
		if(taille ==0)
			return true;
		return false;
	}
	
	int size(){
		return taille;	
	}

	int getCapacite(){
		return capacite;
	}

	~Vector(){
		delete[] tableau;	
	}

	
	private:
		int capacite;
		int taille;
		T* tableau;
};


#endif
