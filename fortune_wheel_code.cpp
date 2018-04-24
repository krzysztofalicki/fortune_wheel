#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;




typedef struct node Node;

struct node {
	string data;
	int number;
	Node *next;
	Node *prev;
};



Node *create (){
	
	Node *nev;
	nev = new (Node);
	cout << "give the data";
	cin >> (nev-> data);
	cout << "give the number";
	cin >> (nev-> number);
	nev->next = NULL;
	nev->prev = NULL;
	
	return nev;
}



Node *createzero (){
	
	Node *nev;
	nev = new (Node);
	nev->data = "0";
	nev->number = 0;
	nev->next = NULL;
	nev->prev = NULL;
	
	return nev;
}



void addlastzero (Node **head, Node **tail){
	
	Node *tmp = createzero();
	
	if (*head == NULL){
		*head = tmp;
		*tail = tmp;
		tmp->next = *head;
		tmp->prev = *tail;
	}
	else{
		Node *pom = *head;
		while (pom->next != *head)
			pom = pom->next;
		pom->next = tmp;
		tmp->next = *head;
		tmp->prev = pom;
		(*head)->prev = tmp;
		(*tail) = tmp;
	}

}



void deletecurrent (Node **current){
	
	((*current)->next)->prev = ((*current)->prev);
	((*current)->prev)->next = ((*current)->next);
	delete (*current);
	
}


void showall (Node *head){
	
	if (head == NULL)
	cout << "empty!";
	
	else{
		Node *pom = head;
		while (pom->next != head){
			cout << pom->data;
			cout << pom->number;
			pom = pom->next;
		}
		cout << pom->data;
		cout << pom->number;
	}
}



Node *moveleft (Node **current){
	
	*current = (*current)->prev;
	
	return *current;
}



Node *moveright (Node **current){
	
	*current = (*current)->next;
	
	return *current;
}



int zapis_z_pliku (Node **head, Node **tail, string nazwa_pliku_wejsciowego, ifstream &plik_odczyt, ofstream &plik_zapis){
	
	int licznik = 0;
	
	plik_odczyt.open(nazwa_pliku_wejsciowego.c_str());
	
	bool wynik;
	
	wynik=plik_odczyt.is_open();
	if (!wynik){
		cout << "Blad otwierania pliku odczytywanego!" << endl;
		return -1;
	}
	
	while (true){
		
		wynik=plik_odczyt.good();
		if (!wynik) break;
		
		addlastzero(&*head, &*tail);
		
		plik_odczyt >> ((*tail)->data) >> ((*tail)->number);
		
		licznik++;
	
	}
	
	plik_odczyt.close();
	
	return licznik;
	
}



int main (void){
	
	srand(time(NULL));
	
	string nazwa_pliku_wejsciowego;

	ifstream plik_odczyt;
	ofstream plik_zapis;
	
	nazwa_pliku_wejsciowego = "test1.txt";
	
	cout << "Jestem kolem fortuny!!!" << endl;
	
	Node *head = NULL, *tail = NULL;
	Node *current = NULL;
	Node *temp = NULL;
	
	int licznik;
	
	licznik = zapis_z_pliku (&head, &tail, nazwa_pliku_wejsciowego, plik_odczyt, plik_zapis);
	
	current = head;
	
	int n = (rand()%1000);
	cout << "Wartosc pierwszego n to: " << n << endl;
	
	int cykl;
	
	if ((n%2) == 0){
		while (n > 0){
				moveright(&current);
				n--;
				cykl = 0;	
			}
		}
		
		else {
			while (n > 0){
				moveleft(&current);
				n--;
				cykl = 1;	
			}
	}
	
	cout << "Wygrales: " << current->data << endl;
	
	n = current->number;
	
	if (cykl == 1){
		temp = current->next;
		n--;	
	}
	else{
		temp = current->prev;
		n--;
	}
	
	deletecurrent (&current);
	
	current = temp;
	
	licznik--;
	
	while (licznik > 0){
		
		if (cykl == 1){
			
			while (n > 0){
				moveright(&current);
				n--;
				cykl = 0;	
			}
		}
		
		else {
			while (n > 0){
				moveleft(&current);
				n--;
				cykl = 1;	
			}
		}
	
		cout << "Wygrales: " << current->data << endl;
	
		n = current->number;
	
		if (cykl == 1){
			temp = current->next;
			n--;	
		}
		else{
			temp = current->prev;
			n--;
		}
	
		deletecurrent (&current);
	
		current = temp;
	
		licznik--;
	
	}
	
		
	system ("pause");
	return 0;
}






