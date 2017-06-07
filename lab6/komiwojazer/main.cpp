#include <vector> 
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <string>
#include <fstream>
#include <algorithm>
#include <ctime>

#define cityquantity 100


void clrScr() { system("clear"); } 

std::vector <std::vector<double>> fromfile(int& numberofNodes,int& numberofEdges)
{
        std::ifstream file("adjMat.txt");
        int x_size,y_size;
        file >> x_size;
        file >> y_size;
        x_size = static_cast<int>(x_size);

        double tmp;



        if(x_size != 0)
        {
            std::vector<std::vector<double>> connectionArray1(x_size,std::vector<double> (x_size));
            for(int i=0; i<x_size; i++)
            {
                for(int j=0; j<x_size; j++)
                {
                    file >> tmp;
                    if (tmp)
                        numberofEdges++;
                    connectionArray1[i][j] = tmp;
                }
            }
            numberofNodes = x_size;
            return connectionArray1;
        }
        else
        {
            std::vector <std::vector<double>> k;
            std::cout<<"Niestety nie"<<std::endl;
            return k;
        }
}

std::vector <std::vector<int>> pointsfromfile()
{
        std::ifstream file("komiwojazer2.dat");

        int tmp;

            std::vector<std::vector<int>> vektortab(cityquantity,std::vector<int> (3));
            for(int i=0; i<cityquantity; i++)
            {
                for(int j=0; j<3; j++)
                {
                    file >> tmp;
                    vektortab[i][j] = tmp;
                }
            }
            return vektortab;

}

void tofile(double path, std::vector <int> numvector,int counter)
{
        std::ofstream file("numvector.txt");
        file <<"Najkrótsza ścieżka: "<<path<<"\n";

            for(unsigned j=0; j<numvector.size(); j++)
            {
                file <<numvector[j]<<" ";
            }
        file <<"\n"<<counter;

}

void pointstofile(std::vector <int> numvector,std::vector <std::vector<int>> points)
{
        std::ofstream file("resultpoints.txt");
            for(int i=0; i<cityquantity; i++)
            {
                file << points[numvector[i]][0] <<" "<<points[numvector[i]][1]<<" "<<points[numvector[i]][2];  
                file <<"\n";
            }

}

//Zwraca długość, nie ruszać, wgl nie ruszać nic powyżej
double getLength(std::vector <int> numvector, std::vector<std::vector<double>> array)
{
	double length = 0;

	for(unsigned i = 0; i < (numvector.size()-1); i++)
	{
		length += array[numvector[i]][numvector[i+1]];
	}

	length += array[numvector[numvector.size()-1]][numvector[0]];

	return length;
}

//zabawna rzecz, nie ruszać
int randomna(int i)
{
	srand(time(0));
	return rand()%i;
}

//Operacja 2-opt, nie ruszać
void swapTwo(std::vector<int> &path)
{
  int rand1 = rand()%(path.size());
  int rand2 = rand()%(path.size());

  while(!((rand1 != rand2)&&(rand1<rand2)))
  {
    rand1 = rand()%(path.size());
    rand2 = rand()%(path.size());
  }

  std::vector<int>::iterator nth1 = path.begin() + rand1;
  std::vector<int>::iterator nth2 = path.begin() + rand2;

  std::reverse(nth1,nth2);

}



void swapThree(std::vector<int> &path)
{
  int rand1 = rand()%(path.size());
  int rand2 = rand()%(path.size());
  int rand3 = rand()%(path.size());

  while(!((rand1 != rand2)&&((rand2 != rand3))&&(rand1<rand2)&&(rand2<rand3)))
  {
    rand1 = rand()%(path.size());
    rand2 = rand()%(path.size());
    rand3 = rand()%(path.size());
  }

  std::vector<int>::iterator nth2 = path.begin() + rand2;
  std::vector<int>::iterator nth3 = path.begin() + rand3;

  std::reverse(nth2,nth3);


  std::vector<int>::iterator nth1 = path.begin() + rand1;
  nth3 = path.begin() + rand3;

  //std::reverse(nth1,nth3);

}


//Funkcja zwracająca prawdopodobieństwo, jeśli ktos ma notatki z wykładu
//To może znajdzie jakąś lepszą, ja tą mam z neta i jest podobno turbofajna
//(w exp przed całością nie ma minusa bo zamieniłem kolejność energy i energy_new)
double probability(float energy,float energy_new,double temperature,double temperatureold)
{
	if(energy_new>energy)
	{
		return exp((energy - energy_new)*(1.0/temperature-1.0/temperatureold));
	}
	else
	{
		return 1.0;
	}
}

//FUnkcja determinująca jak z każdą iteracją będzie maleć temperatura
//Jeśli ktoś ma trochę finezji to pewnie wymyśli fajną
//Internet mówi, że najczęściej jest takiej postaci i zmienia się tylko współczynnik
double changeTemperature(double oldtemperature,int cmod)
{
	return oldtemperature*0.99995;
}


//Paramter określający temperaturę początkową
double startingtemperature = 1.5/100.0;//1.7/static_cast<float>(cityquantity);

//startingtemperature*pow(0.999995,40000) tu można określić liczbę iteracji podstawiając za temperaturelimit (liczba iteracji to to 40000)

//Parametr określający limit temperatury
double temperaturelimit = 10e-3;


int main()
{

	std::vector<std::vector<double> > connectionArray(cityquantity,std::vector<double>(cityquantity));
	std::vector<std::vector<double> > tmpCarray(cityquantity,std::vector<double>(cityquantity));
  std::vector<std::vector<int> > points(cityquantity,std::vector<int>(3));

	int numberofNodes, numberofEdges;

   	connectionArray = fromfile(numberofNodes,numberofEdges);
    points = pointsfromfile();

    tmpCarray = connectionArray;

    double temperature = startingtemperature;
    double SPlenght;

    std::vector<int> vertices;
    std::vector<int> vertices2;
    std::vector<int> bestvertices;
    std::vector<int> bestverticesiniteration;

    for(int i = 0; i<cityquantity; i++)
    {
    	vertices.push_back(i);
    	vertices2.push_back(i);
    	bestvertices.push_back(i);
      bestverticesiniteration.push_back(i);
    }
   

    SPlenght = getLength(vertices,connectionArray);

    //std::cout<<"Początkowa długość"<<SPlenght;

    SPlenght = getLength(vertices,connectionArray);

    tofile(SPlenght,vertices,0);

    pointstofile(vertices,points);

    srand(time(0));

    double probabilityofdoing;

    bestvertices = vertices;

    int counter = 0;
    
    //Tu się dzieje wyżarzanie, nie wiem czy coś tu należy wgl zmieniać

    //Ta zmienna będzie przechowywać temperaturę z poprzedniej iteracji
    //Istnieje po to, bo funkcja prawdopodobieństwa ulepszona jej używa
    //Jeśli chcecie możecie używać domyślnej funkcji prawdopodobieństwa
    //Tj exp((energia-energia_nowa)/temperatura)
    //Ale ponoć ta funkcja co jest jest lepsza
    double temperatureold = changeTemperature(temperature,1);

    int cmod = 0;

    while(true)
    {

 
   
    //Jeśli chcemy, żeby od każdej kolejnej iteracji iteracji (:D) program mieszał ścieżkę
   	//To odkomentować to i zakomentować vertices=bestvertices
    //Nie wiem czy to jakiś turbodobry pomysł, zobaczyć należy co lepiej działa
    //if(counter)

    //Liczba modulo definiuje co ile przejść algorytmu jest losowany nowy wektor startowy
    //Przy dobrych parametrach powinno być co jedno przejście, bo pętla wewnętrzna
    //Powinna dość długo iść raczej i dawać dobry wynik już po przejściu jednym
    if(!(counter%200))
    {
      std::random_shuffle(bestverticesiniteration.begin(),bestverticesiniteration.end(),randomna);
    }

    counter++;

    //Ustawiam aktualny wektor jako najlepszy z poprzedniej iteracji
    //Nie ruszać tego przypisania, powyżej możecie zmienić na counter%1 jeśli chcecie
    //Co jedno wyrzażanie nowy
    vertices = bestverticesiniteration;

    //Licznik iteracji wewnętrznej pętli
    cmod = 0;

    //Pętla w której dzieje się wyżarzanie (pojedyncze opadnięcie temperatury)
    while(temperature > temperaturelimit)
    {

      vertices2 = vertices;

      cmod++;


      //To może was interesować, ZB mówił, że 2-opt lepsze więc dałem, że 3-opt jest turborzadko
      //Może dobrym pomysłem było co jakiś czas robić 3-opt ale jednocześnie dawać prawdopodobieństwo przepięcia 100?
      if(cmod%200)
      {
      swapTwo(vertices2);
      }
      else
      {
      swapThree(vertices2);
      }

      //Tu jest ustawiane prawdopodobieństwo przepięcia zgodnie z funkcją
      //nie musicie patrzyć do środka jak działa np. getLength bo działa dobrze
      //możecie coś zmieniać wewnątrz probability ale to nie jest główny problem optymalizacji
      //Jeśli chceice np zrobić to co napisałem nad tymi zmianami 2 i 3-opt to możecie to dać
      //wewnątrz tego ifa przy 2 opt a przy 3 opt dać probabilityofdoing = 1.0
      //Nie wiem jak to będzie działać, eksperymentujcie
    	probabilityofdoing = probability(getLength(vertices,connectionArray),getLength(vertices2,connectionArray),temperature,temperatureold);

    //	std::cout<<"Próba: "<<counter<<std::endl;
    //	std::cout<<"Energia stara: "<<getLength(vertices,connectionArray)<<std::endl;
    //	std::cout<<"Energia nowa: "<<getLength(vertices2,connectionArray)<<std::endl;


      //Nie musicie nic poniżej robic.
    	if(probabilityofdoing>rand()/(RAND_MAX+1.0))
    	{
    		vertices = vertices2;
    	}

  
    	if(getLength(bestvertices,connectionArray)>getLength(vertices,connectionArray))
    	{
    		bestvertices = vertices;
    		SPlenght = getLength(bestvertices,connectionArray);
    		tofile(SPlenght,bestvertices,counter);
        pointstofile(bestvertices,points);
    	}

      if(getLength(bestverticesiniteration,connectionArray)>getLength(vertices,connectionArray))
      {
        bestverticesiniteration = vertices;
      }
    //	std::cout<<"Najlepsza długość: "<<SPlenght<<std::endl<<"Temperatura: "<<temperature<<std::endl<<"Prawdopodobieństwo: "<<probabilityofdoing<<std::endl;

    //	clrScr();

      //tofile(SPlenght,bestvertices,counter);

      temperatureold = temperature;
      temperature = changeTemperature(temperature,cmod);	

    }

    //tofile(SPlenght,bestvertices,counter+1);
   
    temperature = startingtemperature;


	}


   	return 0;
}